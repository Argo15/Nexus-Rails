#include "RailsManager.h"
#include<iostream>
#include<fstream>

RailsManager::RailsManager() {
	railPositions = 0;
	railColors = 0;
	currentRail = 1;
	currentTime = 0;
	startTimes = 0;
}

void RailsManager::reloadRails() {
	ifstream myReadFile;
	myReadFile.open("Data/Rails.txt");
	char output[100];
	int iOutput = 0;
	if (myReadFile.is_open()) {
		myReadFile >> output >> numRails;
		if (railPositions == 0) {
			delete railPositions;
			delete railColors;
			delete startTimes;
		}
		railPositions = new vector<Vector3 *>[numRails];
		railColors = new Vector3*[numRails];
		startTimes = new int[numRails];
		for (int i=0; i<numRails; i++) {
			myReadFile >> output >> iOutput;
			myReadFile >> output >> startTimes[i];
			int color[3];
			int pos[3];
			pos[0] = 0;
			myReadFile >> color[0] >> color[1] >> color[2];
			railColors[i] = new Vector3(color[0], color[1], color[2]);
			while (pos[0] != -10000) {
				myReadFile >> pos[0] >> pos[1] >> pos[2];
				if (pos[0] != -10000) {
					Vector3 *vPos = new Vector3(pos[0], pos[1], pos[2]);
					railPositions[i].push_back(vPos);
				}
			}

		}
	}
}

void RailsManager::drawRails() {
	int numSubDivides = 10.0;
	GLSLProgram *glslProgram = Root::shaderManager->getShader("Basic");
	glLineWidth(10.0);
	for (int i=0; i<numRails; i++) {
		glslProgram->sendUniform("material.color", railColors[i][0][0],railColors[i][0][1],railColors[i][0][2]);

		glBegin(GL_LINE_STRIP);
		for (int x=0; x<railPositions[i].size()-1; x++) {
			for (float p=0.0; p<1.0; p += 1.0/numSubDivides) {
				Vector3 point = railPositions[i][x][0]*(1-p) + railPositions[i][x+1][0]*p;
				glVertex3f(point[0],point[1],point[2]);
			}
		}
		glEnd();

	}
}

// railPositions: Rail, Segment, 0, xyz
// railColors: Rail, 0, rgb

void RailsManager::updateTime(Camera *camera, float dt) {
	if (Root::inputManager->isKeyDownOnce('a') || Root::inputManager->isKeyDownOnce('d')) {
		currentRail -= 1;
		if (currentRail < 0) {
			currentRail = 1;
		}
	}
	currentTime += dt;
	if (currentTime >= railPositions[currentRail].size()-1) {
		currentTime=0;
	}
	int segment = (int)currentTime+startTimes[currentRail];
	if (segment >= railPositions[currentRail].size()-1 ) return;
	Vector3 segStart = railPositions[currentRail][segment][0];
	Vector3 segEnd = railPositions[currentRail][segment+1][0];
	float p = currentTime - (int)currentTime;
	Vector3 position = railPositions[currentRail][segment][0]*(1-p) + railPositions[currentRail][segment+1][0]*p;
	position[1] += 1.0;
	camera->setPosition(position[0],position[1],position[2]);
	camera->recalculate();
}