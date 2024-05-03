#include "LevelB.h"
#include "Utility.h"

#define LEVEL_WIDTH 100
#define LEVEL_HEIGHT 20

unsigned int LEVELB_DATA[] =
{
//     // 0                     9  10                         19 20                            30                            40                            50
        
        0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 3, 2, 2, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
        0, 2, 0, 0, 3, 0, 3, 0, 0, 3, 0, 2, 0, 1, 1, 0, 0, 0, 0, 0, 2, 3, 0, 1, 3, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 2,
        0, 2, 0, 0, 0, 3, 1, 3, 0, 1, 1, 0, 2, 1, 0, 0, 0, 1, 0, 0, 1, 2, 0, 2, 0, 2, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 3, 3, 0, 0, 0, 3, 0, 0, 0, 1, 0, 2,
        1, 0, 1, 0, 0, 0, 3, 0, 0, 1, 1, 0, 3, 2, 0, 0, 0, 2, 3, 0, 0, 0, 3, 2, 2, 0, 0, 0, 0, 2, 2, 3, 3, 0, 1, 3, 2, 0, 0, 0, 3, 1, 0, 1, 1, 0, 0, 1, 0, 1,
        0, 2, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 1, 0, 1, 2, 3, 0, 3, 0, 0, 0, 3, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 1, 0, 0, 0,
        2, 2, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 1, 0, 1, 2, 3, 0, 3, 0, 0, 9, 3, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 1, 0, 0, 0,
        3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 2, 3, 0, 0, 2, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
        3, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 3, 2, 2, 0, 0, 1, 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
        0, 1, 3, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 1, 0, 0, 0, 0, 0,
        1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 2, 0, 0, 0, 2, 3, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
        0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 3, 2, 2, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
        0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 2, 0, 0, 3, 0, 3, 0, 0, 3, 0, 2, 0, 1, 1, 0, 0, 0, 0, 0, 2, 3, 0, 1, 3, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 2,
        0, 2, 0, 0, 0, 3, 1, 3, 0, 1, 1, 0, 2, 1, 0, 0, 0, 1, 0, 0, 1, 2, 0, 2, 0, 2, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 3, 3, 0, 0, 0, 3, 0, 0, 0, 1, 0, 2,
        1, 0, 1, 0, 0, 0, 3, 0, 0, 1, 1, 0, 3, 2, 0, 0, 0, 2, 3, 0, 0, 0, 3, 2, 2, 0, 0, 0, 0, 2, 2, 3, 3, 0, 1, 3, 2, 0, 0, 0, 3, 1, 0, 1, 1, 0, 0, 1, 0, 1,
        0, 2, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 1, 0, 1, 2, 3, 0, 3, 0, 0, 0, 3, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 1, 0, 0, 0,
        2, 2, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 1, 0, 1, 2, 3, 0, 3, 0, 0, 9, 3, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 1, 0, 0, 0,
        3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 2, 3, 0, 0, 2, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
        3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 2, 3, 0, 0, 2, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2,
        3, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 3, 2, 2, 0, 0, 1, 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
};

LevelB::~LevelB()
{
    delete [] m_state.enemies;
    delete    m_state.player;
    delete    m_state.map;
    Mix_FreeChunk(m_state.jump_sfx);
    Mix_FreeMusic(m_state.bgm);
}

void LevelB::initialise()
{
    font_texture_id = Utility::load_texture("assets/font1.png");
    GLuint map_texture_id = Utility::load_texture("assets/Tileset_1.png");
    m_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVELB_DATA, map_texture_id, 1.0f, 11, 8);

    // Existing
    
    m_state.player = new Entity();
    m_state.player->set_entity_type(PLAYER);

    m_state.player->set_movement(glm::vec3(0.0f));
    m_state.player->set_speed(3.0f);
    m_state.player->set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
    m_state.player->m_texture_id = Utility::load_texture("assets/jin.png");
    
    // Walking
    m_state.player->m_walking[m_state.player->LEFT]  = new int[3] { 6,7,8};
    m_state.player->m_walking[m_state.player->RIGHT] = new int[3] { 12,13,14};
    m_state.player->m_walking[m_state.player->UP] = new int[3]    { 0, 1, 2};
    m_state.player->m_walking[m_state.player->DOWN] = new int[3] { 18,19, 20};

    m_state.player->m_animation_indices = m_state.player->m_walking[m_state.player->RIGHT];  // start George looking left
    m_state.player->m_animation_frames = 4;
    m_state.player->m_animation_index  = 0;
    m_state.player->m_animation_time   = 0.0f;
    m_state.player->m_animation_cols   = 6;
    m_state.player->m_animation_rows   = 4;
    m_state.player->set_height(0.80f);
    m_state.player->set_width(0.7f);
    m_state.player->set_health(10);
