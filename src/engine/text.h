#pragma once
#include <map>
#include <string>
#include "../../lib/glm/glm.hpp"

struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

class TextRenderer {
public:
    TextRenderer();
    int LoadFont(const char* path, int size);
    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);
    void Draw(const std::string &s, double x, double y, float h);
private:
    std::map<char, Character> m_characters;
    unsigned int m_vertexArrayObject, m_vertexBufferObject;
};
