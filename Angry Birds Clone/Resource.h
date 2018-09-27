#pragma once
#include "Dependencies\glew\glew.h"
#include "Box2D/Box2D.h"
#include "ContactListener.h"
#include "InputManager.h"

namespace Engine {
	static const b2Vec2 Gravity(0.0f, -9.8f);
	extern b2World* World;
	extern Listener* CL;
	static float ScreenWidth = 1300.0f;
	static float ScreenHeight = 600.0f;
	static float Ratio = 120.0f;

	extern float DeltaTick;

	extern std::shared_ptr<InputManager> IM;


	int const VelocityIterations = 20;
	int const PositionIterations = 20;

	extern GLuint DebugShader;
	extern GLuint EntityShader;

	void Process();
	void Init();
}
