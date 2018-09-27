#include "Level.h"

Level::Level() {
	SlingshotPos = b2Vec2(1.5f, 1.5f);
	EntityVect.push_back(std::make_shared<GroundEntity>());

	//Building Blocks
	EntityVect.push_back(std::make_shared<BoxEntity>(b2Vec2(8.4f, 0.5f), b2Vec2(0.07f, 0.1f), 0.0f, b2_dynamicBody));
	EntityVect.push_back(std::make_shared<BoxEntity>(b2Vec2(9.0f, 0.5f), b2Vec2(0.07f, 0.1f), 0.0f, b2_dynamicBody));
	EntityVect.push_back(std::make_shared<BoxEntity>(b2Vec2(9.6f, 0.5f), b2Vec2(0.07f, 0.1f), 0.0f, b2_dynamicBody));
	EntityVect.push_back(std::make_shared<BoxEntity>(b2Vec2(10.2f, 0.5f), b2Vec2(0.07f, 0.1f), 0.0f, b2_dynamicBody));
	EntityVect.push_back(std::make_shared<BoxEntity>(b2Vec2(9.3f, 0.6f), b2Vec2(0.96f, 0.07f), 0.0f, b2_dynamicBody));

	EntityVect.push_back(std::make_shared<GlassEntity>(b2Vec2(8.8f, 1.2f), b2Vec2(0.07f, 0.55f), 0.0f, b2_dynamicBody));
	EntityVect.push_back(std::make_shared<GlassEntity>(b2Vec2(9.8f, 1.2f), b2Vec2(0.07f, 0.55f), 0.0f, b2_dynamicBody));
	EntityVect.push_back(std::make_shared<GlassEntity>(b2Vec2(9.3f, 1.7f), b2Vec2(0.55f, 0.05f), 0.0f, b2_dynamicBody));

	EntityVect.push_back(std::make_shared<GlassEntity>(b2Vec2(9.0f, 2.2f), b2Vec2(0.07f, 0.45f), 0.0f, b2_dynamicBody));
	EntityVect.push_back(std::make_shared<GlassEntity>(b2Vec2(9.6f, 2.2f), b2Vec2(0.07f, 0.45f), 0.0f, b2_dynamicBody));

	EntityVect.push_back(std::make_shared<BoxEntity>(b2Vec2(9.3f, 2.9f), b2Vec2(0.35f, 0.07f), 0.0f, b2_dynamicBody));
	EntityVect.push_back(std::make_shared<BoxEntity>(b2Vec2(9.3f, 3.1f), b2Vec2(0.07f, 0.2f), 0.0f, b2_dynamicBody));


	//The birds
	BirdVect.push_back(std::make_shared<BirdEntity>(b2Vec2(1.8f, 0.5f), 0.1f, 0.0f, b2_dynamicBody));
	BirdVect.push_back(std::make_shared<BirdEntity>(b2Vec2(2.1f, 0.5f), 0.1f, 0.0f, b2_dynamicBody));
	BirdVect.push_back(std::make_shared<BirdEntity>(b2Vec2(2.4f, 0.5f), 0.1f, 0.0f, b2_dynamicBody));
}

Level::~Level () {
	BirdVect.clear();
	EntityVect.clear();
	Engine::World->DestroyBody(m_nullBody);
}

void Level::Init() {
	for (auto& it : EntityVect) {
		it->Init();
	}
	for (auto& it : BirdVect) {
		it->Init();
	}
	IM = InputManager::GetInstance();
	IM->ProcessKeys();
	IM->ProcessMouse();

	b2BodyDef bodyDef;
	m_nullBody = Engine::World->CreateBody(&bodyDef);
}

void Level::Process() {

	//process loop
	for (auto& it : EntityVect) {
		it->Process();
	}
	if (BirdVect.size() == 0) {
		return;
	}
	for (auto& it : BirdVect) {
		it->Process();
	}

	float MouseX = ((IM->GetMousePos().x) / 120.0f);
	float MouseY = ((Engine::ScreenHeight - IM->GetMousePos().y) / 120.0f);

	b2Body* body = BirdVect.back()->GetBody();
	//Create the mouse joint and initialize it
	if (IM->MouseArray[MOUSE_LEFT] == FIRST_PRESSED && MouseJoint == nullptr) {
		body->SetTransform(b2Vec2(MouseX, MouseY), 0.0f);
		body->SetAwake(false);
		md.bodyA = m_nullBody;
		md.bodyB = body;
		md.target = b2Vec2(MouseX, MouseY);
		md.maxForce = 1000.0f;
		md.frequencyHz = 100.0f;
		md.dampingRatio = 6.0f;
		md.collideConnected = false;
		MouseJoint = static_cast<b2MouseJoint*>(Engine::World->CreateJoint(&md));
		body->SetFixedRotation(true);
	}

	//Move the mouse joint in relation to the mouse pos
	if (IM->MouseArray[MOUSE_LEFT] == HELD && MouseJoint != nullptr) {
		if ((body->GetPosition() - SlingshotPos).Length() >= 1.0f){
			b2Vec2 d = body->GetPosition() - SlingshotPos;
			d.Normalize();
			d *= 0.99f;
			body->SetTransform(d + SlingshotPos, 0.0f);
			MouseJoint->SetTarget(d + SlingshotPos);
		}
		else{
			MouseJoint->SetTarget(b2Vec2(MouseX, MouseY));
		}
	}

	//Destroy the mouse joint, calculate the spring force, and apply it
	if (IM->MouseArray[MOUSE_LEFT] == RELEASED && MouseJoint != nullptr) {
	
		Engine::World->DestroyJoint(MouseJoint);
		MouseJoint = nullptr;
		//Using the spring formula, f = -kx for the slingshot
		b2Vec2 Direction = body->GetPosition() - SlingshotPos;
		b2Vec2 Force = Direction;				//Force is a copy of Direction because .Normalize() changes the b2vec2 its used on
		float k = 12.0f;						//Strength of the spring
		float x = Direction.Length() * 0.7f;	//Distance stretched
		Force.Normalize();						//Normalizing the direction vector
		Force *= -1.0f * (k * x);				//Calculating the force and multiplying it to the direction vector (F = -1 * (k * x))

		body->SetAwake(false);
		body->SetAwake(true);
		body->SetLinearVelocity(b2Vec2(Force.x, Force.y));
		body->SetFixedRotation(false);
		BirdVect.back()->m_bEnableDecay = true;
		EntityVect.push_back(BirdVect.back());
		BirdVect.pop_back();
	}

	body = nullptr; //since this is a temp pointer, just making sure that we dont leave an unsafe pointer
	IM->ProcessKeys();
	IM->ProcessMouse();
	
	//garbage collection
	std::vector<std::shared_ptr<Entity>>::iterator it = EntityVect.begin();
	while (it != EntityVect.end()) {
		if ((*it)->ed->m_bIsMarkedForDestruction) {
			it->reset();
			it = EntityVect.erase(it);
			std::cout << "Erased an element. Current Body count:" << Engine::World->GetBodyCount() << std::endl;
		}
		else { 
			it++;
		};
	}
}

void Level::Render() {
	for (auto& it : EntityVect) {
		it->Render();
	}
	for (auto& it : BirdVect) {
		it->Render();
	}
}
