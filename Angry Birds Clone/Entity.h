#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

#include "Box2D/Box2D.h"
#include "Resource.h"

class Entity{
public:
	Entity(){
		m_Pos = b2Vec2(15.0f, 5.0f);
		m_Angle = 0.0f;
		m_Type = b2_dynamicBody;
	};
	~Entity(){
		Engine::World->DestroyBody(m_BoxBody);
		m_BoxBody = nullptr;
	};

	b2Body* GetBody(){ return m_BoxBody; };

	virtual void Init() = 0;
	virtual void Process() = 0;
	virtual void Render() = 0;

protected:
	//OpenGL Rendering variables
	GLuint m_VAO, m_VBO;

	//Box2d variables
	b2Body* m_BoxBody;
	b2BodyType m_Type;

	//Entity variables
	b2Vec2 m_Pos;
	float m_Angle;
};