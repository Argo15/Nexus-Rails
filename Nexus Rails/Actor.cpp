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
	glslProgram->sendUniform("material.emission", 0.0f, 0.0f, 0.0f);
	glActiveTextureARB(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	Root::textureManager->BindTexture(*material);
	Root::modelManager->getModel(*model)->draw();
}