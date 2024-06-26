#pragma once
#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL_mixer.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "Util.h"
#include "Entity.h"
#include "Map.h"

struct GameState
{
    Map    *map;
    Entity *player;
    Entity *enemies;
    Entity *gold;
    
    Mix_Music *bgm;
    Mix_Chunk *jump_sfx;
    Mix_Chunk *lost_sfx;
    Mix_Chunk *won_sfx;
    Mix_Chunk *fall_sfx;
    Mix_Chunk *up_sfx;
    
    int next_scene_id;
};

class Scene {
public:
    int m_number_of_enemies = 1;
    int m_number_of_gold = 1;
    GameState m_state;
    
    
    virtual void initialise() = 0;
    virtual void update(float delta_time) = 0;
    virtual void render(ShaderProgram *program) = 0;

};
