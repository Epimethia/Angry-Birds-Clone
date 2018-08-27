#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

#include "Box2D/Box2D.h"
#include "Resource.h"

class BoxEntity {
public:
	BoxEntity();
	~BoxEntity();
	BoxEntity(b2Vec2 _Pos, b2Vec2 _Size, float _Angle, b2BodyType _Type);
	b2Body* GetBody() { return m_BoxBody; };

	void Init();
	void Process();
	void Render();

private:
	//OpenGL Rendering variables
	GLuint m_VAO, m_VBO;

	b2PolygonShape m_DynamicBox;
	b2Body* m_BoxBody;

	b2Vec2 m_Pos;
	b2Vec2 m_Size;
	float m_Angle;
	b2BodyType m_Type;
};