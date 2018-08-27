#include "Resource.h"
extern b2World* Engine::World = new b2World(Engine::Gravity);
extern GLuint Engine::DebugShader = GLuint();

void Engine::Init() {

}

void Engine::Process() {
	World->Step(TimeStep, VelocityIterations, PositionIterations);
	World->ClearForces();
}