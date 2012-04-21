#include "Camera.h"
#include "Root.h"
#include <GL/freeglut.h>
#include <math.h>

#define PI (3.141592653589793)

Camera::Camera()
{
	hAngle=-(float)PI/4.0f;
    vAngle=(float)PI/4.0f;
	eyePos[0]=5.0; eyePos[1]=5.0; eyePos[2]=5.0; 
	recalculate();
	rotSpeed=0.8;
	lastMouseX = -1;
	lastMouseY = -1;
}

void Camera::mouseRotate()
{
	if (!Root::inputManager->isMouseButtonDown(2)) {
		lastMouseX = -1;
		return;
	}
	int mouseX=Root::inputManager->getMouseX();
	int mouseY=Root::inputManager->getMouseY();

	if (lastMouseX == -1) {
		lastMouseX = mouseX;
		lastMouseY = mouseY;
		return;
	}

	int dx = mouseX - lastMouseX;
	int dy = mouseY - lastMouseY;

	hAngle-=(float)dx*rotSpeed*0.005f;
	vAngle+=(float)dy*rotSpeed*0.005f;

	if (vAngle>0.999f*PI/2.0f)
        vAngle=0.999f*(float)PI/2.0f;
    if (vAngle<-0.999f*PI/2.0f)
        vAngle=-0.999f*(float)PI/2.0f;

	recalculate();

	lastMouseX = mouseX;
	lastMouseY = mouseY;
	
	if (Root::GAMESTATE->mouseHidden()) {
		if (mouseX>500) {
			glutWarpPointer(300, mouseY);
			lastMouseX = 300;
		}
		if (mouseX<300) {
			glutWarpPointer(500, mouseY);
			lastMouseX = 500;
		}
		if (mouseY>500) {
			glutWarpPointer(mouseX, 300);
			lastMouseY = 300;
		}
		if (mouseY<300) {
			glutWarpPointer(mouseX, 500);
			lastMouseY = 500;
		}
	}
}

void Camera::move(float speed)
{
	if (Root::inputManager->isKeyDown('w'))
		moveForward(speed*0.1f);
	if (Root::inputManager->isKeyDown('s'))
		moveBackward(speed*0.1f);
	if (Root::inputManager->isKeyDown('a'))
		moveLeft(speed*0.1f);
	if (Root::inputManager->isKeyDown('d'))
		moveRight(speed*0.1f);
	if (Root::inputManager->isKeyDown('e'))
		moveUp(speed*0.1f);
	if (Root::inputManager->isKeyDown('q'))
		moveDown(speed*0.1f);

	mouseRotate();
}

void Camera::moveForward(float speed)
{
	eyePos[0]-=cos(hAngle)*speed;
	eyePos[2]+=sin(hAngle)*speed;
	lookAt[0]-=cos(hAngle)*speed;
	lookAt[2]+=sin(hAngle)*speed;
}

void Camera::moveBackward(float speed)
{
	eyePos[0]+=cos(hAngle)*speed;
	eyePos[2]-=sin(hAngle)*speed;
	lookAt[0]+=cos(hAngle)*speed;
	lookAt[2]-=sin(hAngle)*speed;
}

void Camera::moveLeft(float speed)
{
	eyePos[2]+=cos(hAngle)*speed;
	eyePos[0]+=sin(hAngle)*speed;
	lookAt[2]+=cos(hAngle)*speed;
	lookAt[0]+=sin(hAngle)*speed;
}

void Camera::moveRight(float speed)
{
	eyePos[2]-=cos(hAngle)*speed;
	eyePos[0]-=sin(hAngle)*speed;
	lookAt[2]-=cos(hAngle)*speed;
	lookAt[0]-=sin(hAngle)*speed;
}

void Camera::moveUp(float speed)
{
	eyePos[1]+=speed;
	lookAt[1]+=speed;
}

void Camera::moveDown(float speed)
{
	eyePos[1]-=speed;
	lookAt[1]-=speed;
}

void Camera::recalculate()
{
	lookAt[0]=eyePos[0]-cos(hAngle)*abs(cos(vAngle));
	lookAt[1]=eyePos[1]-sin(vAngle);
	lookAt[2]=eyePos[2]+sin(hAngle)*abs(cos(vAngle));
	up[0]=cos(hAngle)*cos(vAngle+(float)PI/2);
	up[1]=sin(vAngle+(float)PI/2);
	up[2]=-sin(hAngle)*cos(vAngle+(float)PI/2);
	Vector3 vLook(lookAt[0]-eyePos[0],lookAt[1]-eyePos[1],lookAt[2]-eyePos[2]);
	Vector3 vUp(up[0],up[1],up[2]);
	Vector3 vRight = vLook.cross(vUp);
	vRight.normalize();
	right[0]=vRight[0];
	right[1]=vRight[1];
	right[2]=vRight[2];
}