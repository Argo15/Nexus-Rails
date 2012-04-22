#include "Root.h"
#include "Midi.h"

GameState *Root::GAMESTATE = 0;
RenderState Root::RENDERSTATE = FINAL;
TextureManager *Root::textureManager = 0;
ModelManager *Root::modelManager = 0;
MaterialManager *Root::materialManager = 0;
InputManager *Root::inputManager = 0;
ShaderManager *Root::shaderManager = 0;
stack<glm::mat4> Root::ModelviewMatrix = stack<glm::mat4>();
stack<glm::mat4> Root::ProjectionMatrix = stack<glm::mat4>();
stack<glm::mat3> Root::NormalMatrix = stack<glm::mat3>();
Midi *Root::MIDIPLAYER = new Midi();
MusicPlayer *Root::MUSICPLAYER = new MusicPlayer();