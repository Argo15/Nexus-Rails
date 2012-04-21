#include "RailsManager.h"
#include "Matrix.h"
#include "Root.h"
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
	connections = 0;
	transitionPercent = 1.0;
	speed = 0.008;
	actors = 0;
}

void RailsManager::reloadRails() {
	ifstream myReadFile;
	myReadFile.open("Data/Rails.txt");
	char output[100];
	char output2[100];
	int iOutput = 0;
	if (myReadFile.is_open()) {
		myReadFile >> output >> numRails;
		if (railPositions == 0) {
			delete[] railPositions;
			delete[] railColors;
			delete[] startTimes;
			delete[] connections;
			delete actors;
		}
		railPositions = new vector<Vector3 *>[numRails];
		railColors = new Vector3*[numRails];
		startTimes = new int[numRails];
		connections = new vector<Connection>[10000];
		actors = new vector<Actor *>();
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
		int conn[3];
		conn[0] = 0;
		while (conn[0] != -10000) {
			myReadFile >> conn[0] >> conn[1] >> conn[2];
			if (conn[0] >= 0) {
				Connection connection;
				connection.first = conn[1];
				connection.second = conn[2];
				connections[conn[0]].push_back(connection);
			}
		}

		while (output[0] != 'x' || output2[0] != 'x') {
			int pos[3];
			int scale[3];
			myReadFile >> output >> output2 >> pos[0] >> pos[1] >> pos[2] >> scale[0] >> scale[1] >> scale[2];
			if (output[0] != 'x' || output2[0] != 'x') {
				Actor *newActor = new Actor(new string(output), new string(output2));
				newActor->setTranslate(pos[0],pos[1],pos[2]);
				newActor->setScale(scale[0],scale[1],scale[2]);
				actors->push_back(newActor);
			}
		}
		
		myReadFile.close();
	}
}

void RailsManager::drawRails() {
						//sound
	Root::MIDIPLAYER->playRail(speed);
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
		glslProgram->sendUniform("material.emission", railColors[railID][0][0],railColors[railID][0][1],railColors[railID][0][2]);
		int npts = railPositions[railID].size()-1;
		int nsegment = 32;
		Vector3 pts[33];
		glBegin(GL_LINE_STRIP);
		for(int startingPoint =0 ; startingPoint < npts;startingPoint++)
		{
			for(int i =0; i<=nsegment; i++)
			{
				if(startingPoint >= npts)
				{
					break;
				}
				float t = (float)i/nsegment;
				//System.out.println("t "+t);
				pts[i] = calculateSplinePoint(t,railID,startingPoint);
				if(pts[i][0]!=-3000)
				{
					glVertex3f(pts[i][0],pts[i][1],pts[i][2]);
				}
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
	for (int railID=0; railID<numRails; railID++) {
		int npts = railPositions[railID].size()-1;
		for(int startingPoint = 0 ; startingPoint < npts;startingPoint++) {
			glslProgram->sendUniform("material.color", 1.0f, 1.0f, 1.0f);
			glslProgram->sendUniform("material.emission", 1.0f, 1.0f, 1.0f);
			glPointSize(25);
			glBegin(GL_POINTS);
				Vector3 pnt = calculateSplinePoint(0,railID,startingPoint);
				glVertex3f(pnt[0],pnt[1],pnt[2]);
			glEnd();
		}
	}

}

void RailsManager::drawActors() {
	for (vector<Actor *>::iterator it = actors->begin(); it != actors->end(); it++) {
		Actor *actor = (*it);
		Root::ModelviewMatrix.push(Root::ModelviewMatrix.top());
			actor->transformToMatrix(&Root::ModelviewMatrix.top());
			actor->drawActor("Basic");
		Root::ModelviewMatrix.pop();
	}
}

// railPositions: Rail, Segment, 0, xyz
// railColors: Rail, 0, rgb

void RailsManager::updateTime(Camera *camera, float dt) {
	currentTime += speed;
	speed += dt*0.0025;
	int currentSegment = (int)currentTime;
	if (transitionPercent > 0.99 && (Root::inputManager->isKeyDownOnce('a') || Root::inputManager->isKeyDownOnce('d'))) {
		vector<Connection> segConnections = connections[currentSegment];
		for (vector<Connection>::iterator it = segConnections.begin(); it != segConnections.end(); it++) {
			if (it->first == currentRail) {
				transitionPos = camera->geteyeV();
				currentRail = it->second;
				transitionPercent = 0.0f;
			} else if (it->second == currentRail) {
				transitionPos = camera->geteyeV();
				currentRail = it->first;
				transitionPercent = 0.0f;
			}
		}
	}
	int localSegment = (int)currentTime - startTimes[currentRail];
	if (localSegment < 0) return;	
	if (localSegment >= railPositions[currentRail].size()-3) {	// crash into end
		currentTime = startTimes[currentRail];
		localSegment = 0;
		speed = 0.008;
	}
	float p = currentTime - (int)currentTime;
	Vector3 position = calculateSplinePoint(p, currentRail, localSegment);
	if (position[0] == -3000) {
		return;
	}
	if (transitionPercent < 1.0) {
		transitionPercent += dt*5.0;
	}
	position[1] += 1.0;
	Vector3 finalCamPos = position*transitionPercent + transitionPos*(1.0-transitionPercent);
	camera->setPosition(finalCamPos[0],finalCamPos[1],finalCamPos[2]);
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
	else
	{
		return Vector3(-3000,0,0);
	}
	if(startingPoint+1 <= npts)
	{
		point1 = Vector3(railPositions[railID][startingPoint+1][0][0],railPositions[railID][startingPoint+1][0][1],railPositions[railID][startingPoint+1][0][2]);
	}
	else
	{
		return Vector3(-3000,0,0);
	}
	if(startingPoint+2 <= npts)
	{
		point2 = Vector3(railPositions[railID][startingPoint+2][0][0],railPositions[railID][startingPoint+2][0][1],railPositions[railID][startingPoint+2][0][2]);
	}
	else
	{
		return Vector3(-3000,0,0);
	}
	if(startingPoint+3 <= npts)
	{
		point3 = Vector3(railPositions[railID][startingPoint+3][0][0],railPositions[railID][startingPoint+3][0][1],railPositions[railID][startingPoint+3][0][2]);
	}
	else
	{
		return Vector3(-3000,0,0);
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
