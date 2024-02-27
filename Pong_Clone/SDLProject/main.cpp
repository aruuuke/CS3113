#define GL_SILENCE_DEPRECATION
#define STB_IMAGE_IMPLEMENTATION
#define GL_GLEXT_PROTOTYPES 1

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define LOG(argument) std::cout << argument << '\n'


#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "stb_image.h"

// —— NEW STUFF —— //
#include <ctime>   //
#include "cmath"   //
// ——————————————— //

const int WINDOW_WIDTH = 640 * 2,
          WINDOW_HEIGHT = 480 * 2;

const float BG_RED = 0.1922f,
            BG_BLUE = 0.549f,
            BG_GREEN = 0.9059f,
            BG_OPACITY = 1.0f;

const int VIEWPORT_X = 0,
          VIEWPORT_Y = 0,
          VIEWPORT_WIDTH = WINDOW_WIDTH,
          VIEWPORT_HEIGHT = WINDOW_HEIGHT;

const char V_SHADER_PATH[] = "shaders/vertex_textured.glsl",
           F_SHADER_PATH[] = "shaders/fragment_textured.glsl";

const int NUMBER_OF_TEXTURES = 1; // to be generated, that is
const GLint LEVEL_OF_DETAIL = 0;  // base image level; Level n is the nth mipmap reduction image
const GLint TEXTURE_BORDER = 0;   // this value MUST be zero

const char BACKGROUND_FILEPATH[] = "/Users/aruukebaiakmatova/Desktop/CS3113/Pong_Clone/assets/sky.jpg";
const char PLAYER1_SPRITE_FILEPATH[] = "/Users/aruukebaiakmatova/Desktop/CS3113/Pong_Clone/assets/NeoCortex.png";
const char PLAYER2_SPRITE_FILEPATH[] = "/Users/aruukebaiakmatova/Desktop/CS3113/Pong_Clone/assets/Bandicoot.png";
const char BALL_SPRITE_FILEPATH[] = "/Users/aruukebaiakmatova/Desktop/CS3113/Pong_Clone/assets/ball.png";

SDL_Window* g_display_window;
bool g_game_is_running = true;
//bool g_is_growing = true;

ShaderProgram g_shader_program;
glm::mat4 background_matrix, player1_matrix, player2_matrix, ball_matrix, view_matrix, projection_matrix;

GLuint texture_id_background;
GLuint texture_id_player1;
GLuint texture_id_player2;
GLuint texture_id_ball;

glm::vec3 player1_position = glm::vec3(-4.0f, 0.0f, 0.0f); // player1 is on the left side
glm::vec3 player1_movement = glm::vec3(0.0f, 0.0f, 0.0f);

glm::vec3 player2_position = glm::vec3(4.0f, 0.0f, 0.0f); // player2 is on the right side
glm::vec3 player2_movement = glm::vec3(0.0f, 0.0f, 0.0f);

glm::vec3 ball_position = glm::vec3(0.0f, 0.0f, 0.0f); // ball is at the center
glm::vec3 ball_movement = glm::vec3(1.0f, 1.0f, 0.0f);

float g_previous_ticks = 0.0f;
const float MILLISECONDS_IN_SECOND = 1000.0;

const float LeftRightBounds = 6.0f; // left-right bounds
const float TopBottomBounds = 6.0f; //  top-bottom bounds

float speed = 4.0f;
float player2_speed = 5.0f; // player2 speed in 1-player mode
float ball_speed = 1.0f;

bool single_player = false; // by default, the game is for 2 players
bool play = true;

                                                            

GLuint load_texture(const char* filepath) {
    // STEP 1: Loading the image file
    int width, height, number_of_components;
    unsigned char* image = stbi_load(filepath, &width, &height, &number_of_components, STBI_rgb_alpha);
    
    if (image == NULL){
            LOG("Unable to load image. Make sure the path is correct.");
            LOG(filepath);
            assert(false);
    }
    
    // STEP 2: Generating and binding a texture ID to our image
    GLuint textureID;
    glGenTextures(NUMBER_OF_TEXTURES, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, LEVEL_OF_DETAIL, GL_RGBA, width, height, TEXTURE_BORDER, GL_RGBA, GL_UNSIGNED_BYTE, image);
    
    // STEP 3: Setting our texture filter parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // STEP 4: Releasing our file from memory and returning our texture id
    stbi_image_free(image);
    
    return textureID;
}


void draw_object(glm::mat4 &object_model_matrix, GLuint &object_texture_id) {
    g_shader_program.set_model_matrix(object_model_matrix);
    glBindTexture(GL_TEXTURE_2D, object_texture_id);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}


