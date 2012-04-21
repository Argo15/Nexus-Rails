#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <string>
#include <map>
#include "TgaTexture.h"
using namespace std;

class TextureManager {
private:
	map<string,Texture *> textures;

public:
	TextureManager();
	~TextureManager(){}

    void Initialize();
	void LoadTexture(string filename);
	void BindTexture(string name);
	void DeleteTexture(string name);
	void DeleteAllTextures();

	Texture *getTexture(string name) { return textures[name]; }
	map<string,Texture *> *getTextures() {return &textures;}	
};

#endif