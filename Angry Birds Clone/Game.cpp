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
	Engine::Process();
	level1.Process();
}