#ifndef LIGHT_H
#define LIGHT_H

#include <string>
using namespace std;

class Light {
protected:
	float color[3];
	float ambient;
	float diffuse;
	float specular;
	bool enabled;

public:
	void setAmbient(float amt) {ambient=amt;}
	void setDiffuse(float amt) {diffuse=amt;}
	void setSpecular(float amt) {specular=amt;}
	float getDiffuse() {return diffuse;}
	float getAmbient() {return ambient;}
	float getSpecular() {return specular;}

	void setColor(float r, float g, float b) {color[0]=r; color[1]=g; color[2]=b;}
	float *getColor() {return color;}

	bool isenabled() {return enabled;}
	void setEnabled(bool enabled) {this->enabled=enabled;}

	virtual void sendToShader(string shader) = 0;
};

#endif