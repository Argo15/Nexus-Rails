#include "InputManager.h"

InputManager::InputManager()
{
	for (int i=0; i<256; i++) {
		keysPressedNotChecked[i]=false;
		keys[i]=false;
	}
	for (int i=0; i<5; i++)
		mouseButtons[i] = false;
	mouseX = 0;
	mouseY = 0;
	mouseCentered = false;
	anyKey = true;
}

void InputManager::registerKeyDown(int key)
{
	keys[key]=true;
	keysPressedNotChecked[key]=true;
}

void InputManager::registerKeyUp(int key)
{
	keys[key]=false;
}

bool InputManager::isKeyDown(int key)
{
	keysPressedNotChecked[key]=false; 
	return keys[key];
}

bool InputManager::isKeyDownOnce(int key)
{
	if(keysPressedNotChecked[key]){
		keysPressedNotChecked[key]=false;
		return true;
	}
	return false;
}

void InputManager::registerMouseButtonDown(int mouse)
{
	mouseButtons[mouse] = true;
}

void InputManager::registerMouseButtonUp(int mouse)
{
	mouseButtons[mouse] = false;
}

void InputManager::setMousePosition(int x, int y)
{
	mouseX = x;
	mouseY = y;
}

void InputManager::setMouseCentered(int x, int y)
{
	mouseCentered = true;
}