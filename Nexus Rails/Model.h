#ifndef MODEL_H
#define MODEL_H

#include "Entity.h"
#include <windows.h>
#include <GL/gl.h>
#undef __glext_h_
#undef __glxext_h_
#undef __gl_h_
#include <GL/GLee.h>

class Model : public Entity
{
protected:
	int numTriangles;
	float center[3];
	float radius;

public:
	Model(){}
	~Model(){}
	virtual bool load(string filename) = 0;
	virtual void draw() = 0;
	virtual void remove() = 0;

	int getNumTriangles(){return numTriangles;}
	float *getCenter() {return center;}
	float getRadius() {return radius;}
	
};

#endif