#ifndef ACTOR_H
#define ACTOR_H

#include <math.h>
#include "Model.h"
#include "Matrix.h"
#include "ModelManager.h"
#include "Transformable.h"
#include "GLSLProgram.h"

class Actor : public Entity, public Transformable {
private:
	string *model;
	string *material;
	
public:
	Actor(string *model = 0, string *material = 0);
	~Actor(){}

	void setModel(string *model) {this->model = model;}
	string *getModel() {return model;}
	void setMaterial(string *material) {this->material = material;}
	string *getMaterial() {return material;}

	float getScaledRadius();

	void drawActor(string shader);
};

#endif