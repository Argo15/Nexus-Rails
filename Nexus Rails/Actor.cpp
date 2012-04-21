#include "Actor.h"
#include "Root.h"

Actor::Actor(string *model, string *material) : Transformable()
{
	this->model = model;
	this->material = material;
	this->name=name;
}

float Actor::getScaledRadius()
{
	return Root::modelManager->getModel(*model)->getRadius()*max(max(scale[0],scale[1]),scale[2]);
}

void Actor::drawActor(string shader)
{
	GLSLProgram *glslProgram = Root::shaderManager->getShader(shader);
	glslProgram->sendUniform("modelviewMatrix", &Root::ModelviewMatrix.top()[0][0]);
	if (shader == "Basic" || shader == "GBuffer") {
		glslProgram->sendUniform("normalMatrix", &Root::NormalMatrix.top()[0][0],false,3);
		Root::materialManager->getMaterial(*material)->sendToShader(shader);
	}
	Root::modelManager->getModel(*model)->draw();
}