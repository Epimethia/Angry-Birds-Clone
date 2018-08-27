#include "Entity.h"
#include <iostream>

BoxEntity::BoxEntity() {
	m_Pos = b2Vec2(15.0f, 15.0f);
	m_Size = b2Vec2(0.3f, 0.3f);
	m_Angle = 0.0f;
	m_Type = b2_dynamicBody;
}

BoxEntity::BoxEntity(b2Vec2 _Pos, b2Vec2 _Size, float _Angle, b2BodyType _Type) {
	m_Pos = _Pos;
	m_Size = _Size;
	m_Angle = _Angle;
	m_Type = _Type;
}

BoxEntity::~BoxEntity() {
	//Engine::World->DestroyBody(m_BoxBody);
	//m_BoxBody = nullptr;
}

void BoxEntity::Init() {
	b2BodyDef BoxBodyDef;
	BoxBodyDef.type = m_Type;
	BoxBodyDef.position.Set(m_Pos.x, m_Pos.y);

	m_BoxBody = Engine::World->CreateBody(&BoxBodyDef);
	m_DynamicBox.SetAsBox(m_Size.x, m_Size.y);

	b2FixtureDef FixtureDef;
	FixtureDef.shape = &m_DynamicBox;
	FixtureDef.density = 1.0f;
	FixtureDef.friction = 0.1f;
	FixtureDef.restitution = 0.0f;
	m_BoxBody->CreateFixture(&FixtureDef);


	float verts[300];

	int CurrentIndex = 0;
	for (int i = 0; i < m_DynamicBox.m_count; i++) {
		verts[CurrentIndex++] = (m_DynamicBox.m_vertices[i].x); //x
		verts[CurrentIndex++] = (m_DynamicBox.m_vertices[i].y); //y
		verts[CurrentIndex++] = 0.0f; //z

		//color verts
		verts[CurrentIndex++] = 1.0f;
		verts[CurrentIndex++] = 1.0f; 
		verts[CurrentIndex++] = 1.0f;
	}
	

	//generating and binding the buffers
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLuint) * (6 * m_DynamicBox.m_count), verts, GL_STATIC_DRAW);
	glBindVertexArray(m_VAO);

	//Enabling the positional floats
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GLfloat),
		(GLvoid*) 0
	);

	glEnableVertexAttribArray(0);

	//Enabling Color Floats
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GLfloat),
		(GLvoid*) (3 * sizeof(GLfloat))
	);
	glEnableVertexAttribArray(1);
}

void BoxEntity::Process() {
	//std::cout << m_BoxBody->GetPosition().y << std::endl;
}

void BoxEntity::Render() {
	glm::mat4 TranslationMatrix = glm::translate(glm::mat4(), glm::vec3(m_BoxBody->GetPosition().x, m_BoxBody->GetPosition().y, 0.0f));
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(), glm::vec3(30.0f, 30.0f, 30.0f));

	glm::mat4 ModelMatrix = ScaleMatrix * TranslationMatrix;
	glm::mat4 proj = glm::ortho(0.0f, 900.0f, 0.0f, 600.0f);
	glm::mat4 MVP = proj * ModelMatrix;

	glUniformMatrix4fv(glGetUniformLocation(Engine::DebugShader, "MVP"), 1, GL_FALSE, glm::value_ptr(MVP));

	glUseProgram(Engine::DebugShader);
	glBindVertexArray(m_VAO);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	glBindVertexArray(0);
}
