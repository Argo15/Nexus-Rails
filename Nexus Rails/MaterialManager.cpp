#include "MaterialManager.h"
#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include<string.h>
#include<fstream>
#include "dirent.h"

MaterialManager::MaterialManager()
{
}

void MaterialManager::Initialize()
{
	DIR *pDIR;
	struct dirent *entry;
	if( pDIR=opendir("./Data/Materials") ){
		while(entry = readdir(pDIR)){
			if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 )
				LoadMaterial(string("./Data/Materials/") + entry->d_name);
		}
		closedir(pDIR);
	}
}

void MaterialManager::LoadMaterial(string filename)
{
	Material *newMaterial = new Material();
	if (newMaterial->loadMaterial(filename.c_str())) {
		string *name = newMaterial->getName();
		materials[*name] = newMaterial;
	}
}

void MaterialManager::DeleteMaterial(string name)
{
	if (materials.find(name) != materials.end()) {
		delete materials[name];
		materials.erase(name);
	}
}

void MaterialManager::DeleteAllMaterials()
{
	materials.clear();
}