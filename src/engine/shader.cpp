#include "shader.h"

#include <GLES3/gl3.h>
#include <iostream>
#include <fstream>
#include <sstream>

int Shader::compileShader(GLenum shaderType, const char* sourceCode, GLuint* outShaderId) {
    GLuint shaderId = glCreateShader(shaderType); 
    glShaderSource(shaderId, 1, &sourceCode, NULL); 
    glCompileShader(shaderId); 

    *outShaderId = shaderId;

    // print compile errors if any
    int success;
    char infoLog[512];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

    if(!success) {
        glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    return success;
}

std::string readFile(const char* path) {
    std::ifstream file;
    std::string content;

    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try {
        // open files
        file.open(path);

        // read file's buffer contents into streams
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        content   = stream.str();
    }
    catch(std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    return content;
}

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    const char* vShaderCode = readFile(vertexPath).c_str();
    const char* fShaderCode = readFile(fragmentPath).c_str();

    // compile shader
    GLuint vertexShaderId, fragmentShaderId;
    compileShader(GL_VERTEX_SHADER, vShaderCode, &vertexShaderId);
    compileShader(GL_FRAGMENT_SHADER, fShaderCode, &fragmentShaderId);

    // link all shaders into program 
    m_programId = glCreateProgram();
    glAttachShader(m_programId, vertexShaderId);
    glAttachShader(m_programId, fragmentShaderId);
    glLinkProgram(m_programId);

    int success;
    char infoLog[512];
    glGetProgramiv(m_programId, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(m_programId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
      
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

}

void Shader::use() {
    glUseProgram(m_programId);
}
