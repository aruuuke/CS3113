#include "Scene.h"


class Start : public Scene {
public:
    // ————— STATIC ATTRIBUTES ————— //
    GLuint font_texture_id;
    
    // ————— CONSTRUCTOR ————— //
    ~Start();
    
    // ————— METHODS ————— //
    void initialise() override;
    void update(float deltaTime) override;
    void render(ShaderProgram *program) override;
};

