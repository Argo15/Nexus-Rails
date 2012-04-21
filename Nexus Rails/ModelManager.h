#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <string>
#include <map>
#include "AObjModel.h"
using namespace std;

class ModelManager {
private:
	map<string,Model *> models;

public:
	ModelManager();
	~ModelManager(){}

    void Initialize();
	void LoadModel(string filename);
	void DrawModel(string name);
	void DeleteModel(string name);
	void DeleteAllModels();

	Model *getModel(string name) { return models[name]; }
	map<string,Model *> *getModels() {return &models;}		
};

#endif