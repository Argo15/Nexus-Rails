#include "Frustum.h"

#define ANG2RAD 3.14159265358979323846/180.0

Frustum::Frustum()
{

}

void Frustum::getFrustum(Camera *camera, View *view)
{
	Vector3 p = camera->geteyeV();
	Vector3 d = camera->getLookAt()-p;
	d.normalize();
	Vector3 up = camera->getUp();
	up.normalize();
	Vector3 right = d.cross(up);
	right.normalize();

	float fov = view->getFOV();
	float ratio = view->getAspect();

	float nearDist = view->getNear();
	Hnear = 2 * tan((fov / 2.0)*(3.1415/180)) * nearDist;
	Wnear = Hnear * ratio;

	float farDist = view->getFar();
	Hfar = 2 * tan((fov / 2.0)*(3.1415/180)) * farDist;
	Wfar = Hfar * ratio;
 
	Vector3 fc = p + d * farDist ; 
	Vector3 nc = p + d * nearDist;

	plane[F_NEAR].point=nc;
	plane[F_FAR].point=fc;
	plane[F_LEFT].point=p;
	plane[F_RIGHT].point=p;
	plane[F_UP].point=p;
	plane[F_DOWN].point=p;

	Vector3 a;

	plane[F_NEAR].normal=d*-1.0;
	plane[F_NEAR].normal.normalize();
	plane[F_FAR].normal=d;
	plane[F_FAR].normal.normalize();
	a = (fc - right * (Wfar / 2)) - p;
	a.normalize();
	plane[F_LEFT].normal=up.cross(a);
	plane[F_LEFT].normal.normalize();
	a = (fc + right * (Wfar / 2)) - p;
	a.normalize();
	plane[F_RIGHT].normal=a.cross(up);
	plane[F_RIGHT].normal.normalize();
	a = (fc + up * (Hfar / 2)) - p;
	a.normalize();
	plane[F_UP].normal=right.cross(a);
	plane[F_UP].normal.normalize();
	a = (fc - up * (Hfar / 2)) - p;
	a.normalize();
	plane[F_DOWN].normal=a.cross(right);
	plane[F_DOWN].normal.normalize();

	for (int i=0; i<6; i++)
		plane[i].d=(plane[i].point.dot(plane[i].normal));
}

void Frustum::getOrthoFrustum(Camera *camera, View *view)
{
	Vector3 lookat = (camera->getLookAt()-camera->geteyeV()).normalize();
	Vector3 right = camera->getRight().normalize();
	Vector3 up = camera->getUp().normalize();
	Vector3 center = camera->geteyeV()+lookat*(view->getOrthoFar()-view->getOrthoNear())*0.5;

	plane[F_NEAR].normal=lookat*-1.0;
	plane[F_FAR].normal=lookat;
	plane[F_LEFT].normal=right*-1.0;
	plane[F_RIGHT].normal=right;
	plane[F_UP].normal=up;
	plane[F_DOWN].normal=up*-1.0;
	
	plane[F_NEAR].point=center-lookat*(view->getOrthoDepth()/2.0);
	plane[F_FAR].point=center+lookat*(view->getOrthoDepth()/2.0);
	plane[F_LEFT].point=center-right*(view->getOrthoWidth()/2.0);
	plane[F_RIGHT].point=center+right*(view->getOrthoWidth()/2.0);
	plane[F_UP].point=center+up*(view->getOrthoHeight()/2.0);
	plane[F_DOWN].point=center-up*(view->getOrthoHeight()/2.0);

	for (int i=0; i<6; i++)
		plane[i].d=(plane[i].point.dot(plane[i].normal));
}

bool Frustum::isInFrustum(Vector3 center, float radius)
{
	bool inFrustum=true;
	for (int i=0; i<6; i++){
		float dist = plane[i].distance(&center);
		if (dist>=radius){
			inFrustum=false;
		}
	}
	return inFrustum;
}

void Frustum::calcFarPlane(Camera *camera, View *view)
{
	Vector3 nc,fc,X,Y,Z;

	float tang = (float)tan(ANG2RAD * view->getFOV() * 0.5) ;
	float fh = (view->getFar()-0.005) * tang;
	float fw = fh * view->getAspect();

	X = camera->getRight();
	Y = camera->getUp();
	Z = camera->getLookAt()-camera->geteyeV();
	Z.normalize();

	fc = camera->geteyeV()+Z*(view->getFar()-0.005);

	ftl = fc + Y * fh - X * fw;
	ftr = fc + Y * fh + X * fw;
	fbl = fc - Y * fh - X * fw;
	fbr = fc - Y * fh + X * fw;
}