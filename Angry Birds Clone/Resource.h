#pragma once

#include "Dependencies\glew\glew.h"
#include "Box2D/Box2D.h"
#include "ShaderLoader.h"

namespace Engine {
	static const b2Vec2 Gravity(0.0f, -9.8f);
	extern b2World* World;
	extern GLuint DebugShader;
	extern GLuint EntityShader;

	static float ScreenWidth = 1300.0f;
	static float ScreenHeight = 600.0f;
	static float Ratio = 120.0f;

	float const TimeStep = 1.0f / 120.0f;
	int const VelocityIterations = 20;
	int const PositionIterations = 20;

	void Process();
	void Init();
}
