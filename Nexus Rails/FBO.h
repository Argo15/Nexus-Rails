#ifndef FBO_H
#define FBO_H

#include <windows.h>
#include <gl/glee.h>
#include <iostream>
#include <GL/freeglut.h>

class FBO {
private:
	GLuint depthTex;
	GLuint color;
	GLuint emission;
	GLuint buffer;

public:
	FBO();
	~FBO() {}

	void bind() {glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, buffer);}
	void unbind() {glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);}
	GLuint getBuffer() {return buffer;}
	GLuint getColorTexture() {return color;}
	GLuint getEmissionTexture() {return emission;}

};

#endif