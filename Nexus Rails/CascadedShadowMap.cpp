#include "CascadedShadowMap.h"

#define ANG2RAD 3.14159265358979323846/180.0

CascadedShadowMap::CascadedShadowMap(int size, float slice1, float slice2, float slice3)
{
	for (int i=0;i<4;i++) {
		shadowMaps[i] = new DepthBuffer(size,size);
	}
	slices[0] = slice1;
	slices[1] = slice2;
	slices[2] = slice3;

	this->size = size;
}

void CascadedShadowMap::buildShadowMaps()
{
	float slice[] = {0.0, slices[0], slices[1], slices[2], 1.0};
	WorldState *worldState = (WorldState *) Root::GAMESTATE;
	Camera *camera = worldState->getPhysicsManager()->getWorldCameras()->getCurrentCamera();
	View *view = worldState->getRenderer()->getView();
	Frustum *frustum = worldState->getRenderer()->getFrustum();
	DirectLight *sun = worldState->getWorldManager()->getSun();

	shadowMaps[3]->bind();
	glClearDepth(1.0);
	glClear(GL_DEPTH_BUFFER_BIT);

	for (int i=0; i<3; i++) {
		Camera *lightCamera = createLightCamera(slice[i],slice[i+1],camera,view,sun);
		View *lightView = createLightView(slice[i],slice[i+1],camera,lightCamera,view,frustum);
		Frustum *lightFrustum = new Frustum();
		lightFrustum->getOrthoFrustum(lightCamera,lightView);

		Root::ModelviewMatrix.push(glm::mat4(1.0f)); 
		Root::ProjectionMatrix.push(glm::mat4(1.0f));
		
		shadowMaps[i]->bind();
		glClearDepth(1.0);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_DEPTH_BUFFER_BIT);
		glPushAttrib( GL_VIEWPORT_BIT );
		glViewport( 0, 0, size, size);
		lightView->use3D(false);
		glm::mat4 cameraMat = glm::mat4(1.0f);
		lightCamera->transformToMatrix(&cameraMat);
		lightMatrix[i] = Root::ProjectionMatrix.top() * cameraMat;
		GLSLProgram *glslProgram = Root::shaderManager->getShader("SunShadow");
		glslProgram->use();
		Root::ProjectionMatrix.top() *= cameraMat;
		glslProgram->sendUniform("projectionCameraMatrix",&Root::ProjectionMatrix.top()[0][0]);
		glslProgram->sendUniform("camPos",camera->geteyeX(),camera->geteyeY(),camera->geteyeZ());
		glBindAttribLocation(glslProgram->getHandle(), 0, "v_vertex");

		if (i<3) {
			worldState->getWorldManager()->renderWorld("SunShadow",lightFrustum);
		}
		
		glslProgram->disable();
		glPopAttrib();
		shadowMaps[i]->unbind();


		delete lightCamera;
		delete lightView;
		delete lightFrustum;
	}
	
}

Camera *CascadedShadowMap::createLightCamera(float slice1, float slice2, Camera *camera, View *view, DirectLight *dLight)
{
	Vector3 lightLookAt = dLight->getDirection();
	Vector3 lightRight = dLight->getRight();
	Vector3 lightUp = dLight->getUp();
	float viewDepth = (float)(view->getNear()+(view->getFar()-view->getNear())*(slice2+slice1)/2.0);
	Vector3 cameraDir = camera->getLookAt()-camera->geteyeV();
	cameraDir.normalize();
	Vector3 lightLookPoint = camera->geteyeV()+cameraDir*viewDepth;
	Vector3 lightPos = lightLookPoint-lightLookAt*25.0;
	Camera *lightCamera = new Camera();
	lightCamera->setPosition(lightPos[0],lightPos[1],lightPos[2]);
	lightCamera->setLookAt(lightLookPoint[0],lightLookPoint[1],lightLookPoint[2]);
	lightCamera->setUp(lightUp[0],lightUp[1],lightUp[2]);
	lightCamera->setRight(lightRight[0],lightRight[1],lightRight[2]);
	return lightCamera;
}

