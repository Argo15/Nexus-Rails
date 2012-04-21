#include "RailsState.h"

RailsState::RailsState() : GameState() {
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);

	view = new View();
	camera = new WorldCamera();
	frustum = new Frustum();
}

void RailsState::resize(int w, int h) {
	if(h == 0)
		h = 1;
	GLfloat aspect = GLfloat(w) / h;
	view->viewport(0, 0, w, h);
	view->set3D(45.0f,aspect,0.01,500);
	view->set2D(0,1,0,1,0,1);
}

void RailsState::tick(int fps) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	view->use3D(true);
	glMultMatrix(&Root::ProjectionMatrix[0][0]);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBegin(GL_QUADS);
	
}
