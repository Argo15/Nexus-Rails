#include "DirectLight.h"
#include <windows.h>
#include <gl/glee.h>

DirectLight::DirectLight()
{
	color[0]=1.0f; color[1]=1.0f; color[2]=1.0f;
	ambient=0.5f;
	diffuse=0.5f;
	specular=1.0f;
	direction[0]=0;direction[1]=-1.0f;direction[2]=0;direction[3]=0;
	Quaternion quat;
	quat.createQuaternion(0.9*(2*3.1415),2.0f,0.0f,-1.0f);
	Rotate(quat);
	enabled=true;
}

void DirectLight::setDirection(float x, float y, float z)
{
	direction[0]=x;
	direction[1]=y;
	direction[2]=z;
}

void DirectLight::sendToShader(string shader)
{
	GLSLProgram *glslProgram = Root::shaderManager->getShader(shader);
	glslProgram->use();

	Vector3 dir = getDirection();

	glslProgram->sendUniform("light.direction", dir[0],dir[1],dir[2]);
	glslProgram->sendUniform("light.color", color[0],color[1],color[2]);
	glslProgram->sendUniform("light.ambient", ambient);
	glslProgram->sendUniform("light.diffuse", diffuse);
	glslProgram->sendUniform("light.specular", specular);
	glslProgram->sendUniform("lightenabled", true);
}

Vector3 DirectLight::getDirection()
{
	Vector4 dir(direction[0],direction[1],direction[2],direction[3]);
	Matrix4 rot = this->getRotate().getMatrix();
	Vector4 final = rot*dir;
	return Vector3(final);
}

Vector3 DirectLight::getUp()
{
	Vector4 dir(1.0,0,0,0);
	Matrix4 rot = this->getRotate().getMatrix();
	Vector4 final = rot*dir;
	return Vector3(final);
}

Vector3 DirectLight::getRight()
{
	Vector4 dir(0,0,1.0,0);
	Matrix4 rot = this->getRotate().getMatrix();
	Vector4 final = rot*dir;
	return Vector3(final);
}