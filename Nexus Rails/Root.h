#ifndef ROOT_H
#define ROOT_H
#include "GameState.h"
#include "TextureManager.h"
#include "ModelManager.h"
#include "MaterialManager.h"
#include "InputManager.h"
#include "ShaderManager.h"
#include "Midi.h"
#include "MusicPlayer.h"

enum RenderState {FORWARD, FINAL, POSITION, NORMAL, COLOR, LIGHTING, SSAO, SPECULAR, MOTION};

class Root {
public:
	static GameState *GAMESTATE;
	static RenderState RENDERSTATE;
	static TextureManager *textureManager;
	static ModelManager *modelManager;
	static MaterialManager *materialManager;
	static InputManager *inputManager;
	static ShaderManager *shaderManager;
	static stack<glm::mat4> ModelviewMatrix;
	static stack<glm::mat4> ProjectionMatrix;
	static stack<glm::mat3> NormalMatrix;
	static Midi *MIDIPLAYER;
	static MusicPlayer *MUSICPLAYER;
};

#endif