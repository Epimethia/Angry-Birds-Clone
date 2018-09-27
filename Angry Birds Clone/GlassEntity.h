#pragma once
#include "BoxEntity.h"

class GlassEntity : public BoxEntity {
public:	
	GlassEntity();
	~GlassEntity();
	GlassEntity(b2Vec2 _Pos, b2Vec2 _Size, float _Angle, b2BodyType _Type);

	void Init();
	void Process();
	void Render();
};