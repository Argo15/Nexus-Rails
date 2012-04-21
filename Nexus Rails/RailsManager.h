#ifndef RAILSMANAGER_H
#define RAILSMANAGER_H

#include "Matrix.h"
#include <vector>
#include "Root.h"
#include "Camera.h"
using namespace std;

class RailsManager {
private:
	int numRails;
	vector<Vector3 *> *railPositions;
	Vector3 **railColors;
	int *startTimes;

	float currentTime;	// Time = num segments since start of rail 0
	int currentRail;	// Starts on 0

public:
	RailsManager();
	~RailsManager() {}

	void updateTime(Camera *camera, float dt);
	void reloadRails();
	void drawRails();
};

#endif