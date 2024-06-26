#define GL_SILENCE_DEPRECATION
#define GL_GLEXT_PROTOTYPES 1
#define FIXED_TIMESTEP 0.0166666f
#define LEVEL1_WIDTH 14
#define LEVEL1_HEIGHT 8
#define LEVEL1_LEFT_EDGE 5.0f
#define NUM_SCENES 3

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#include <SDL_mixer.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "cmath"
#include <ctime>
#include <vector>
#include "Utility.h"
#include "Scene.h"
#include "Effects.h"
#include "Start.h"
#include "LevelA.h"
#include "LevelB.h"
#include "LevelC.h"



// ————— CONSTANTS ————— //
const int WINDOW_WIDTH  = 640,
          WINDOW_HEIGHT = 480;

const float BG_RED     = 0.682f,
            BG_BLUE    = 0.8f,
            BG_GREEN   = 0.839f,
            BG_OPACITY = 1.0f;

const int VIEWPORT_X = 0,
          VIEWPORT_Y = 0,
          VIEWPORT_WIDTH  = WINDOW_WIDTH,
          VIEWPORT_HEIGHT = WINDOW_HEIGHT;

const char V_SHADER_PATH[] = "shaders/vertex_textured.glsl",
           F_SHADER_PATH[] = "shaders/fragment_textured.glsl";

const float MILLISECONDS_IN_SECOND = 1000.0;

// ————— GLOBAL VARIABLES ————— //
Scene *g_current_scene;
Start *g_start_screen; //
LevelA *g_level_a;
LevelB *g_level_b; //
LevelC *g_level_c;
Scene *scenes[NUM_SCENES]; // arr of scenes, needed for switching scenes
Effects *g_effects; // effects
bool g_is_colliding_bottom = false; // shaking effect


SDL_Window* g_display_window;
bool g_game_is_running = true;

ShaderProgram g_shader_program;
glm::mat4 g_view_matrix, g_projection_matrix;

float g_previous_ticks = 0.0f;
float g_accumulator = 0.0f;

GLuint font_texture_id;


void switch_to_scene(Scene *scene)
{
    g_current_scene = scene;
    g_current_scene->initialise();
}


void initialise()
{
    // ————— VIDEO ————— //
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    g_display_window = SDL_CreateWindow("Platformer!",
                                      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                      WINDOW_WIDTH, WINDOW_HEIGHT,
                                      SDL_WINDOW_OPENGL);
    
    SDL_GLContext context = SDL_GL_CreateContext(g_display_window);
    SDL_GL_MakeCurrent(g_display_window, context);
    
#ifdef _WINDOWS
    glewInit();
#endif
    
    // ————— GENERAL ————— //
    glViewport(VIEWPORT_X, VIEWPORT_Y, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
    g_shader_program.load(V_SHADER_PATH, F_SHADER_PATH);

    g_view_matrix = glm::mat4(1.0f);
    g_projection_matrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
    
    g_shader_program.set_projection_matrix(g_projection_matrix);
    g_shader_program.set_view_matrix(g_view_matrix);
    
    glUseProgram(g_shader_program.get_program_id());
    
    glClearColor(BG_RED, BG_BLUE, BG_GREEN, BG_OPACITY);
    
    // ————— LEVELS & START SCREEN SETUP ————— //
    g_start_screen = new Start();
    g_level_a = new LevelA();
    g_level_b = new LevelB();
    g_level_c = new LevelC();
    
    switch_to_scene(g_start_screen);
    // fill up the arr of scenes
    scenes[0] = g_level_a;
    scenes[1] = g_level_b;
    scenes[2] = g_level_c;
    // set up font_texture_id for the win/loss message
    font_texture_id = Utility::load_texture("assets/font1.png");

    g_effects = new Effects(g_projection_matrix, g_view_matrix);
    g_effects->start(SHRINK, 2.0f);
    
    // ————— BLENDING ————— //
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}



void process_input()
{
    g_current_scene->m_state.player->set_movement(glm::vec3(0.0f));
    
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type) {
        case SDL_QUIT:
        case SDL_WINDOWEVENT_CLOSE:
            g_game_is_running  = false;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_q:
                // Quit the game with a keystroke
                g_game_is_running  = false;
                break;

            case SDLK_SPACE:
                // Jump
                    if (g_current_scene->m_state.player->m_collided_bottom)
                {
                    g_current_scene->m_state.player->m_is_jumping = true;
                    Mix_PlayChannel(-1, g_current_scene->m_state.jump_sfx, 0);
                }
                break;
                    
            case SDLK_RETURN:
                    // switch to level1 if the user presses 'return' key iff we're currently at game menu
                    if (g_current_scene == g_start_screen){
                        switch_to_scene(scenes[g_current_scene->m_state.next_scene_id]);
                    }
                break;

            default:
                break;
            }

        default:
            break;
        }
    }

    const Uint8* key_state = SDL_GetKeyboardState(NULL);

    if (key_state[SDL_SCANCODE_LEFT])
    {
        g_current_scene->m_state.player->move_left();
        g_current_scene->m_state.player->m_animation_indices = g_current_scene->m_state.player->m_walking[g_current_scene->m_state.player->LEFT];
    }
    else if (key_state[SDL_SCANCODE_RIGHT])
    {
        g_current_scene->m_state.player->move_right();
        g_current_scene->m_state.player->m_animation_indices = g_current_scene->m_state.player->m_walking[g_current_scene->m_state.player->RIGHT];
    }

    if (glm::length(g_current_scene->m_state.player->get_movement()) > 1.0f)
    {
        g_current_scene->m_state.player->set_movement(glm::normalize(g_current_scene->m_state.player->get_movement()));
    }
}


