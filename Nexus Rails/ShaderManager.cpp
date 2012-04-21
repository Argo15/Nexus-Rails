#include "ShaderManager.h"
#include <assert.h>

ShaderManager::ShaderManager()
{

}

void ShaderManager::compileProgram(GLSLProgram *program)
{
	std::string log;
	if (!program->vertex_->isCompiled()){
		program->vertex_->getShaderLog(log);
		assert(false);
	}
	if (!program->fragment_->isCompiled()){	
		program->fragment_->getShaderLog(log);
		assert(false);
	}
}

void ShaderManager::Initialize()
{
	LoadShader("Basic", "Data/Shaders/v_material.glsl","Data/Shaders/f_material.glsl");
}

void ShaderManager::LoadShader(string name, string vertexShader, string fragmentShader)
{
	GLSLProgram *glslProgram = new GLSLProgram(vertexShader,fragmentShader);
	compileProgram(glslProgram);
	shaders[name] = glslProgram;
}

void ShaderManager::UseShader(string name)
{
	shaders[name]->use();
}

void ShaderManager::DisableShader(string name)
{
	shaders[name]->disable();
}

void ShaderManager::DeleteShader(string name)
{
	delete shaders[name];
}

void ShaderManager::DeleteAllShaders()
{
	shaders.clear();
}
