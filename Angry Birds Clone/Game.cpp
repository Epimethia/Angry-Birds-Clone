#include "Game.h"

Game::Game() {}

Game::~Game() {}

void Game::Init() {
	level1.Init();
}

void Game::Render() {
	level1.Render();
}

void Game::Process() {
	if (Engine::IM->KeyArray['r'] == KEYSTATE::FIRST_PRESSED) {
		level1 = Level();
		level1.Init();
		//delete Engine::World;
		//Engine::World = new b2World(Engine::Gravity);
	}
	Engine::Process();
	level1.Process();
}