#include "player.h"
#include <GL/gl.h>
#include <GLES3/gl3.h>
#include <glm/trigonometric.hpp>

Player::Player() {
    this->att.maxV = Velocity{0.01, 0.01, 0};
    this->att.pos = Position{0, 0, 0};
    this->att.v = Velocity{0, 0, 0};
}

void Player::Load() {
    // make buffers for vertices
    glGenVertexArrays(1, &m_vertexArrayObj);
    glGenBuffers(1, &m_vertexBufferObj);

    // tell gl to store vertices in the array obj to keep track of stride attributes & stuff
    glBindVertexArray(m_vertexArrayObj);

    const float size = 0.4f;
    const float vertices[] = {
    //    x      y      r    g     b
        size,  -size, 1.0f, 0.0f, 0.0f,
        0.0f,  size,  0.0f, 1.0f, 0.0f,
        -size, -size, 0.0f, 0.0f, 1.0f,
    };
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObj); // specify we're using current buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // fill the buffer, using static draw because buffer memory won't change often (never)
    
    // one attrib array describing vertices position (2 components, stride of 5 elements, offset 0)
    // and another for colors (3 components, stride of 5 elements, offset 2)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // load the shader
    m_shader = Shader("assets/shaders/rainbow_vertex.glsl", "assets/shaders/rainbow_fragment.glsl");

    // uniform for position translation
    m_shaderUniformPos = glGetUniformLocation(m_shader.Id, "worldPos");
    m_shaderUniformColorMut = glGetUniformLocation(m_shader.Id, "colorMut");
}

void Player::Render() {
    const float colorpowa = 2.0f;
    const float r = glm::cos(glfwGetTime() * colorpowa) / 3.0f + 0.5f;
    const float g = glm::cos(glfwGetTime() * colorpowa) / 3.0f + 0.5f;
    const float b = glm::cos(glfwGetTime() * colorpowa) / 3.0f + 0.5f;

    m_shader.use();
    glUniform3f(m_shaderUniformPos, att.pos.x, att.pos.y, att.pos.z);
    glUniform3f(m_shaderUniformColorMut, r,g,b);
    glBindVertexArray(m_vertexArrayObj);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Player::Update(double elapsed) {
    Velocity normalVel = GetVelocityNormalized();
    Translate(normalVel.x * elapsed, normalVel.y * elapsed, this->att.v.z * elapsed);
}

