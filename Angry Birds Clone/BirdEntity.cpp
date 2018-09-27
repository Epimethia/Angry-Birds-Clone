#include "BirdEntity.h"

BirdEntity::BirdEntity(){
	m_Pos = b2Vec2(15.0f, 5.0f);
	m_Radius = 1.0f;
	m_SpawnPos = b2Vec2(0.0f, 0.0f);
	m_Angle = 0.0f;
	m_Type = b2_dynamicBody;
}

BirdEntity::~BirdEntity(){

}

BirdEntity::BirdEntity(b2Vec2 _Pos, float _Radius, float _Angle, b2BodyType _Type){
	m_Pos = _Pos;
	m_Radius = _Radius;
	m_Angle = _Angle;
	m_Type = _Type;
	m_SpawnPos = _Pos;
}

void BirdEntity::Init(){
	m_bEnableDecay = false;
	m_fDecayTimer = 0.0f;
	//Creating the rigidbody for the entity
	b2BodyDef BoxBodyDef;
	BoxBodyDef.type = m_Type;
	BoxBodyDef.active = true;
	BoxBodyDef.position.Set(m_Pos.x, m_Pos.y);
	BoxBodyDef.angle = m_Angle;

	//Spawning the body with the engine
	m_BoxBody = Engine::World->CreateBody(&BoxBodyDef);

	//Defining physics parameters for the fixture
	b2FixtureDef FixtureDef;
	CircleBody.m_p.Set(0.0f, 0.0f);
	CircleBody.m_radius = m_Radius;
	FixtureDef.shape = &CircleBody;
	FixtureDef.density = 20.0f;
	FixtureDef.friction = 0.5f;
	FixtureDef.restitution = 0.001f;

	//Binding the fixture to the body
	m_BoxBody->CreateFixture(&FixtureDef);

	ed = new EntityData;
	ed->EntityType = "Bird";
	m_BoxBody->SetUserData(ed);
	auto a = static_cast<EntityData*>(m_BoxBody->GetUserData())->EntityType;

	//Translating the vertices supplied by Box2D into vertices usable by GLEW
	float verts[216];
	int CurrentIndex = 0;
	for (int i = 0; i < 36; ++i) {
		float angle = (i * 10.0f) * 3.1415f / 180.0f;
		verts[CurrentIndex++] = (CircleBody.m_radius * std::cos(angle)); //x
		verts[CurrentIndex++] = (CircleBody.m_radius * std::sin(angle)); //y
		verts[CurrentIndex++] = 0.0f; //z

		//color verts (the birds are all blue)
		verts[CurrentIndex++] = 1.0f;
		verts[CurrentIndex++] = 0.82f;
		verts[CurrentIndex++] = 0.0f;
	}


	//generating and binding the buffers
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glBindVertexArray(m_VAO);

	//Enabling the positional floats
	glVertexAttribPointer(
		0, 3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GLfloat),
		(GLvoid*) 0
	);
	glEnableVertexAttribArray(0);

	//Enabling Color Floats
	glVertexAttribPointer(
		1, 3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GLfloat),
		(GLvoid*) (3 * sizeof(GLfloat))
	);
	glEnableVertexAttribArray(1);

	//CleanUp (Unbinding)
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void BirdEntity::Process(){
	
}

void BirdEntity::Render(){
	//Creating the transformation matrices
	glm::mat4 TranslationMatrix = glm::translate(glm::mat4(), glm::vec3(m_BoxBody->GetPosition().x, m_BoxBody->GetPosition().y, 0.0f));
	glm::mat4 RotationMatrix = glm::rotate(glm::mat4(), m_BoxBody->GetAngle(), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(), glm::vec3(1.0f, 1.0f, 1.0f));

	//Creating the MVP using the translation matrices and orthographic projection
	glm::mat4 ModelMatrix = TranslationMatrix * RotationMatrix * ScaleMatrix;
	glm::mat4 proj = glm::ortho(0.0f, Engine::ScreenWidth / Engine::Ratio, 0.0f, Engine::ScreenHeight / Engine::Ratio);			//Scaled down to accomodate for Box2D's unit measurements
	glm::mat4 MVP = proj * ModelMatrix;

	//Setting a memory pointer in the shader program to the MVP
	glUniformMatrix4fv(glGetUniformLocation(Engine::DebugShader, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));

	//Binding appropriate buffers and rendering
	glUseProgram(Engine::DebugShader);
	glBindVertexArray(m_VAO);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_LINE_LOOP, 0, 36);
	glBindVertexArray(0);
}
