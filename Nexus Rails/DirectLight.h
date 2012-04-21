#ifndef DIRECTLIGHT_H
#define DIRECTLIGHT_H

#include <string>
#include "Transformable.h"
#include "Light.h"
#include "GLSLProgram.h"
#include "Root.h"
using namespace std;

class DirectLight : public Light, public Transformable {
private:
	float direction[4];

public:
	DirectLight();
	~DirectLight(){}

	void sendToShader(string shader);
	void setDirection(float x, float y, float z);
	Vector3 getDirection();
	Vector3 getUp();
	Vector3 getRight();
};

#endif