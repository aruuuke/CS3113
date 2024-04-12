#include "LevelA.h"
#include "Utility.h"

#define LEVEL_WIDTH 14
#define LEVEL_HEIGHT 8

unsigned int LEVELA_DATA[] =
{
//X  0  0  1  2  3  4  5  6  7  8  9  10 11 12 13
        0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0,
        0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0,
        0, 0, 3, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1,
        0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1,
        0, 2, 2, 2, 0, 2, 0, 0, 2, 2, 2, 2, 2, 2
//   7
};

LevelA::~LevelA()
{
    delete [] m_state.enemies;
    delete    m_state.player;
    delete    m_state.map;
    Mix_FreeChunk(m_state.jump_sfx);
    Mix_FreeMusic(m_state.bgm);
}

void LevelA::initialise()
{
    m_state.next_scene_id = -1;
    
    GLuint map_texture_id = Utility::load_texture("assets/TilesetStone.png");
    m_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELA_DATA, map_texture_id, 1.0f, 8, 8);

    // player setup
    // Existing
    m_state.player = new Entity();
    m_state.player->set_entity_type(PLAYER);
    m_state.player->set_position(glm::vec3(1.0f, 4.0f, 0.0f));

    m_state.player->set_movement(glm::vec3(0.0f));
    m_state.player->set_speed(2.0f);
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
    GLuint enemy_texture_id = Utility::load_texture("assets/fox7.png");
    
    m_state.enemies = new Entity[ENEMY_COUNT];
    m_state.enemies[0].set_entity_type(ENEMY);
    m_state.enemies[0].set_ai_type(GUARD);
    m_state.enemies[0].set_ai_state(IDLE);
    m_state.enemies[0].set_position(glm::vec3(8.0f, 0.0f, 0.0f));
    m_state.enemies[0].set_movement(glm::vec3(0.0f));
    m_state.enemies[0].set_speed(1.0f);
    m_state.enemies[0].set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
    m_state.enemies[0].m_texture_id = enemy_texture_id;
    

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


void LevelA::update(float delta_time)
{
    m_state.player->update(delta_time, m_state.player, m_state.enemies, ENEMY_COUNT, m_state.map);
    
    if (m_state.player->get_position().y < -10.0f) m_state.next_scene_id = 1;
    
    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        m_state.enemies[i].update(delta_time, m_state.player, 0, 0, m_state.map);
    }
}


void LevelA::render(ShaderProgram *program)
{
    m_state.map->render(program);
    m_state.player->render(program);
    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        m_state.enemies[i].render(program);
    }
    
}
