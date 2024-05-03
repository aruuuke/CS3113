#include "Start.h"
#include "Utility.h"

#define LEVEL_WIDTH 1
#define LEVEL_HEIGHT 1

unsigned int LEVEL_DATA_MENU[] =
{
        1,  
    //2,  3,  4,  5,  6,  7,  8,  9, 10,
    //11, 12, 13, 14, 15, 16,
    //17, 18, 19, 20,
//        13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
//        25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36,
//        37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
//        49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
//        61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72,
//        73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84,
//        85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96,
//        97, 98, 99,100,101,102,103,104,105,106,107, 108,
//        109,110,111,112,113,114,115,116,117,118,119,120

    
};

Start::~Start()
{
    delete [] m_state.enemies;
    delete    m_state.player;
    delete    m_state.map;
    Mix_FreeMusic(m_state.bgm);
}

void Start::initialise()
{
    GLuint menu_texture_id = Utility::load_texture("assets/mene.png");
    m_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVEL_DATA_MENU, menu_texture_id, 8.0f, 1, 1);

    m_state.player = new Entity();
   
    
}

void Start::update(float delta_time){
    m_state.player->update(delta_time, m_state.player, NULL, 0, m_state.map);
}


void Start::render(ShaderProgram *program){
    m_state.map->render(program);
}