bool check_collision(glm::vec3 &position_a, glm::vec3 &position_b) {
    float x_distance = fabs(position_a.x - position_b.x) - ((2.0f+0.7f) / 2.0f);
    float y_distance = fabs(position_a.y - position_b.y) - ((2.0f+0.7f)/ 2.0f);
    
    if (x_distance < 0 && y_distance < 0){
        // Collision!
        std::cout << "Collision!\n";
    }
    
    return (x_distance < 0.0f && y_distance < 0.0f);
}


void initialise() {
    SDL_Init(SDL_INIT_VIDEO);
    g_display_window = SDL_CreateWindow("Pong Clone",
                                      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                      WINDOW_WIDTH, WINDOW_HEIGHT,
                                      SDL_WINDOW_OPENGL);
    
    SDL_GLContext context = SDL_GL_CreateContext(g_display_window);
    SDL_GL_MakeCurrent(g_display_window, context);
    
    #ifdef _WINDOWS
    glewInit();
    #endif
    
    glViewport(VIEWPORT_X, VIEWPORT_Y, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
    
    g_shader_program.load(V_SHADER_PATH, F_SHADER_PATH);
    
 
    background_matrix   = glm::mat4(1.0f);
    player1_matrix    = glm::mat4(1.0f);
    player2_matrix    = glm::mat4(1.0f);
    ball_matrix  = glm::mat4(1.0f);
    view_matrix         = glm::mat4(1.0f); // Defines the position (location and orientation) of the camera
    projection_matrix   = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f); // Defines the characteristics of your camera, such as clip planes, field of view, projection method etc.
    
    g_shader_program.set_projection_matrix(projection_matrix);
    g_shader_program.set_view_matrix(view_matrix);
    
    glUseProgram(g_shader_program.get_program_id());
    
    glClearColor(BG_RED, BG_BLUE, BG_GREEN, BG_OPACITY);
    
    texture_id_background = load_texture(BACKGROUND_FILEPATH);
    texture_id_player1 = load_texture(PLAYER1_SPRITE_FILEPATH);
    texture_id_player2 = load_texture(PLAYER2_SPRITE_FILEPATH);
    texture_id_ball = load_texture(BALL_SPRITE_FILEPATH);
    
    background_matrix = glm::scale(background_matrix, glm::vec3(10.0f, 8.0f, 0.0f)); // scale background texture
    
    // enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void process_input() {
    // VERY IMPORTANT: If nothing is pressed, we don't want to go anywhere   //
    player1_movement = glm::vec3(0.0f);
    player2_movement = glm::vec3(0.0f);

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            // End game
            case SDL_QUIT:
            case SDL_WINDOWEVENT_CLOSE:
                g_game_is_running = false;
                break;
                        
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                // player 1 could use the W and S keys
                    case SDLK_w:
                        player1_movement.y = 1.0f;
                        break;
                
                    case SDLK_s:
                        player1_movement.y = -1.0f;
                        break;
                        
                // player 2 would use the Up and Down arrows
                    case SDLK_UP:
                        if (!single_player) {
                            player2_movement.y = 1.0f;
                        }
                        break;
                        
                    case SDLK_DOWN:
                        if (!single_player) {
                            player2_movement.y = -1.0f;
                        }
                        break;
                        
                // switching from 2-player mode to 1-player mode
                    case SDLK_t:
                        single_player = !single_player;
                        break;
                
                    case SDLK_q:
                    // Quit the game with a keystroke
                        g_game_is_running = false;
                        break;
                        
                    default:
                        break;
                }
                
            default:
                break;
        }
    }
    
    const Uint8 *key_state = SDL_GetKeyboardState(NULL);

    if (key_state[SDL_SCANCODE_W]) {
        player1_movement.y = 1.0f;
    }
    else if (key_state[SDL_SCANCODE_S]) {
        player1_movement.y = -1.0f;
    }
    
    if (key_state[SDL_SCANCODE_UP]) {
        player2_movement.y = 1.0f;
    }

    else if (key_state[SDL_SCANCODE_DOWN]) {
        player2_movement.y = -1.0f;
    }
    
    // normalize speed
    if (glm::length(player1_movement) > 1.0f) {
        player1_movement = glm::normalize(player1_movement);
    }
    
    if (glm::length(player2_movement) > 1.0f) {
        player2_movement = glm::normalize(player2_movement);
    }

    if (glm::length(ball_movement) > 1.0f) {
        ball_movement = glm::normalize(ball_movement);
    }
}


