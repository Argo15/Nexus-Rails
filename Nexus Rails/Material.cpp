#include "Material.h"
#include "Root.h"
#include <fstream>

Material::Material()
	: Entity()
{
	for (int i=0;i<3;i++){
		color[i]=1.0;
		emission[i]=0.0;
	}
	texOffset[0]=0.0;
	texOffset[1]=0.0;
	texScale[0]=1.0;
	texScale[1]=1.0;
	texRotate=0.0;
	specular=0.0;
	shininess=25;
	normalName=Root::textureManager->getTexture("White")->getName();
	normalEnabled=false;
}

void Material::use()
{
	float spec[] = {specular, specular, specular};
	glDisable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,color);
	glMaterialfv(GL_FRONT,GL_AMBIENT,color);
	glMaterialfv(GL_FRONT,GL_SPECULAR,spec);
	glMateriali(GL_FRONT,GL_SHININESS,shininess);
	glMaterialfv(GL_FRONT,GL_EMISSION,emission);
	glMatrixMode(GL_TEXTURE);
	glActiveTextureARB(GL_TEXTURE0);
	glLoadIdentity();
	glTranslatef(texOffset[0],texOffset[1],0.0);
	glRotatef(texRotate,0.0,0.0,1.0);
	glScalef(texScale[0],texScale[1],1.0);
	glMatrixMode(GL_MODELVIEW);

	glActiveTextureARB(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	Root::textureManager->BindTexture(*textureName);
}

void Material::sendToShader(string shader)
{
	GLSLProgram *glslProgram = Root::shaderManager->getShader(shader);
	glActiveTextureARB(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	Root::textureManager->BindTexture(*textureName);
	glActiveTextureARB(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	Root::textureManager->BindTexture(*normalName);
	glslProgram->sendUniform("tex", 0);
	glslProgram->sendUniform("normalmap", 1);
	glslProgram->sendUniform("material.normalenabled", normalEnabled);
	glslProgram->sendUniform("material.color", color[0],color[1],color[2]);
	if (shader == "GBuffer") {
		glslProgram->sendUniform("material.emission", emission[0],emission[1],emission[2]);
		glslProgram->sendUniform("material.specular", specular);
		glslProgram->sendUniform("material.shininess", (float)shininess/128.0f);
	}
	glm::mat4 textureMatrix = glm::mat4(1.0f);
	textureMatrix = glm::translate(textureMatrix, glm::vec3(texOffset[0],texOffset[1],0));
	textureMatrix = glm::rotate(textureMatrix, texRotate, glm::vec3(0,0,1.0));
	textureMatrix = glm::scale(textureMatrix, glm::vec3(texScale[0],texScale[1],1.0));
	glslProgram->sendUniform("textureMatrix", &textureMatrix[0][0]);
}

bool Material::loadMaterial(const char* filename) 
{
	SaveMat load;

	ifstream file(filename, ios::in|ios::binary|ios::ate);
	if (file.is_open())
	{ 
		file.seekg (0, ios::beg);
		file.read((char*)&load,sizeof(load));
	} else { return false; }
	file.close();

	for (int i=0; i<3; i++) {
		color[i] = load.color[i];
		emission[i] = load.emission[i];
	}
	for (int i=0; i<2; i++) {
		texOffset[i] = load.texOffset[i];
		texScale[i] = load.texScale[i];
	}
	specular = load.specular;
	shininess = load.shininess;
	texRotate = load.texRotate;
	normalEnabled = load.normalEnabled;

	name = new string(load.name);
	textureName = new string(load.textureName);
	normalName = new string(load.normalName);
	return true;
}