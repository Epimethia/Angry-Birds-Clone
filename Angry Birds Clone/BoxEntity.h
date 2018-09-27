#pragma once

#include "Box2D/Box2D.h"

#include "Entity.h"
#include "Resource.h"

class BoxEntity : public Entity {
public:
	BoxEntity();
	~BoxEntity();
	BoxEntity(b2Vec2 _Pos, b2Vec2 _Size, float _Angle, b2BodyType _Type);

	void Init();
	void Process();
	void Render();
protected:
	b2PolygonShape m_DynamicBox;
	b2Vec2 m_Size;
};