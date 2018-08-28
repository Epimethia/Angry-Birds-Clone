#pragma once
#include "Box2D/Box2D.h"
#include "Resource.h"
#include "BoxEntity.h"
#include "BirdEntity.h"
#include "InputManager.h"
#include <memory>

class Level {
public:
	Level();
	~Level();

	void Process();
	void Init();
	void Render();


private:
	std::shared_ptr<BoxEntity> Box;
	std::shared_ptr<BoxEntity> Ground;
	std::shared_ptr<InputManager> IM;
	b2Body* m_groundbody;

	b2Vec2 SlingshotPos;

	b2MouseJoint* MouseJoint;
	b2MouseJointDef md;

	std::vector<std::shared_ptr<Entity>> EntityVect;
	std::vector<std::shared_ptr<BirdEntity>> BirdVect;
};