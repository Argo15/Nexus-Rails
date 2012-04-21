#include "RailsManager.h"
#include "Matrix.h"
#include<iostream>
#include<fstream>
#include<math.h>
using namespace std;

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
	//int numSubDivides = 10.0;
	GLSLProgram *glslProgram = Root::shaderManager->getShader("Basic");
	//glLineWidth(10.0);
	//for (int i=0; i<numRails; i++) {
	//glslProgram->sendUniform("material.color", railColors[i][0][0],railColors[i][0][1],railColors[i][0][2]);

	//glBegin(GL_LINE_STRIP);
	//for (int x=0; x<railPositions[i].size()-1; x++) {
	//for (float p=0.0; p<1.0; p += 1.0/numSubDivides) {
	//Vector3 point = railPositions[i][x][0]*(1-p) + railPositions[i][x+1][0]*p;
	//glVertex3f(point[0],point[1],point[2]);
	//}
	//}
	//glEnd();
	glLineWidth(10.0);
	for (int railID=0; railID<numRails; railID++) {
		glslProgram->sendUniform("material.color", railColors[railID][0][0],railColors[railID][0][1],railColors[railID][0][2]);
		int npts = railPositions[1].size()-1;
		int nsegment = 32;
		Vector3 pts[33];
		glBegin(GL_LINE_STRIP);
		for(int startingPoint =0 ; startingPoint < npts;startingPoint++)
		{
			for(int i =0; i<=nsegment; i++)
			{
				if(startingPoint >= npts-3)
				{
					break;
				}
				float t = (float)i/nsegment;
				//System.out.println("t "+t);
				pts[i] = calculateSplinePoint(t,railID,startingPoint);
				glVertex3f(pts[i][0],pts[i][1],pts[i][2]);
				//cout<<pts[i][0]<<" "<<pts[i][1]<<" "<<pts[i][2]<<endl;
			}
		}


		//glBegin(GL_LINE_STRIP);
		//for(int r =5;r<30;r++)
		//{
		//	glVertex3f(pts[r][0],pts[r][1],pts[r][2]);
		//}
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
	int segment = (int)currentTime;
	if (segment < 0 || segment >= railPositions[currentRail].size()-4) return;
	float p = currentTime - (int)currentTime;
	Vector3 position = calculateSplinePoint(p, currentRail, segment);
	position[1] += 1.0;
	camera->setPosition(position[0],position[1],position[2]);
	camera->recalculate();
}




Vector3 RailsManager::calculateSplinePoint(float t, int railID, int startingPoint)
{
	int npts = railPositions[railID].size()-1;

	Vector3 point0;
	Vector3 point1;
	Vector3 point2;
	Vector3 point3;

	if(startingPoint <= npts)
	{
		point0 = Vector3(railPositions[railID][startingPoint][0][0],railPositions[railID][startingPoint][0][1],railPositions[railID][startingPoint][0][2]);
	}
	if(startingPoint+1 <= npts)
	{
		point1 = Vector3(railPositions[railID][startingPoint+1][0][0],railPositions[railID][startingPoint+1][0][1],railPositions[railID][startingPoint+1][0][2]);
	}
	if(startingPoint+2 <= npts)
	{
		point2 = Vector3(railPositions[railID][startingPoint+2][0][0],railPositions[railID][startingPoint+2][0][1],railPositions[railID][startingPoint+2][0][2]);
	}
	if(startingPoint+3 <= npts)
	{
		point3 = Vector3(railPositions[railID][startingPoint+3][0][0],railPositions[railID][startingPoint+3][0][1],railPositions[railID][startingPoint+3][0][2]);
	}
	point0*=((float)(((float)1/6)*(pow(-t,3)+(3*pow(t,2))-(3*t)+1)));
	point1*=((float)(((float)1/6)*((3*pow(t,3))-(6*pow(t,2))+4)));
	point2*=((float)(((float)1/6)*((-3*pow(t,3))+(3*pow(t,2))+(3*t +1))));
	point3*=((float)(((float)1/6)*(pow(t,3))));

	Vector3 total = Vector3(0,0,0);
	total+=point0;
	total+=point1;
	total+=point2;
	total+=point3;
	return total;
}