#ifndef STATICMODEL_H
#define STATICMODEL_H

#include "Model.h"
#include <string>
using namespace std;

class StaticModel : public Model
{
protected:
	GLuint bufferID;
public:
	StaticModel(){}
	~StaticModel(){}
	virtual bool load(string filename) = 0;
	void remove() { glDeleteBuffersARB(1, &bufferID); }
	void draw();
	void drawSelection();
};

#endif