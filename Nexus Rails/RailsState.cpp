#include "RailsState.h"
#include "Root.h"

RailsState::RailsState() : GameState() {
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glClearColor(0.0f, 0.0f, 0.03f, 1.0f);
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
	cameraMode = false;
	rails->reloadRails();
	clock = 0;
	glowEnabled = true;
	glowBuffer = new FBO();

	Root::MUSICPLAYER->init();
	//Root::MIDIPLAYER->init();
	generateSky();
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
		//rails->reloadRails();
	}
	Root::ModelviewMatrix.top() = glm::mat4(1.0f);
	Root::ProjectionMatrix.top() = glm::mat4(1.0f);

	if (cameraMode) {
		camera->move(180/fps);
	} else {
		camera->move(180/fps);
		rails->updateTime(camera,0.6/fps);
	}
	if (Root::inputManager->isKeyDownOnce('2')) {
		cameraMode = !cameraMode;
	}
	view->use3D(true);

	if (Root::inputManager->isKeyDownOnce('1')) {
		glowEnabled = !glowEnabled;
	}

	if (glowEnabled) {
		renderGlow(fps);
	} else {
		renderBasic(fps);
	}

	glutSwapBuffers();
}

void RailsState::generateSky() {
	numStars = 1000;
	stars = new Vector3[numStars];

	for (int i=0; i<numStars; i++) {
		float x = (float)rand()/(float)RAND_MAX;
		float y = (float)rand()/(float)RAND_MAX;
		float z = (float)rand()/(float)RAND_MAX;
		stars[i] = Vector3(x*200-100,y*20+200,z*200-100);
	}
}

void RailsState::drawSky(GLSLProgram *glslProgram, int fps) {
	glslProgram->sendUniform("material.color", 1.0f, 1.0f, 1.0f);
	glslProgram->sendUniform("material.emission", 1.0f, 1.0f, 1.0f);
	Vector3 camPos = camera->geteyeV();
	int xPos = (camPos[0]+100)-((int)camPos[0]+100)%200;
	int zPos = (camPos[2]+100)-((int)camPos[2]+100)%200;
	int count = numStars;
	for (int i=0; i<count; i++) {
		Vector3 currentStar = stars[i]+Vector3(xPos,0,zPos);
		glPointSize(2);
		Vector3 diff = Vector3(camPos-currentStar);
		diff[1]=0;
		glBegin(GL_POINTS);
			if (diff.length() < 90) glVertexAttrib3f(0,currentStar[0],		currentStar[1],currentStar[2]);
			diff[0]-=200;
			if (diff.length() < 90) glVertexAttrib3f(0,currentStar[0]+200,	currentStar[1],currentStar[2]);
			diff[0]+=200; diff[2]-=200;
			if (diff.length() < 90) glVertexAttrib3f(0,currentStar[0],		currentStar[1],currentStar[2]+200);
			diff[0]+=200; diff[2]+=200;
			if (diff.length() < 90) glVertexAttrib3f(0,currentStar[0]-200,	currentStar[1],currentStar[2]);
			diff[0]-=200; diff[2]+=200;
			if (diff.length() < 90) glVertexAttrib3f(0,currentStar[0],		currentStar[1],currentStar[2]-200);
		glEnd();
	}
}

void RailsState::renderBasic(int fps) {
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
	Root::textureManager->BindTexture("Ground");
	glslProgram->sendUniform("tex",0);
	Vector3 color = rails->getRailColor();
	glslProgram->sendUniform("material.color", color[0], color[1], color[2]);
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
	rails->drawRails(camera);
	drawSky(glslProgram, fps);
	rails->drawActors(camera, "Basic");
	rails->drawGrade(camera, "Basic");
	glslProgram->disable();

}

void RailsState::renderGlow(int fps) {
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
		Root::textureManager->BindTexture("Ground");
		glslProgram->sendUniform("tex",0);
		Vector3 color = rails->getRailColor();
		glslProgram->sendUniform("material.color", color[0], color[1], color[2]);
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
		rails->drawRails(camera);
		drawSky(glslProgram, fps);
		rails->drawActors(camera, "Glow");
		rails->drawGrade(camera, "Glow");
		glslProgram->disable();
	glowBuffer->unbind();

	glslProgram = Root::shaderManager->getShader("Final");
	glslProgram->use();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Root::ModelviewMatrix.top() = glm::mat4(1.0f);
	Root::ProjectionMatrix.top() = glm::mat4(1.0f);
	view->use3D(false);
	glslProgram->sendUniform("projectionMatrix", &Root::ProjectionMatrix.top()[0][0]);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	view->viewport();
	glOrtho(0,1.0,0,1.0,0,10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_CULL_FACE);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, glowBuffer->getColorTexture());
	glslProgram->sendUniform("colorTex",0);
	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, glowBuffer->getEmissionTexture());
	glslProgram->sendUniform("emissionTex",1);

	glBindAttribLocation(glslProgram->getHandle(), 0, "v_vertex");
	glBindAttribLocation(glslProgram->getHandle(), 1, "v_texture");
	
	glBegin(GL_QUADS);
		glVertexAttrib2f(1,0,0);	glVertexAttrib3f(0,0,0,-1.0);
		glVertexAttrib2f(1,0,1.0);	glVertexAttrib3f(0,0,1.0,-1.0);
		glVertexAttrib2f(1,1.0,1.0);glVertexAttrib3f(0,1.0,1.0,-1.0);
		glVertexAttrib2f(1,1.0,0);	glVertexAttrib3f(0,1.0,0,-1.0);
	glEnd();

	glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_CULL_FACE);

	glslProgram->disable();
}
