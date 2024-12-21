#pragma once

#include <GLES3/gl3.h>
class Shader {
    public:
        unsigned int m_programId;
        Shader(const char* vertexPath, const char* fragmentPath);
        void use();

    private:
        int compileShader(GLenum shaderType, const char* sourceCode, GLuint* outShaderId) ;
};
