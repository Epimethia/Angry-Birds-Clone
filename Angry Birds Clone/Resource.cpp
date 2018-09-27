#include "Resource.h"
#include "ShaderLoader.h"
#include "Clock.h"

extern b2World* Engine::World = new b2World(Engine::Gravity);
extern Listener* Engine::CL = new Listener;
extern GLuint Engine::DebugShader = GLuint();
extern GLuint Engine::EntityShader = GLuint();
extern float Engine::DeltaTick = 0.0f;
extern std::shared_ptr<InputManager> Engine::IM = InputManager::GetInstance();

void Engine::Init() {
	ShaderLoader SL;
	ShaderLoader SL1;

	//initializing global clock
	Clock::GetInstance();

	EntityShader = SL.CreateProgram(
		const_cast<char*>("Dependencies/shaders/Vertex Shader.vs"),
		const_cast<char*>("Dependencies/shaders/Fragment Shader.fs")
	);

	//Have no idea why it requires 2 shader loaders
	DebugShader = SL1.CreateProgram(
		const_cast<char*>("Dependencies/shaders/Debug Vertex Shader.vs"),
		const_cast<char*>("Dependencies/shaders/Debug Fragment Shader.fs")
	);

	World->SetContactListener(&*CL);
}

void Engine::Process() {
	DeltaTick = Clock::GetDeltaTime();
	World->Step(DeltaTick, VelocityIterations, PositionIterations);
	World->ClearForces();
}