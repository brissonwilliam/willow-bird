#pragma once

#include <GLES3/gl3.h>
class Shader {
    public:
        Shader();
        Shader(const char* vertexPath, const char* fragmentPath);
        unsigned int Id;
        void use();

    private:
        int compileShader(const char* path, GLenum shaderType, GLuint* outShaderId) ;
};