View *CascadedShadowMap::createLightView(float slice1, float slice2, Camera *camera, Camera *lightCamera, View *view, Frustum *frustum)
{
	glm::vec3 ntl,ntr,nbl,nbr,ftl,ftr,fbl,fbr,nc,fc,X,Y,Z;

	float nearDepth = (float)(view->getNear()+(view->getFar()-view->getNear())*slice1);
	float farDepth = (float)(view->getNear()+(view->getFar()-view->getNear())*slice2);

	float nh = (frustum->getHNear()+(frustum->getHFar()-frustum->getHNear())*slice1)/2.0f;
	float nw = (frustum->getWNear()+(frustum->getWFar()-frustum->getWNear())*slice1)/2.0f; 
	float fh = (frustum->getHNear()+(frustum->getHFar()-frustum->getHNear())*slice2)/2.0f;
	float fw = (frustum->getWNear()+(frustum->getWFar()-frustum->getWNear())*slice2)/2.0f;

	glm::vec3 cameraRight(camera->getRight()[0], camera->getRight()[1], camera->getRight()[2]);
	glm::vec3 cameraUp(camera->getUp()[0], camera->getUp()[1], camera->getUp()[2]);
	glm::vec3 cameraLookAt(camera->getLookAt()[0],camera->getLookAt()[1],camera->getLookAt()[2]);
	glm::vec3 cameraEye(camera->geteyeV()[0],camera->geteyeV()[1],camera->geteyeV()[2]);

	X = cameraRight;
	X = glm::normalize(X);
	Y = cameraUp;
	Y = glm::normalize(Y);
	Z = cameraLookAt - cameraEye;
	Z = glm::normalize(Z);

	nc = cameraEye+Z*nearDepth;
	fc = cameraEye+Z*farDepth;

	ntl = nc + Y * nh - X * nw;
	ntr = nc + Y * nh + X * nw;
	nbl = nc - Y * nh - X * nw;
	nbr = nc - Y * nh + X * nw;
	ftl = fc + Y * fh - X * fw;
	ftr = fc + Y * fh + X * fw;
	fbl = fc - Y * fh - X * fw;
	fbr = fc - Y * fh + X * fw;

	// calculate the actual bounds for the ortho projection
	glm::mat4 lightMVP;
	lightMVP = glm::ortho(-1,1,-1,1,0,1);
	lightCamera->transformToMatrix(&lightMVP);

	float left, right, up, down, back;

	glm::vec4 corners[] = {glm::vec4(ntl,1.0f), glm::vec4(ntr,1.0f), glm::vec4(nbl,1.0f), glm::vec4(nbr,1.0f),
							glm::vec4(ftl,1.0f), glm::vec4(ftr,1.0f), glm::vec4(fbl,1.0f), glm::vec4(fbr,1.0f)};

	// get the projected positions of the corners
	for (int i=0; i<8; i++){
		corners[i]=lightMVP*corners[i];
	}


	left  = corners[0][0];
	right = corners[0][0];
	up    = corners[0][1];
	down  = corners[0][1];
	back  = corners[0][2];

	// determine the bounds
	for (int i=1; i<8; i++){
		if (corners[i][0]<left)
			left=corners[i][0];
		if (corners[i][0]>right)
			right=corners[i][0];
		if (corners[i][1]<down)
			down=corners[i][1];
		if (corners[i][1]>up)
			up=corners[i][1];
		if (corners[i][2]>back)
			back=corners[i][2];
	}

	View *lightView = new View();
	lightView->set2D(left,right,down,up,0.1,50);
	return lightView;
}

void CascadedShadowMap::sendToShader(string shader)
{
	GLSLProgram *glslProgram = Root::shaderManager->getShader(shader);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D,shadowMaps[0]->getTexture());
	glslProgram->sendUniform("shadowMap[0]",4);
	glActiveTexture(GL_TEXTURE5);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,shadowMaps[1]->getTexture());
	glslProgram->sendUniform("shadowMap[1]",5);
	glActiveTexture(GL_TEXTURE6);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,shadowMaps[2]->getTexture());
	glslProgram->sendUniform("shadowMap[2]",6);
	glActiveTexture(GL_TEXTURE7);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,shadowMaps[3]->getTexture());
	glslProgram->sendUniform("shadowMap[3]",7);

	glslProgram->sendUniform("slices[0]",slices[0]);
	glslProgram->sendUniform("slices[1]",slices[1]);
	glslProgram->sendUniform("slices[2]",slices[2]);

	lightMatrix[0] = glm::translate(glm::mat4(1.0f),glm::vec3(0.5f,0.5f,0.5f)) * glm::scale(glm::mat4(1.0f),glm::vec3(0.5f,0.5f,0.5f)) * lightMatrix[0];
	lightMatrix[1] = glm::translate(glm::mat4(1.0f),glm::vec3(0.5f,0.5f,0.5f)) * glm::scale(glm::mat4(1.0f),glm::vec3(0.5f,0.5f,0.5f)) * lightMatrix[1];
	lightMatrix[2] = glm::translate(glm::mat4(1.0f),glm::vec3(0.5f,0.5f,0.5f)) * glm::scale(glm::mat4(1.0f),glm::vec3(0.5f,0.5f,0.5f)) * lightMatrix[2];
	lightMatrix[3] = glm::translate(glm::mat4(1.0f),glm::vec3(0.5f,0.5f,0.5f)) * glm::scale(glm::mat4(1.0f),glm::vec3(0.5f,0.5f,0.5f)) * lightMatrix[3];

	glslProgram->sendUniform("lightMatrix[0]", &lightMatrix[0][0][0]);
	glslProgram->sendUniform("lightMatrix[1]", &lightMatrix[1][0][0]);
	glslProgram->sendUniform("lightMatrix[2]", &lightMatrix[2][0][0]);
	glslProgram->sendUniform("lightMatrix[3]", &lightMatrix[3][0][0]);
}

void CascadedShadowMap::drawShadowMaps()
{

}