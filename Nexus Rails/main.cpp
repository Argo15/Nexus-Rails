#include <algorithm>
#include <stdlib.h>
#include <GL/freeglut.h>
#include "Root.h"
#include "RailsState.h"

int currentTime = 0;
int vsync = 0;
int sizeX = 0;
int sizeY = 0;
int counter = 0;

void init() {
	Root::ModelviewMatrix.push(glm::mat4(1.0f)); 
	Root::ProjectionMatrix.push(glm::mat4(1.0f));
	Root::NormalMatrix.push(glm::mat3(1.0f));

	Root::textureManager = new TextureManager();
	Root::textureManager->Initialize();
	Root::modelManager = new ModelManager();
	Root::modelManager->Initialize();
	Root::materialManager = new MaterialManager();
	Root::materialManager->Initialize();
	Root::shaderManager = new ShaderManager();
	Root::shaderManager->Initialize();

	Root::inputManager = new InputManager();

	Root::GAMESTATE = new RailsState();
}

void resize(int w, int h) {
	Root::GAMESTATE->resize(w,h);
	sizeX = w;
	sizeY = h;
}

void render(void) {
	int lastTime = currentTime;
	currentTime = glutGet( GLUT_ELAPSED_TIME );
	int timePassed = currentTime - lastTime;
	vsync += timePassed;
	
	if (vsync > (1000/60)){
		float fps = 1000.0f/timePassed;
		if (fps > 60)
			fps=60;
		vsync = 0;

		char buffer[5];
		_itoa((int)fps, buffer, 10);
		string title = string("Living Nexus - FPS: ") + string(buffer);
		glutSetWindowTitle(title.c_str());
		
		Root::GAMESTATE->tick((int)fps);
		counter++;
	}
	
}

void keyDown(unsigned char key, int xx, int yy) {
	if (key == 27) exit(0);
	Root::inputManager->registerKeyDown((int)key);
}

void keyUp(unsigned char key, int xx, int yy) {
	Root::inputManager->registerKeyUp((int)key);
}

void mousePress(int button, int state, int x, int y) {
	if (state == GLUT_DOWN)
		Root::inputManager->registerMouseButtonDown(button);
	else
		Root::inputManager->registerMouseButtonUp(button);
}

void mousePressedMove(int x, int y) {
	Root::inputManager->setMousePosition(x,y);
}

void mouseReleasedMove(int x, int y) {
	Root::inputManager->setMousePosition(x,y);
}

void specialKeyDown(int key, int xx, int yy)
{

}

void mouseWheel(int button, int dir, int x, int y)
{
}

int main(int argc, char **argv) {
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(1280,720);
	glutCreateWindow("Nexus Rails");

	// register callbacks
	glutDisplayFunc(render);
	glutReshapeFunc(resize);
	glutIdleFunc(render);
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(specialKeyDown);
	glutMouseFunc(mousePress);
	glutMotionFunc(mousePressedMove);
	glutPassiveMotionFunc(mouseReleasedMove);

	// enter GLUT event processing cycle
	init();
	glutMainLoop();

	return 1;
}
