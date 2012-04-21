#ifndef VIEW_H
#define VIEW_H

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

class View{
private:
	double fovy, aspect, zNear, zFar;
	double left, right, top, bottom, front, back;
	int width, height;
public:
	View(){}
	~View(){}

	void use3D(bool use3D);
	void set3D(GLdouble _fovy, GLdouble _aspect, GLdouble _zNear, GLdouble _zFar);
	void set2D(GLdouble _left, GLdouble _right, GLdouble _bottom, GLdouble _top, GLdouble front, GLdouble back);
	void viewport() {glViewport(0,0,width,height);}
	void viewport(int x, int y, int width, int height) {this->width = width; this->height = height; glViewport(x,y,width,height);}

	double getFOV() {return fovy;}
	double getAspect() {return aspect;}
	double getNear() {return zNear;}
	double getFar() {return zFar;}

	double getOrthoWidth() {return right-left;}
	double getOrthoHeight() {return top-bottom;}
	double getOrthoDepth() {return back-front;}
	double getOrthoNear() {return front;}
	double getOrthoFar() {return back;}
};

#endif