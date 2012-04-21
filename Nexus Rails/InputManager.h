#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

class InputManager {
private:
	bool keys[256];
	bool keysPressedNotChecked[256];
	bool mouseButtons[5];
	int mouseX, mouseY;
	bool mouseCentered;
	bool mouseMoved;

public:
	InputManager();
	~InputManager() {}

	void registerKeyDown(int key);
	void registerKeyUp(int key);
	bool isKeyDown(int key);
	bool isKeyDownOnce(int key);

	void registerMouseButtonDown(int mouse);
	void registerMouseButtonUp(int mouse);
	void setMousePosition(int x, int y);
	void setMouseCentered(int x, int y);
	bool isMouseButtonDown(int mouse) {return mouseButtons[mouse];}
	int getMouseX() {return mouseX;}
	int getMouseY() {return mouseY;}
	bool isMouseMoved() {return mouseMoved;}
};

#endif