void update()
{
    // ————— DELTA TIME / FIXED TIME STEP CALCULATION ————— //
    float ticks = (float)SDL_GetTicks() / MILLISECONDS_IN_SECOND;
    float delta_time = ticks - g_previous_ticks;
    g_previous_ticks = ticks;
    
    delta_time += g_accumulator;
    
    if (delta_time < FIXED_TIMESTEP)
    {
        g_accumulator = delta_time;
        return;
    }
    
    while (delta_time >= FIXED_TIMESTEP) {
        // ————— UPDATING THE SCENE (i.e. map, character, enemies...) ————— //
        g_current_scene->update(FIXED_TIMESTEP);
        g_effects->update(FIXED_TIMESTEP);

        if (g_is_colliding_bottom == false && g_current_scene->m_state.player->m_collided_bottom) g_effects->start(SHAKE, 1.0f);
        
        g_is_colliding_bottom = g_current_scene->m_state.player->m_collided_bottom;
        delta_time -= FIXED_TIMESTEP;
    }
    
    g_accumulator = delta_time;
    
    
    // ————— PLAYER CAMERA ————— //
    g_view_matrix = glm::mat4(1.0f);
    
    if (g_current_scene->m_state.player->get_position().x > LEVEL1_LEFT_EDGE) {
        g_view_matrix = glm::translate(g_view_matrix, glm::vec3(-g_current_scene->m_state.player->get_position().x, 3.75, 0));
    }
    else {
        g_view_matrix = glm::translate(g_view_matrix, glm::vec3(-5, 3.75, 0));
    }
}



void render()
{
    g_shader_program.set_view_matrix(g_view_matrix);
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    // ————— RENDERING THE SCENE (i.e. map, character, enemies...) ————— //
    g_current_scene->render(&g_shader_program);
    g_effects->render();
    
    // if the player runs of health & gets deactivated, they lose.
    if (!g_current_scene->m_state.player->get_activity_status()){
        Utility::draw_text(&g_shader_program, font_texture_id, "YOU LOSE.", 1.0f, 0.01f, glm::vec3(g_current_scene->m_state.player->get_position().x - 3.0f, -2.0f, 0.0f));
        Mix_HaltMusic();
    }
    // if the player killed the last enemy & finished the last level, they win!
    else if (g_current_scene == g_level_c && g_current_scene->m_state.player->dead == g_current_scene->m_number_of_enemies && g_current_scene->m_state.player->get_activity_status()){
        
        Utility::draw_text(&g_shader_program, font_texture_id, "YOU WIN!!!", 1.0f, 0.01f, glm::vec3(g_current_scene->m_state.player->get_position().x - 3.0f, -2.0f, 0.0f));
        Mix_HaltMusic();
    }

    SDL_GL_SwapWindow(g_display_window);
}

void shutdown()
{
    SDL_Quit();
    // ————— DELETING LEVEL A DATA (i.e. map, character, enemies...) ————— //
    delete g_start_screen;
    delete g_level_a;
    delete g_level_b;
    delete g_level_c;
}

// ————— GAME LOOP ————— //
int main(int argc, char* argv[])
{
    initialise();
    
    while (g_game_is_running)
    {
        process_input();
        update();

        if (g_current_scene->m_state.next_scene_id > 0)
        {
            switch_to_scene(scenes[g_current_scene->m_state.next_scene_id]);
        }
        render();
    }
    
    shutdown();
    return 0;
}
