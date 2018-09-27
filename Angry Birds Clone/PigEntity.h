#pragma once
#include "Entity.h"

class PigEntity : public Entity {
public:
	PigEntity();
	~PigEntity();
	PigEntity(b2Vec2 _Pos);

	void Init();
	void Process();
	void Render();
protected:
	b2PolygonShape m_DynamicBox;
	b2Vec2 m_Size;
};