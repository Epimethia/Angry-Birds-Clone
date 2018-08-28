#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"

#include "Box2D/Box2D.h"

#include "Entity.h"
#include "Resource.h"

class BirdEntity : public Entity{
public:
	BirdEntity();
	~BirdEntity();
	BirdEntity(b2Vec2 _Pos, b2Vec2 _Size, float _Angle, b2BodyType _Type);

	void Init();
	void Process();
	void Render();

	b2Vec2 m_SpawnPos;
};

