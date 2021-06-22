//
// Created by hegeda on 2021-02-10.
//

#include "Shaders.h"
#include <iostream>
#include "glew.h"

unsigned int Shaders::shaderProgramId = 0;

unsigned int Shaders::CompileShader(unsigned int type, const std::string& src) {
    unsigned int id = glCreateShader(type);
    const char* source = src.c_str();
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    //gets error message after shader compilation
    if(result == GL_FALSE) {
        int logLength;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
        char * logMessage = new char[logLength];
        glGetShaderInfoLog(id, logLength, &logLength, logMessage);
        std::cout << "Faild to compile "
                  << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!"
                  << std::endl;
        std::cout << logMessage << std::endl;
        glDeleteShader(id);
        delete[] logMessage;
        return 0;
    }

    return id;
}

void Shaders::CreateShader() {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    shaderProgramId = program;
}

void Shaders::Bind() {
    //setting uniforms TODO karban tartani
    int colorLocation = glGetUniformLocation(Shaders::shaderProgramId, "color");
    glUniform4f(colorLocation, 0.7, 0.7, 0.7, 1);
}
