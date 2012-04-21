#ifndef CAMERA_H
#define CAMERA_H

#include <windows.h>
#include <Gl/gl.h>
#include <GL/glu.h>
#include "Matrix.h"
#include "Root.h"

class Camera {
protected:
	float eyePos[3];
	float lookAt[3];
	float up[3];
	float right[3];
	float hAngle;
	float vAngle;
	int lastMouseX, lastMouseY;

	float rotSpeed;

public:
	Camera();
	~Camera(){}

	void setPosition(float x, float y, float z) {eyePos[0]=x;eyePos[1]=y;eyePos[2]=z;}
	void setLookAt(float x, float y, float z) {lookAt[0]=x;lookAt[1]=y;lookAt[2]=z;}
	void setUp(float x, float y, float z) {up[0]=x;up[1]=y;up[2]=z;}
	void setRight(float x, float y, float z) {right[0]=x;right[1]=y;right[2]=z;}
	void setRotSpeed(float speed) {rotSpeed=speed;}
	void transform() {
		Root::ModelviewMatrix.top() = glm::lookAt(
			glm::vec3(eyePos[0],eyePos[1],eyePos[2]),
			glm::vec3(lookAt[0],lookAt[1],lookAt[2]),
			glm::vec3(up[0],up[1],up[2])
		);
	}
	void transformToMatrix(glm::mat4 *matrix) {
		*matrix = *matrix * glm::lookAt(
			glm::vec3(eyePos[0],eyePos[1],eyePos[2]),
			glm::vec3(lookAt[0],lookAt[1],lookAt[2]),
			glm::vec3(up[0],up[1],up[2])
		);
	}

	float geteyeX() {return eyePos[0];}
	float geteyeY() {return eyePos[1];}
	float geteyeZ() {return eyePos[2];}
	float *getEye() {float *peye = eyePos; return peye;}

	Vector3 geteyeV() {return Vector3(eyePos[0],eyePos[1],eyePos[2]);}
	Vector3 getLookAt() {return Vector3(lookAt[0],lookAt[1],lookAt[2]);}
	Vector3 getUp() {return Vector3(up[0],up[1],up[2]);}
	Vector3 getRight() {return Vector3(right[0],right[1],right[2]);}

	void mouseRotate();

	virtual void move(float speed);
	virtual void moveForward(float speed);
	virtual void moveBackward(float speed);
	virtual void moveLeft(float speed);
	virtual void moveRight(float speed);
	virtual void moveUp(float speed);
	virtual void moveDown(float speed);

	void recalculate();
};

#endif
