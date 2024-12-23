#pragma once
#include "../engine/asset.h"
#include "../engine/shader.h"
#include <GLFW/glfw3.h>

class Player : public DynamicAsset {
public:
    Player();
    void Load() override;
    void Update(double elapsed);
    void Render();

    // Used to re-apply velocity when it gets nullified with inputs
    // For example when holding right, pressing left, release left, we still want to move right
    bool rightPressed = false;
    bool leftPressed = false;
    bool upPressed = false;
    bool downPressed = false;

private:
    Shader m_shader;
    unsigned int m_vertexArrayObj;
    unsigned int m_vertexBufferObj;
    int m_shaderUniformPos;
    int m_shaderUniformColorMut;
};
