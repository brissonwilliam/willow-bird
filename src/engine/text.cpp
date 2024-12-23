#include "text.h"
#include "shader.h"
#include <GLES3/gl3.h>
#include <freetype2/ft2build.h>
#include <iostream>
#include <ostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include FT_FREETYPE_H
#include FT_GLYPH_H

TextRenderer::TextRenderer() {}

TextRenderer::TextRenderer(glm::mat4 projection) {
    m_shader = Shader("assets/shaders/text_vertex.glsl", "assets/shaders/text_fragment.glsl");

    m_shader.use();
    glUniformMatrix4fv(glGetUniformLocation(m_shader.Id, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}

int TextRenderer::LoadFont(const char* filePath, int fontSize) {
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return -1;
    }

    FT_Face face;
    if (FT_New_Face(ft, filePath, 0, &face)) {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;  
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
        return -1;
    }

    // this lets font size be calculated automatically based on height
    const int fontSizeWidthAuto = 0; 
    FT_Set_Pixel_Sizes(face, fontSizeWidthAuto, fontSize); // todo: maybe scale this based on display dimmensions or a config


    // OpenGL requires that textures all have a 4-byte alignment e.g.
    // their size is always a multiple of 4 bytes. Normally this won't be a problem since most textures have a width 
    // that is a multiple of 4 and/or use 4 bytes per pixel, but since we now only use a single byte per pixel, the texture can have any possible width.
    // By setting its unpack alignment to 1 we ensure there are no alignment issues (which could cause segmentation faults).
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 

    // load a couple ascii characters
    for (unsigned char c = 32; c < 128; c++)
    {
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }

        // Generate texture
        //
        // note here is that we use GL_RED as the texture's internalFormat and format arguments.
        // The bitmap generated from the glyph is a grayscale 8-bit image where each color is represented by a single byte.
        // For this reason we'd like to store each byte of the bitmap buffer as the texture's single color value.
        // We accomplish this by creating a texture where each byte corresponds to the texture color's red component (first byte of its color vector).
        // If we use a single byte to represent the colors of a texture we do need to take care of a restriction of OpenGL:
        uint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture, // TextureID
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows), // Glyph size
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top), // Offset from left top of bitmap 
            static_cast<unsigned int>(face->glyph->advance.x)
        };
        m_characters.insert(std::pair<char, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    // OpenGL requires that textures all have a 4-byte alignment e.g. their size is always a multiple of 4 bytes. Normally this won't be a problem since most textures have a width that is a multiple of 4 and/or use 4 bytes per pixel, but since we now only use a single byte per pixel, the texture can have any possible width. By setting its unpack alignment to 1 we ensure there are no alignment issues (which could cause segmentation faults).

    // free some free type resources
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    allocateGlQuads();

    std::cout << "True type font loaded succesfuly. Characters: " << m_characters.size() << std::endl;

    return 0;
}

void TextRenderer::allocateGlQuads() {
    // configure VAO/VBO for texture quads
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);

    glGenBuffers(1, &m_vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);

    // The 2D quad requires 6 vertices of 4 floats each, so we reserve 6 * 4 floats of memory. Because we'll be updating the content of the VBO's memory quite often we'll allocate the memory with GL_DYNAMIC_DRAW.
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
}

void TextRenderer::RenderText(std::string text, float x, float y, float scale, glm::vec3 color) {
    // use the text shader for drawing calls we will make
    m_shader.use();

    glUniform3f(glGetUniformLocation(m_shader.Id, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_vertexArrayObject);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) 
    {
        Character ch = m_characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },            
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }           
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
