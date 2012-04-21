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
	glEnable(GL_TEXTURE_2D);

	view = new View();
	camera = new Camera();
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
	Root::ModelviewMatrix.top() = glm::mat4(1.0f);
	Root::ProjectionMatrix.top() = glm::mat4(1.0f);

	camera->mouseRotate();
	camera->move(fps/20);
	view->use3D(true);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLSLProgram *glslProgram = Root::shaderManager->getShader("Basic");
	glslProgram->use();

	glBindFragDataLocation(glslProgram->getHandle(), 0, "fragColor");
	glBindAttribLocation(glslProgram->getHandle(), 0, "v_vertex");
	glBindAttribLocation(glslProgram->getHandle(), 1, "v_texture");

	camera->transformToMatrix(&Root::ProjectionMatrix.top());
	glslProgram->sendUniform("projectionCameraMatrix", &Root::ProjectionMatrix.top()[0][0]);
	glslProgram->sendUniform("modelviewMatrix", &Root::ModelviewMatrix.top()[0][0]);
	glm::mat4 texMat = glm::mat4(1.0f);
	glslProgram->sendUniform("textureMatrix", &texMat[0][0]);

	glslProgram->sendUniform("camPos",camera->geteyeX(),camera->geteyeY(),camera->geteyeZ());

	glActiveTexture(GL_TEXTURE0); 
	Root::textureManager->BindTexture("cobble");
	glslProgram->sendUniform("tex",0);
	glslProgram->sendUniform("material.color", 1.0f,1.0f,1.0f);
	glslProgram->sendUniform("material.emission", 0);

	for (float i=0; i<1.0; i += 0.01) {
		for (float j=0; j<1.0; j += 0.01) {
			glBegin(GL_QUADS);
				glVertexAttrib2f(1,0.0,0.0); glVertexAttrib3f(0,-50.0+100*i,0.0,-50.0+100*j);
				glVertexAttrib2f(1,0.0,1.0); glVertexAttrib3f(0,-50.0+100*i,0.0,-50.0+100*j+1);
				glVertexAttrib2f(1,1.0,1.0); glVertexAttrib3f(0,-50.0+100*i+1,0.0,-50.0+100*j+1);
				glVertexAttrib2f(1,1.0,0.0); glVertexAttrib3f(0,-50.0+100*i+1,0.0,-50.0+100*j);
			glEnd();
		}
	}
	glslProgram->disable();
	glutSwapBuffers();
}
