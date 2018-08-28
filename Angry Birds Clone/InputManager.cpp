#include "InputManager.h"
#include <iostream>
unsigned char InputManager::KeyArray[255];
unsigned int InputManager::MouseArray[3];
glm::vec2 InputManager::MousePos = glm::vec2();
std::shared_ptr<InputManager> InputManager::InputManagerInstance;

//Initializes all the keys in the array to "Released" state
InputManager::InputManager() {
	for (int i = 0; i < 255; ++i) KeyArray[i] = RELEASED;
	for (int i = 0; i < 3; ++i) MouseArray[i] = RELEASED;
}

unsigned char InputManager::ProcessKeys() {
	glutKeyboardFunc(InputManager::NormKeyDown);
	glutKeyboardUpFunc(InputManager::NormKeyUp);

	if (KeyArray['t'] == FIRST_PRESSED) {
		KeyArray['t'] = HELD;
		return 't';
	}
	else if (KeyArray['l'] == FIRST_PRESSED) {
		KeyArray['l'] = HELD;
		return 'l';
	}
	else return 'm';
}

void InputManager::ProcessMouse() {
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMovement);
	glutPassiveMotionFunc(MouseMovement);

	if (MouseArray[MOUSE_LEFT] == FIRST_PRESSED) {
		MouseArray[MOUSE_LEFT] = HELD;
	}
}

std::shared_ptr<InputManager> InputManager::GetInstance() {
	if (InputManagerInstance == nullptr) {
		InputManagerInstance = std::shared_ptr<InputManager>();
		for (int i = 0; i < 255; ++i) KeyArray[i] = RELEASED;
		for (int i = 0; i < 3; ++i) MouseArray[i] = RELEASED;
	}
	return InputManagerInstance;
}

void InputManager::DestroyInstance() {
	InputManagerInstance.reset();
}

void InputManager::NormKeyDown(unsigned char key, int x, int y) {
	KeyArray[key] = FIRST_PRESSED;
}

void InputManager::NormKeyUp(unsigned char key, int x, int y) {
	KeyArray[key] = RELEASED;
}

void InputManager::MouseButton(int button, int state, int x, int y) {
	if (button < 3) {
		if (state == GLUT_DOWN) MouseArray[button] = FIRST_PRESSED;
		else if (state == GLUT_UP) MouseArray[button] = RELEASED;
	}
}

void InputManager::MouseMovement(int x, int y) {
	MousePos = glm::vec2(x, y);
}
