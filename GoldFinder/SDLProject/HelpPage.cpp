#include "HelpPage.h"
#include "Utility.h"

#define LEVEL_WIDTH 1
#define LEVEL_HEIGHT 1

unsigned int LEVEL_DATA_HELPPAGE[] =
{
    1,

};


HelpPage::~HelpPage()
{
    delete [] m_state.enemies;
    delete    m_state.player;
    delete    m_state.map;
}

void HelpPage::initialise()
{
    GLuint help_texture_id = Utility::load_texture("assets/help_page.png");
    m_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVEL_DATA_HELPPAGE, help_texture_id, 5.0f, 1, 1);
    m_state.player = new Entity();
}

void HelpPage::update(float delta_time)
{
    m_state.player->update(delta_time, m_state.player, m_state.enemies, ENEMY_COUNT, m_state.map);
}


void HelpPage::render(ShaderProgram *program)
{
    m_state.map->render(program);
}
