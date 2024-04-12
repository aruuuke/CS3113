#include "Start.h"
#include "Utility.h"


Start::~Start()
{
    
    Mix_FreeMusic(m_state.bgm);
    Mix_FreeChunk(m_state.jump_sfx);
}

void Start::initialise()
{
    font_texture_id = Utility::load_texture("assets/font1.png");

    m_state.player = new Entity();
    m_state.player->set_entity_type(PLAYER);
    m_state.player->set_position(glm::vec3(1.0f, 0.0f, 0.0f));
    m_state.player->set_movement(glm::vec3(0.0f));
    m_state.player->set_speed(0.0f);
    m_state.player->set_acceleration(glm::vec3(0.0f, -9.81f, 0.0f));
    
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    m_state.bgm = Mix_LoadMUS("assets/IndustrialCinematic.mp3");
    Mix_PlayMusic(m_state.bgm, -1);
    Mix_VolumeMusic(5.0f);
    
    m_state.jump_sfx = Mix_LoadWAV("assets/blip.wav");
    //    std::cout<<"starting the start screen: "<< font_texture_id <<std::endl;
}

void Start::update(float delta_time) {}


void Start::render(ShaderProgram *program) {
   
    Utility::draw_text(program, font_texture_id, "start by pressing", 0.5f, 0.01, glm::vec3(1.0f, -2.0f, 0.0f));
    
    Utility::draw_text(program, font_texture_id, "RETURN", 0.5f, 0.01,
                       glm::vec3(3.5f, -3.0f, 0.0f));
}
