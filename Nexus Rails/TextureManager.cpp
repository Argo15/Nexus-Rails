#include "TextureManager.h"
#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include<string.h>
#include<fstream>
#include "dirent.h"

TextureManager::TextureManager()
{
	
}

void TextureManager::Initialize()
{
	DIR *pDIR;
	struct dirent *entry;
	if( pDIR=opendir("./Data/Textures") ){
		while(entry = readdir(pDIR)){
			if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 )
				LoadTexture(string("./Data/Textures/") + entry->d_name);
		}
		closedir(pDIR);
	}
}

void TextureManager::LoadTexture(string filename)
{
	Texture *texture = new TgaTexture();
	if (texture->load(filename.c_str())) {
		int start_pos = filename.rfind("/")+1;
		int end_pos = filename.rfind(".");
		string name = filename.substr(start_pos,end_pos-start_pos);
		texture->setName(name);
		textures[name]=texture;
	}
}

void TextureManager::BindTexture(string name)
{
	textures[name]->use();
}

void TextureManager::DeleteTexture(string name)
{
	if (textures.find(name) != textures.end()) {
		textures[name]->remove();
		delete textures[name];
		textures.erase(name);
	}
}

void TextureManager::DeleteAllTextures()
{
	textures.clear();
}