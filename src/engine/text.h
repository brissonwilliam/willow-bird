#pragma once
#include <map>
#include <string>
#include <glm/glm.hpp>
#include "shader.h"

struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

class TextRenderer {
public:
    TextRenderer();
    TextRenderer(glm::mat4 projection);
    int LoadFont(const char* path, int size);
    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);
    void Draw(const std::string &s, double x, double y, float h);

private:
    Shader m_shader;
    std::map<char, Character> m_characters;
    uint m_vertexArrayObject;
    uint m_vertexBufferObject;

    void allocateGlQuads(); 
};
