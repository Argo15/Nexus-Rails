#include "RailsManager.h"
#include<iostream>
#include<fstream>

RailsManager::RailsManager() {
	railPositions = 0;
	railColors = 0;
}

void RailsManager::reloadRails() {
	ifstream myReadFile;
	myReadFile.open("Data/Rails.txt");
	char output[100];
	if (myReadFile.is_open()) {
		myReadFile >> output >> numRails;
		if (railPositions == 0) {
			delete railPositions;
			delete railColors;
		}
		railPositions = new vector<Vector3 *>[numRails];
		railColors = new Vector3*[numRails];
		for (int i=0; i<numRails; i++) {
			int color[3];
			myReadFile >> color[0] >> color[1] >> color[2];
			railColors[i] = new Vector3(color[0], color[1], color[2]);
			while (strcmp(output,"END") != 0) {
				int pos[3];
				myReadFile >> pos[0] >> pos[1] >> pos[2];
				Vector3 *vPos = new Vector3(pos[0], pos[1], pos[2]);
				railPositions[i].push_back(vPos);
			}

		}
	}
}

void RailsManager::drawRails() {
	// lol nothing
}