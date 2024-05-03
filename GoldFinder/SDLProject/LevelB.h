#include "Scene.h"

class LevelB : public Scene {
public:
    int ENEMY_COUNT = 50;
    int GOLD_COUNT = 1;
    GLuint font_texture_id;
    
    ~LevelB();
    
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;
};
