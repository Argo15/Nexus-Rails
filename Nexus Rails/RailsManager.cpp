#include "RailsManager.h"
#include<iostream>
#include<fstream>

RailsManager::RailsManager() {

}

void RailsManager::reloadRails() {
	ifstream myReadFile;
	myReadFile.open("Data/Rails.txt");
	char output[100];
	if (myReadFile.is_open()) {
		myReadFile >> output >> numRails;
		railPositions = new vector<Vector3>[numRails];
		railColors = new Vector3[numRails];
		for (int i=0; i<numRails; i++) {
			while (strcmp(output,"END") != 0) {

			}

		}
	}
}

void RailsManager::drawRails() {
	// lol nothing
}