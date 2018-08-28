#include "Resource.h"
#include "ShaderLoader.h"
extern b2World* Engine::World = new b2World(Engine::Gravity);
extern GLuint Engine::DebugShader = GLuint();

void Engine::Init() {
	ShaderLoader SL;
	DebugShader = SL.CreateProgram(
		const_cast<char*>("Dependencies/shaders/Vertex Shader.vs"),
		const_cast<char*>("Dependencies/shaders/Fragment Shader.fs")
	);
}

void Engine::Process() {
	World->Step(TimeStep, VelocityIterations, PositionIterations);
	World->ClearForces();
}