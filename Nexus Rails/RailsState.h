#ifndef RAILSSTATE_H
#define RAILSSTATE_H

#include "GameState.h"
#include "WorldCamera.h"
#include "View.h"
#include "Frustum.h"

class RailsState : public GameState {
private: 
	Frustum *frustum;
	View *view;
	WorldCamera *camera;

public:
	RailsState();
	~RailsState() {}

	void resize(int w, int h);
	void tick(int fps);

	bool mouseHidden() {return false;}

};

#endif