#ifndef RAILSSTATE_H
#define RAILSSTATE_H

#include "GameState.h"
#include "WorldCamera.h"
#include "View.h"
#include "Frustum.h"
#include <GL/freeglut.h>
#include "RailsManager.h"
#include "Transformable.h"
#include "Actor.h"
#include "FBO.h"

class RailsState : public GameState {
private: 
	Frustum *frustum;
	View *view;
	Camera *camera;
	RailsManager *rails;

	float clock;

	bool cameraMode;
	bool glowEnabled;
	FBO *glowBuffer;

	int numStars;
	Vector3 *stars;

	void renderBasic(int fps);
	void renderGlow(int fps);

	void generateSky();
	void drawSky(GLSLProgram *glslProgram, int fps);

public:
	RailsState();
	~RailsState() {}

	void resize(int w, int h);
	void tick(int fps);

	bool mouseHidden() {return false;}

};

#endif