//    m_state.player->set_damage(5);
   
    
    m_state.player->set_position(glm::vec3(0.0f, 0.0f, 0.0f));
    
    
    // Jumping
    m_state.player->m_jumping_power = 6.0f;
    
    
    // Enemy setup
    GLuint enemy_texture_id = Utility::load_texture("assets/kaz.png");
    
    m_state.enemies = new Entity[ENEMY_COUNT];

    for(int i = 0; i < ENEMY_COUNT; ++i){
        m_state.enemies[i].set_entity_type(ENEMY);
        m_state.enemies[i].set_ai_type(GUARD);
        m_state.enemies[i].set_ai_state(IDLE);
        m_state.enemies[i].set_movement(glm::vec3(0.0f));
        m_state.enemies[i].set_speed(1.8f);
        m_state.enemies[i].set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
        m_state.enemies[i].m_texture_id = enemy_texture_id;
      

        m_state.enemies[i].m_walking[m_state.enemies[0].LEFT]  = new int[3] { 6,7,8};
        m_state.enemies[i].m_walking[m_state.enemies[0].RIGHT] = new int[3] { 12,13,14};

        m_state.enemies[i].m_animation_indices = m_state.enemies[0].m_walking[m_state.enemies[0].LEFT];  // start kaz looking left
        m_state.enemies[i].m_animation_frames = 4;
        m_state.enemies[i].m_animation_index  = 0;
        m_state.enemies[i].m_animation_time   = 0.0f;
        m_state.enemies[i].m_animation_cols   = 6;
        m_state.enemies[i].m_animation_rows   = 4;
        m_state.enemies[i].set_height(0.80f);
        m_state.enemies[i].set_width(0.7f);
        m_state.enemies[i].set_health(10);

        m_state.enemies[i].set_position(glm::vec3(rand() % 100, rand() % 10, 0.0f));
    }

    m_state.gold = new Entity[GOLD_COUNT];
    GLuint gold_texture_id = Utility::load_texture("assets/gold.png");
    //m_state.gold->set_total_gold(GOLD_COUNT);
    
    for (int i = 0; i < GOLD_COUNT; ++i){
        m_state.gold[i].set_entity_type(GOLD);
        m_state.gold[i].set_movement(glm::vec3(0.0f));
        m_state.gold[i].set_speed(0.0f);
        m_state.gold[i].m_texture_id = gold_texture_id;
        
        m_state.gold[i].set_height(0.1f);
        m_state.gold[i].set_width(0.5f);
        
        m_state.gold[i].set_position(glm::vec3(i+rand() % 80, i-rand() % 5, 0.0f));
    }
    

    /**
     BGM and SFX
     */
    
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    
    m_state.bgm = Mix_LoadMUS("assets/Dvorak Polka.mp3");
    std::cout<< m_state.bgm << std::endl;
    Mix_PlayMusic(m_state.bgm, -1);
    //Mix_VolumeMusic(5.0f);
    
    m_state.jump_sfx = Mix_LoadWAV("assets/blip.wav");
    m_state.lost_sfx = Mix_LoadWAV("assets/wrong-answer-21-199825.wav");
    m_state.won_sfx = Mix_LoadWAV("assets/success-fanfare-trumpets-6185.wav");
    m_state.fall_sfx = Mix_LoadWAV("assets/cartoon-slide-whistle-down7.wav");
    m_state.up_sfx = Mix_LoadWAV("assets/ui-pop-up-5-197889.wav");
   
    Mix_VolumeMusic(10.0f);
}


void LevelB::update(float delta_time)
{
    
    m_state.player->update(delta_time, m_state.player, m_state.enemies, ENEMY_COUNT, m_state.map);
    
    
    if (m_state.player->get_position().x >= LEVEL_WIDTH && m_state.player->get_activity_status()) m_state.next_scene_id = 1;
    
    // bounds: player falling not at the of the map, loses health
    if (m_state.player->get_position().x < LEVEL_WIDTH && m_state.player->get_position().y <= -LEVEL_HEIGHT && m_state.player->get_activity_status()){
        
        m_state.player->set_health(m_state.player->get_health() - 1);
        m_state.player->set_position(glm::vec3(0.0f, 0.0f, 0.0f));
    }
    
    

    for (int i = 0; i < GOLD_COUNT; i++){
        
        m_state.gold[i].update(delta_time, m_state.player, 0, 0, m_state.map);
    }
    
    
    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        m_state.enemies[i].update(delta_time, m_state.player, 0, 0, m_state.map);
        // bounds: enemy falling of the map, deactivates.
        if ((m_state.enemies[i].get_position().x > LEVEL_WIDTH || m_state.enemies[i].get_position().y <= -LEVEL_HEIGHT) && m_state.enemies[i].get_activity_status())
        {
            m_state.enemies[i].deactivate();
            m_state.enemies[i].set_position(glm::vec3(-100.0f, -100.0f, 0.0f));
        }
    }
}



void LevelB::render(ShaderProgram *program)
{
    m_state.map->render(program);
    m_state.player->render(program);
    //m_state.gold->render(program);
    
    Utility::draw_text(program, font_texture_id, "lives = "+std::to_string(m_state.player->get_health()), 0.275f, 0.01,  m_state.player->get_position()+glm::vec3(0.0f, 0.575f, 1.0f));
    Utility::draw_text(program, font_texture_id, "gold = "+std::to_string(m_state.player->found)+"/"+std::to_string(GOLD_COUNT), 0.275f, 0.01,  m_state.player->get_position()+glm::vec3(0.0f, 0.775f, 1.0f));
    
    
    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        m_state.enemies[i].render(program);
    }
    
    for (int i = 0; i < GOLD_COUNT; i++)
    {
        m_state.gold[i].render(program);
    }
    
    
}
