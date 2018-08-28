#include "Game.h"

Game* g = new Game;

void Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	g->Render();
	glutSwapBuffers();
}

void Update() {
	g->Process();
	glutPostRedisplay();
}

void init() {
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glLineWidth(1.0f);
	g->Init();
	Engine::Init();
	InputManager::GetInstance();
}

void exit() {
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);

	//Box2D initialization
	B2_NOT_USED(argc);
	B2_NOT_USED(argv);

	glutSetOption(GLUT_MULTISAMPLE, 8);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Engine::ScreenWidth, Engine::ScreenHeight);
	glutCreateWindow("OpenGL First Window");
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_MULTISAMPLE);
	glewInit();
	init();
	glutDisplayFunc(Render);
	glutIdleFunc(Update);
	glutIgnoreKeyRepeat(1);
	glutCloseFunc(exit);

	glutMainLoop();
	return 0;
}

