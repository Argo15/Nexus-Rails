#include "Texture.h"

Texture::Texture()
	: Entity()
{
}

void Texture::use()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::remove()
{
	 glDeleteTextures(1,&textureID);
}