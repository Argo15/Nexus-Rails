#include "RailsState.h"
#include "Root.h"

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
	rails = new RailsManager();
	cameraMode = true;
	rails->reloadRails();
	clock = 0;
	glowEnabled = false;
	//glowBuffer = new FBO();
	Root::MIDIPLAYER->init();
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
	clock += 1.0/fps;
	if (clock > 1.0) {
		clock = 0.0;
		rails->reloadRails();
	}
	Root::ModelviewMatrix.top() = glm::mat4(1.0f);
	Root::ProjectionMatrix.top() = glm::mat4(1.0f);

	camera->mouseRotate();
	if (cameraMode) {
		camera->move(fps/20);
	} else {
		rails->updateTime(camera,fps/6000.0);
	}
	if (Root::inputManager->isKeyDownOnce('c')) {
		cameraMode = !cameraMode;
	}
	view->use3D(true);

	if (Root::inputManager->isKeyDownOnce('g')) {
		glowEnabled = !glowEnabled;
	}

	if (glowEnabled) {
		renderGlow();
	} else {
		renderBasic();
	}

	glutSwapBuffers();
}

void RailsState::renderBasic() {
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
	Root::textureManager->BindTexture("Grass");
	glslProgram->sendUniform("tex",0);
	glslProgram->sendUniform("material.color", 1.0f, 1.0f, 1.0f);
	glslProgram->sendUniform("material.emission", 0.0f, 0.0f, 0.0f);

	for (float i=0; i<1.0; i += 0.01) {
		for (float j=0; j<1.0; j += 0.01) {
			int xOff = 50*(camera->geteyeX()/50);
			int yOff = 50*(camera->geteyeZ()/50);
			glBegin(GL_QUADS);
			glVertexAttrib2f(1,0.0,0.0); glVertexAttrib3f(0,-50.0+100*i+xOff,0.0,-50.0+100*j+yOff);
			glVertexAttrib2f(1,0.0,1.0); glVertexAttrib3f(0,-50.0+100*i+xOff,0.0,-50.0+100*j+1+yOff);
			glVertexAttrib2f(1,1.0,1.0); glVertexAttrib3f(0,-50.0+100*i+1+xOff,0.0,-50.0+100*j+1+yOff);
			glVertexAttrib2f(1,1.0,0.0); glVertexAttrib3f(0,-50.0+100*i+1+xOff,0.0,-50.0+100*j+yOff);
			glEnd();
		}
	}
	Root::textureManager->BindTexture("White");
	rails->drawRails();
	rails->drawActors();
	glslProgram->disable();

	glutSwapBuffers();

}

void RailsState::renderGlow() {
	glowBuffer->bind();
		GLenum mrt[] = { GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT};
		glDrawBuffers(2, mrt);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushAttrib( GL_VIEWPORT_BIT );
		glViewport( 0, 0, 1280, 720);
		GLSLProgram *glslProgram = Root::shaderManager->getShader("Glow");
		glslProgram->use();

		glBindAttribLocation(glslProgram->getHandle(), 0, "v_vertex");
		glBindAttribLocation(glslProgram->getHandle(), 1, "v_texture");

		camera->transformToMatrix(&Root::ProjectionMatrix.top());
		glslProgram->sendUniform("projectionCameraMatrix", &Root::ProjectionMatrix.top()[0][0]);
		glslProgram->sendUniform("modelviewMatrix", &Root::ModelviewMatrix.top()[0][0]);

		glm::mat4 texMat = glm::mat4(1.0f);
		glslProgram->sendUniform("textureMatrix", &texMat[0][0]);
		glslProgram->sendUniform("camPos",camera->geteyeX(),camera->geteyeY(),camera->geteyeZ());

		glActiveTexture(GL_TEXTURE0);
		Root::textureManager->BindTexture("Grass");
		glslProgram->sendUniform("tex",0);
		glslProgram->sendUniform("material.color", 1.0f, 1.0f, 1.0f);
		glslProgram->sendUniform("material.emission", 0.0f, 0.0f, 0.0f);
		for (float i=0; i<1.0; i += 0.01) {
			for (float j=0; j<1.0; j += 0.01) {
				int xOff = 50*(camera->geteyeX()/50);
				int yOff = 50*(camera->geteyeZ()/50);
				glBegin(GL_QUADS);
				glVertexAttrib2f(1,0.0,0.0); glVertexAttrib3f(0,-50.0+100*i+xOff,0.0,-50.0+100*j+yOff);
				glVertexAttrib2f(1,0.0,1.0); glVertexAttrib3f(0,-50.0+100*i+xOff,0.0,-50.0+100*j+1+yOff);
				glVertexAttrib2f(1,1.0,1.0); glVertexAttrib3f(0,-50.0+100*i+1+xOff,0.0,-50.0+100*j+1+yOff);
				glVertexAttrib2f(1,1.0,0.0); glVertexAttrib3f(0,-50.0+100*i+1+xOff,0.0,-50.0+100*j+yOff);
				glEnd();
			}
		}
		Root::textureManager->BindTexture("White");
		rails->drawRails();
		rails->drawActors();
		glslProgram->disable();
	glowBuffer->unbind();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Root::ModelviewMatrix.top() = glm::mat4(1.0f);
	Root::ProjectionMatrix.top() = glm::mat4(1.0f);
	view->use3D(false);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	view->viewport();
	glOrtho(0,1.0,0,1.0,0,10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_CULL_FACE);

	glBindTexture(GL_TEXTURE_2D, glowBuffer->getEmissionTexture());
	glBegin(GL_QUADS);
		glTexCoord2f(0,0); glVertex3f(0,0,-1.0);
		glTexCoord2f(0,1.0); glVertex3f(0,1.0,-1.0);
		glTexCoord2f(1.0,1.0); glVertex3f(1.0,1.0,-1.0);
		glTexCoord2f(1.0,0); glVertex3f(1.0,0,-1.0);
	glEnd();

}
