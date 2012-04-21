#ifndef MATERIAL_H
#define MATERIAL_H

#include <iostream>
#include <fstream>
#include "Entity.h"
#include "TextureManager.h"
#include "Matrix.h"
#include "ShaderManager.h"
using namespace std;

struct SaveMat 
{
	float color[3];
	float emission[3];
	float specular;
	int shininess;

	float texOffset[2];
	float texScale[2];
	float texRotate;

	char name[100];
	char textureName[100];
	char normalName[100];

	bool normalEnabled;
};

class Material : public Entity
{
private:
	float color[3];
	float emission[3];
	float specular;
	int shininess;

	float texOffset[2];
	float texScale[2];
	float texRotate;

	string *textureName;
	string *normalName;

	bool normalEnabled;
public:
	Material();
	Material(Material *copyMaterial) {*this=*copyMaterial;}
	~Material(){}

	void use();
	void sendToShader(string shader);

	void setColor(float r, float g, float b) {color[0]=r;color[1]=g;color[2]=b;}
	void setEmission(float r, float g, float b) {emission[0]=r;emission[1]=g;emission[2]=b;}
	void setSpecular(float i) {specular=i;}
	void setShine(int shine) {shininess=shine;}
	void setTexOffset(float x, float y) {texOffset[0]=x; texOffset[1]=y;}
	void setUTexOffset(float value) {texOffset[0]=value;}
	void setVTexOffset(float value) {texOffset[1]=value;}
	void setTexScale(float x, float y) {texScale[0]=x; texScale[1]=y;}
	void setUTexScale(float value) {texScale[0]=value;}
	void setVTexScale(float value) {texScale[1]=value;}
	void setTexRotate(float rotate) {texRotate=rotate;}

	float *getColor() {return color;}
	float *getEmission() {return emission;}
	float getSpecular() {return specular;}
	int getShine() {return shininess;}
	float *getTexOffset() {return texOffset;}
	float *getTexScale() {return texScale;}
	float getTexRotate() {return texRotate;}

	void setTexture(string *newTextureName) {textureName=newTextureName;}
	string *getTexture() {return textureName;}
	void setNormal(string *newNormalName) {normalName=newNormalName;}
	string *getNormal() {return normalName;}

	void enableNormal(bool enabled) {normalEnabled=enabled;}
	bool normalsEnabled() {return normalEnabled;}

	bool loadMaterial(const char* filename);
};

#endif