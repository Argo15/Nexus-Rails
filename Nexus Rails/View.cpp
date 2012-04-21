#include "View.h"
#include "Matrix.h"
#include "Root.h"

void View::use3D(bool use3D){
    if (use3D)
		Root::ProjectionMatrix.top() = glm::perspective(fovy, aspect, zNear, zFar);
    else
		Root::ProjectionMatrix.top() = glm::ortho(left, right, bottom, top, front, back);
}

void View::set3D(GLdouble _fovy, GLdouble _aspect, GLdouble _zNear, GLdouble _zFar){
	fovy=_fovy;
    aspect=_aspect;
    zNear=_zNear;
    zFar=_zFar;
}

void View::set2D(GLdouble _left, GLdouble _right, GLdouble _bottom, GLdouble _top, GLdouble _front, GLdouble _back){
        left=_left;
        right=_right;
        bottom=_bottom;
        top=_top;
        front=_front;
        back=_back;
}