#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <string>
#include <map>
#include "GLSLProgram.h"
#include "GLSLShader.h"
using namespace std;

class ShaderManager {
private:
	map<string,GLSLProgram *> shaders;
	void compileProgram(GLSLProgram *program);

public:
	ShaderManager();
	~ShaderManager(){}

    void Initialize();
	void LoadShader(string name, string vertexShader, string fragmentShader);
	void UseShader(string name);
	void DisableShader(string name);
	void DeleteShader(string name);
	void DeleteAllShaders();

	GLSLProgram *getShader(string name) { return shaders[name]; }
	map<string,GLSLProgram *> *getShaders() {return &shaders;}	
};

#endif