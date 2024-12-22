#include "shader.h"

#include <GLES3/gl3.h>
#include <iostream>
#include <fstream>
#include <sstream>

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


int Shader::compileShader(const char* path, GLenum shaderType, GLuint* outShaderId) {
    auto fileContent = readFile(path);
    const char* code = fileContent.c_str();

    GLuint shaderId = glCreateShader(shaderType); 
    glShaderSource(shaderId, 1, &code, NULL); 
    glCompileShader(shaderId); 

    *outShaderId = shaderId;

    // print compile errors if any
    int success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

    if(!success) {
        char infoLog[512];
        glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\nFile: " << path << "\n" << infoLog << std::endl;
    };

    std::cout << "Shader loaded: " << path << std::endl;

    return success;
}

Shader::Shader() {}

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    // read files and compile shader
    GLuint vertexShaderId, fragmentShaderId;
    compileShader(vertexPath, GL_VERTEX_SHADER, &vertexShaderId);
    compileShader(fragmentPath, GL_FRAGMENT_SHADER, &fragmentShaderId);

    // link all shaders into program 
    Id = glCreateProgram();
    glAttachShader(Id, vertexShaderId);
    glAttachShader(Id, fragmentShaderId);
    glLinkProgram(Id);

    int success;
    char infoLog[512];
    glGetProgramiv(Id, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(Id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
      
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
}

void Shader::use() {
    glUseProgram(Id);
}
