//
//  LevelC.cpp
//  SDLProject
//
//  Created by Aruuke Baiakmatova on 4/7/24.
//  Copyright © 2024 ctg. All rights reserved.
#include "LevelC.h"
#include "Utility.h"

#define LEVEL_WIDTH 14
#define LEVEL_HEIGHT 8

unsigned int LEVELC_DATA[] =
{
    0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0,
    0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0,
    0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 2, 2,
    0, 0, 0, 0, 3, 0, 0, 1, 1, 1, 0, 0, 2, 2,
    0, 1, 1, 1, 3, 0, 1, 1, 1, 2, 2, 2, 2, 2,
    0, 2, 2, 2, 3, 0, 2, 2, 2, 2, 2, 2, 2, 2
};

LevelC::~LevelC()
{
    delete [] m_state.enemies;
    delete    m_state.player;
    delete    m_state.map;
    Mix_FreeChunk(m_state.jump_sfx);
    Mix_FreeMusic(m_state.bgm);
}

void LevelC::initialise()
{
    m_state.next_scene_id = -1;
    GLuint map_texture_id = Utility::load_texture("assets/TilesetStone.png");
    m_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELC_DATA, map_texture_id, 1.0f, 8, 8);
    
    // player setup
    // Existing
    m_state.player = new Entity();
    m_state.player->set_entity_type(PLAYER);
    m_state.player->set_position(glm::vec3(1.0f, 5.0f, 0.0f));
    m_state.player->set_movement(glm::vec3(0.0f));
    m_state.player->set_speed(2.5f);
    m_state.player->set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
    m_state.player->m_texture_id = Utility::load_texture("assets/aang.png");
    
    // Walking
    m_state.player->m_walking[m_state.player->LEFT]  = new int[4] { 4, 5, 6,  7 };
    m_state.player->m_walking[m_state.player->RIGHT] = new int[4] { 8, 9, 10, 11 };
    m_state.player->m_walking[m_state.player->UP]    = new int[4] { 0, 12, 1, 13 };
    m_state.player->m_walking[m_state.player->DOWN]  = new int[4] { 1, 14, 2, 15 };

    m_state.player->m_animation_indices = m_state.player->m_walking[m_state.player->RIGHT];  // start George looking left
    m_state.player->m_animation_frames = 4;
    m_state.player->m_animation_index  = 0;
    m_state.player->m_animation_time   = 0.0f;
    m_state.player->m_animation_cols   = 4;
    m_state.player->m_animation_rows   = 4;
    m_state.player->set_height(0.8f);
    m_state.player->set_width(0.8f);
    
    // Jumping
    m_state.player->m_jumping_power = 5.0f;
    
    // Enemy setup
    GLuint enemy_texture_id = Utility::load_texture("assets/zuko.png");
    
    m_state.enemies = new Entity[ENEMY_COUNT];
    m_state.enemies[0].set_entity_type(ENEMY);
    m_state.enemies[0].set_ai_type(GUARD);
    m_state.enemies[0].set_ai_state(IDLE);
    m_state.enemies[0].m_texture_id = enemy_texture_id;
    m_state.enemies[0].set_position(glm::vec3(9.0f, 2.0f, 0.0f));
    m_state.enemies[0].set_movement(glm::vec3(0.0f));
    m_state.enemies[0].set_speed(2.0f);
    m_state.enemies[0].set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
    
    /**
     BGM and SFX
     */
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    
    m_state.bgm = Mix_LoadMUS("assets/StreetParty.mp3");
    std::cout<< m_state.bgm << std::endl;
    Mix_PlayMusic(m_state.bgm, -1);
    Mix_VolumeMusic(5.0f);
    
    m_state.jump_sfx = Mix_LoadWAV("assets/blip.wav");
}

void LevelC::update(float delta_time)
{
    m_state.player->update(delta_time, m_state.player, m_state.enemies, ENEMY_COUNT, m_state.map);
    
    if (m_state.player->get_position().y < -10.0f) {
        m_state.next_scene_id = -1;
        
    }
    
    for (int i = 0; i < ENEMY_COUNT; i++)
        {
            m_state.enemies[i].update(delta_time, m_state.player, 0, 0, m_state.map);
//            if (m_state.enemies[i].get_position().y< -LEVEL_HEIGHT && m_state.enemies[i].get_activity_status()){
//                m_state.enemies[i].set_position(glm::vec3(1.0f, 5.0f, 0.0f));
//            }
        }
}

void LevelC::render(ShaderProgram *program)
{
    m_state.map->render(program);
    m_state.player->render(program);
    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        m_state.enemies[i].render(program);
    }
}

