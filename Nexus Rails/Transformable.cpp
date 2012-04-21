#include "Transformable.h"

Transformable::Transformable()
{
	for (int i=0;i<3;i++){
		translations[i]=0;
		scale[i]=1.0;
	}
	rotation = Quaternion();
}

void Transformable::transform()
{
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(translations[0],translations[1],translations[2]);
	rotation.getMatrix().multiplyToCurrent();
	glScalef(scale[0],scale[1],scale[2]);
}

void Transformable::transformToMatrix(glm::mat4 *matrix)
{
	glm::mat4 mat = glm::mat4(1.0f);
	mat = glm::translate(mat, glm::vec3(translations[0],translations[1],translations[2]));
	glm::quat rot = glm::quat(rotation[0],rotation[1],rotation[2],rotation[3]);
	mat = mat * glm::mat4_cast(rot);
	mat = glm::scale(mat, glm::vec3(scale[0],scale[1],scale[2]));
	*matrix = (*matrix) * mat;
}

void Transformable::transformToMatrix(glm::mat3 *matrix)
{
	glm::mat3 mat = glm::mat3(1.0f);
	glm::quat rot = glm::quat(rotation[0],rotation[1],rotation[2],rotation[3]);
	mat = mat * glm::mat3_cast(rot);
	*matrix = (*matrix) * mat;
}