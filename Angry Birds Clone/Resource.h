#pragma once

#include "Dependencies\glew\glew.h"
#include "Box2D/Box2D.h"
#include "ShaderLoader.h"

namespace Engine {
	static const b2Vec2 Gravity(0.0f, -9.8f);
	extern b2World* World;
	extern GLuint DebugShader;

	float const TimeStep = 1.0f / 60.0f;
	int const VelocityIterations = 6;
	int const PositionIterations = 2;

	void Process();
	void Init();
}
