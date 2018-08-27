#include "Level.h"
#include "Line.h"
Level::Level () {
	Ground = std::make_shared<BoxEntity>(b2Vec2(13.1f, 0.5f), b2Vec2(17.0f, 0.5f), 0.0f, b2_staticBody);
	Box = std::make_shared<BoxEntity>();
	EntityVect.push_back(Ground);
	EntityVect.push_back(Box);
}

Level::~Level () {}

void Level::Init() {
	for (auto& it : EntityVect) {
		it->Init();
	}
	IM = InputManager::GetInstance();
	IM->ProcessKeys();
	IM->ProcessMouse();

	b2BodyDef bodyDef;
	m_groundbody = Engine::World->CreateBody(&bodyDef);
}

void Level::Process() {

	//process loop
	for (auto& it : EntityVect) {
		it->Process();
	}

	if (IM->MouseArray[MOUSE_LEFT] == FIRST_PRESSED && MouseJoint == nullptr) {
		b2Body* body = Box->GetBody();
		md.bodyA = m_groundbody;
		md.bodyB = body;
		md.target = b2Vec2(IM->GetMousePos().x / 25.0f, IM->GetMousePos().y / 25.0f);
		md.maxForce = 1000.0f;
		md.frequencyHz = 5.0f;
		md.dampingRatio = 1.0f;
		md.collideConnected = true;
		MouseJoint = (b2MouseJoint*) Engine::World->CreateJoint(&md);
		body->SetAwake(true);
	}
	if (IM->MouseArray[MOUSE_LEFT] == HELD && MouseJoint != nullptr) {
		MouseJoint->SetTarget(b2Vec2(IM->GetMousePos().x / 30.0f, (600.0f - IM->GetMousePos().y) / 30.0f));
	}
	if (IM->MouseArray[MOUSE_LEFT] == RELEASED && MouseJoint != nullptr) {
		Engine::World->DestroyJoint(MouseJoint);
		MouseJoint = nullptr;
	}
	IM->ProcessKeys();
	IM->ProcessMouse();
}

void Level::Render() {
	Box->GetBody()->SetTransform(b2Vec2(5.0f,5.0f), 0.0f);
	for (auto& it : EntityVect) {
		it->Render();
	}
}