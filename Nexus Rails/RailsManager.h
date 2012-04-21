#ifndef RAILSMANAGER_H
#define RAILSMANAGER_H

#include "Matrix.h"
#include <vector>
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
};

#endif