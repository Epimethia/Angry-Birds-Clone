#pragma once

#include "Level.h"
#include "InputManager.h"

class Game {
public:
	void Process();
	Game();
	~Game();
	void Init();
	void Render();
private:
	Level level1;
};