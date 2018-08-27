#pragma once
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtx\string_cast.hpp"
#include <iostream>

enum KEYSTATE {
	FIRST_PRESSED,
	HELD,
	RELEASED
};

enum MOUSE_INPUT {
	MOUSE_LEFT,
	MOUSE_RIGHT,
	MOUSE_MIDDLE
};

class InputManager {
public:
	glm::vec2 GetMousePos() { return MousePos; }
	unsigned char ProcessKeys();
	void ProcessMouse();
	static std::shared_ptr<InputManager> GetInstance();
	void DestroyInstance();

	//Contains an array of all normal characters on a keyboard
	static unsigned char KeyArray[255];

	//Contains an array of the 3 mouse buttons
	static unsigned int MouseArray[3];
	static glm::vec2 MousePos;

private:
	InputManager();

	static std::shared_ptr<InputManager> InputManagerInstance;



	static void NormKeyDown(unsigned char key, int x, int y);;
	static void NormKeyUp(unsigned char key, int x, int y);;
	static void MouseButton(int button, int state, int x, int y);
	static void MouseMovement(int x, int y);
};

