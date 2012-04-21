#ifndef WORLDCAMERA_H
#define WORLDCAMERA_H

#include "Camera.h"

class WorldCamera : public Camera {
private:
	float speedFactor;

public:
	WorldCamera();
	~WorldCamera() {}

	void move(float speed);
	void moveForward(float speed);
	void moveBackward(float speed);
	void moveLeft(float speed);
	void moveRight(float speed);
	void moveUp(float speed) {return;}
	void moveDown(float speed) {return;}
};

#endif