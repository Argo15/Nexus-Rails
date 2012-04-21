#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include "Matrix.h"

class Transformable {
protected:
	float translations[3];
	Quaternion rotation;
	float scale[3];

public:
	Transformable();

	void Translate(float x, float y, float z) {translations[0]+=x;translations[1]+=y;translations[2]+=z;}
	void Rotate(Quaternion quat) {rotation=quat*rotation;}
	void Scale(float x, float y, float z) {scale[0]+=x;scale[1]+=y;scale[2]+=z;}
	void setTranslate(float x, float y, float z) {translations[0]=x;translations[1]=y;translations[2]=z;}
	void setRotate(Quaternion quat) {rotation = quat;}
	void setScale(float x, float y, float z) {scale[0]=x;scale[1]=y;scale[2]=z;}
	float *getTranslate() {float *pTranslate; pTranslate=translations; return pTranslate;}
	Quaternion getRotate() {return rotation;}
	float *getScale() {float *pScale; pScale=scale; return pScale;}
	Vector3 getTranslateV() {return Vector3(translations[0],translations[1],translations[2]);}

	void transform();
	void transformToMatrix(glm::mat4 *matrix);
	void transformToMatrix(glm::mat3 *matrix);
};

#endif