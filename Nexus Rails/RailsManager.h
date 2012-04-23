#ifndef RAILSMANAGER_H
#define RAILSMANAGER_H

#include "Matrix.h"
#include <vector>
#include "Root.h"
#include "Camera.h"
#include "Actor.h"
using namespace std;

struct Connection {
	int first;
	int second;
	int hash() { return 1000*first+second; }
};

class RailsManager {
private:
	int numRails;
	vector<Vector3 *> *railPositions;
	vector<Vector3 *> *bsplinePositions;
	Vector3 **railColors;
	int *startTimes;
	vector<Connection> *connections;
	vector<Actor *> *actors;

	Vector3 transitionPos;
	float transitionPercent;

	Vector3 lastPosition;
	Vector3 lastLook;

	float speed;
	bool flickerFix;

	float currentTime;	// Time = num segments since start of rail 0
	int currentRail;	// Starts on 0
	int previousRail;
	void loadRails();

public:
	RailsManager();
	~RailsManager() {}

	void updateTime(Camera *camera, float dt);
	void reloadRails();
	void drawRails(Camera *camera);
	void drawActors(Camera *camera, string shader);
	Vector3 calculateSplinePoint(float,int,int); 
	Vector3 getRailColor();
};

#endif