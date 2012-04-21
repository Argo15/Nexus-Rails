#include "WorldCamera.h"

WorldCamera::WorldCamera() : Camera() 
{
	hAngle=0;
    vAngle=0;
	eyePos[0]=0.0; eyePos[1]=1.8f; eyePos[2]=0.0; 
	speedFactor = 0.3f;
	rotSpeed = 0.3f;
}

void WorldCamera::move(float speed)
{
	//WorldState *worldState = (WorldState *) Root::GAMESTATE;
	//worldState->getPhysicsManager()->getBulletManager()->updateDynamicsWorld(speed);

	mouseRotate();
}

void WorldCamera::moveForward(float speed)
{
	eyePos[0]-=cos(hAngle)*speed*speedFactor;
	eyePos[2]+=sin(hAngle)*speed*speedFactor;
	lookAt[0]-=cos(hAngle)*speed*speedFactor;
	lookAt[2]+=sin(hAngle)*speed*speedFactor;
}

void WorldCamera::moveBackward(float speed)
{
	eyePos[0]+=cos(hAngle)*speed*speedFactor;
	eyePos[2]-=sin(hAngle)*speed*speedFactor;
	lookAt[0]+=cos(hAngle)*speed*speedFactor;
	lookAt[2]-=sin(hAngle)*speed*speedFactor;
}

void WorldCamera::moveLeft(float speed)
{
	eyePos[2]+=cos(hAngle)*speed*speedFactor;
	eyePos[0]+=sin(hAngle)*speed*speedFactor;
	lookAt[2]+=cos(hAngle)*speed*speedFactor;
	lookAt[0]+=sin(hAngle)*speed*speedFactor;
}

void WorldCamera::moveRight(float speed)
{
	eyePos[2]-=cos(hAngle)*speed*speedFactor;
	eyePos[0]-=sin(hAngle)*speed*speedFactor;
	lookAt[2]-=cos(hAngle)*speed*speedFactor;
	lookAt[0]-=sin(hAngle)*speed*speedFactor;
}