void update() {
    // delta time
    float ticks = (float) SDL_GetTicks() / MILLISECONDS_IN_SECOND;
    float delta_time = ticks - g_previous_ticks;
    g_previous_ticks = ticks;
    
    // 1 player mode movement
    if (single_player){
        player1_matrix = glm::mat4(1.0f);
        player1_position += player1_movement * speed * delta_time;
        player1_matrix = glm::translate(player1_matrix, player1_position);
        
        player2_matrix = glm::mat4(1.0f);
        player2_position += player2_speed * delta_time;
        player2_matrix = glm::translate(player2_matrix, glm::vec3(4.0f, player2_position.y, 0.0f));
        // ball movement
        ball_matrix = glm::mat4(1.0f);
        ball_position      += ball_movement * ball_speed * delta_time;
        ball_matrix = glm::translate(ball_matrix, ball_position);
    }
    
    // 2 player mode movement
    else if (!single_player){
        player1_matrix = glm::mat4(1.0f);
        player1_position += player1_movement * speed * delta_time;
        player1_matrix = glm::translate(player1_matrix, player1_position);
        
        player2_matrix = glm::mat4(1.0f);
        player2_position += player2_movement * speed * delta_time;
        player2_matrix = glm::translate(player2_matrix, player2_position);
        
        // ball movement
        ball_matrix = glm::mat4(1.0f);
        ball_position += ball_movement * ball_speed * delta_time;
        ball_matrix = glm::translate(ball_matrix, ball_position);
    }
    
    
    // player hits top or bottom bound
    if (player1_position.y > TopBottomBounds || player1_position.y < -TopBottomBounds ) {
        player1_position.y = -1 * TopBottomBounds;
    }
    
    if (player2_position.y > TopBottomBounds || player2_position.y < -TopBottomBounds) {
        player2_position.y = -1 * TopBottomBounds;
    }
    
    // ball hits top or bottom bound
    if (ball_position.y >  TopBottomBounds || ball_position.y < -TopBottomBounds) {
        ball_position.y = -1 * TopBottomBounds;
    }
    
    // stop the game when the ball hits a wall on the left or right
    if (ball_position.x > LeftRightBounds || ball_position.x < -LeftRightBounds) {
        if (ball_position.x > LeftRightBounds){
            std::cout <<"Player One won!\n";
        }
        
        else {
            std::cout <<"Player Two won!\n";
        }

        std::cout <<"The End!\n";
        
        play = false;
        g_game_is_running = false;
    }
    
    // Collision: player & ball
    if (check_collision(player1_position, ball_position)) {
        ball_movement.x *= -1.0f; // change the ball's direction
        player1_position.y += -1*0.2f; // move the player slightly in the opposite y-dir
        ball_speed *= 1.00025f; // make ball move a bit faster
        speed *= 1.0025; // make player move a bit faster
    }
    
    if  (check_collision(player2_position, ball_position)){
        ball_movement.x *= -1.0f;
        player2_position.y += -1*0.2f;
        ball_speed *= 1.00025;
        if (!single_player){
            speed *= 1.0025;
        }
        if (single_player){
            player2_speed *= 1.025;
        }
    }
    
    // scale players & ball
    player1_matrix = glm::scale(player1_matrix, glm::vec3(2.0f, 2.0f, 0.0f));
    player2_matrix = glm::scale(player2_matrix, glm::vec3(2.0f, 2.0f, 0.0f));
    ball_matrix = glm::scale(ball_matrix, glm::vec3(0.7f,0.7f,0.0f));
}


void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    // vertices
    float vertices[] = {
        -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f,  // triangle 1
        -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f   // triangle 2
    };

    // textures
    float texture_coordinates[] = {
        0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,     // triangle 1
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,     // triangle 2
    };
    
    glVertexAttribPointer(g_shader_program.get_position_attribute(), 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(g_shader_program.get_position_attribute());
    
    glVertexAttribPointer(g_shader_program.get_tex_coordinate_attribute(), 2, GL_FLOAT, false, 0, texture_coordinates);
    glEnableVertexAttribArray(g_shader_program.get_tex_coordinate_attribute());
    
    // bind textures
    draw_object(background_matrix, texture_id_background);
    draw_object(player1_matrix, texture_id_player1);
    draw_object(player2_matrix, texture_id_player2);
    draw_object(ball_matrix, texture_id_ball);
    
    glDisableVertexAttribArray(g_shader_program.get_position_attribute());
    glDisableVertexAttribArray(g_shader_program.get_tex_coordinate_attribute());
    
    SDL_GL_SwapWindow(g_display_window);
}


void shutdown() {
    SDL_Quit();
}


int main(int argc, char* argv[]) {
    initialise();
    
    while (g_game_is_running) {
        process_input();
        update();
        render();
    }
    
    shutdown();
    return 0;
}
