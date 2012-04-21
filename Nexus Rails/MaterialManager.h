#ifndef MATERIALMANAGER_H
#define MATERIALMANAGER_H

#include <string>
#include <map>
#include "Material.h"
using namespace std;

class MaterialManager {
private:
	map<string,Material *> materials;

public:
	MaterialManager();	
	~MaterialManager(){}

    void Initialize();
	void LoadMaterial(string filename);
	void UseMaterial(string name) {materials[name]->use();}
	void DeleteMaterial(string name);
	void DeleteAllMaterials();

	Material *getMaterial(string name) {return materials[name];}
	map<string,Material *> *getMaterials() {return &materials;}
};

#endif