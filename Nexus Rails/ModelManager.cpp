#include "ModelManager.h"
#include<stdio.h>
#include<cstdlib>
#include<iostream>
#include<string.h>
#include<fstream>
#include "dirent.h"

ModelManager::ModelManager()
{
	
}

void ModelManager::Initialize()
{
	DIR *pDIR;
	struct dirent *entry;
	if( pDIR=opendir("./Data/Models") ){
		while(entry = readdir(pDIR)){
			if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 )
				LoadModel(string("./Data/Models/") + entry->d_name);
		}
		closedir(pDIR);
	}
}

void ModelManager::LoadModel(string filename)
{
	Model *model = new AObjModel();
	if (model->load(filename)) {
		int start_pos = filename.rfind("/")+1;
		int end_pos = filename.rfind(".");
		string name = filename.substr(start_pos,end_pos-start_pos);
		model->setName(name);
		models[name]=model;
	}
}

void ModelManager::DrawModel(string name)
{
	models[name]->draw();
}

void ModelManager::DeleteModel(string name)
{
	if (models.find(name) == models.end()){
		models[name]->remove();
		delete models[name];
		models.erase(name);
	}
}

void ModelManager::DeleteAllModels()
{
	models.clear();
}