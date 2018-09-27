#include "Resource.h"
#include "ShaderLoader.h"
extern b2World* Engine::World = new b2World(Engine::Gravity);
extern Listener* Engine::CL = new Listener;
extern GLuint Engine::DebugShader = GLuint();
extern GLuint Engine::EntityShader = GLuint();

void Engine::Init() {
	ShaderLoader SL;
	ShaderLoader SL1;

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
	World->Step(TimeStep, VelocityIterations, PositionIterations);
	World->ClearForces();
}