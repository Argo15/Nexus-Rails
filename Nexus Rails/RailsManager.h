#ifndef RAILSMANAGER_H
#define RAILSMANAGER_H

#include "Matrix.h"
#include <vector>
#include "Root.h"
using namespace std;

class RailsManager {
private:
	int numRails;
	vector<Vector3 *> *railPositions;
	Vector3 **railColors;

public:
	RailsManager();
	~RailsManager() {}

	void reloadRails();
	void drawRails();
	Vector3 calculateSplinePoint(float,int,int); 
};

#endif