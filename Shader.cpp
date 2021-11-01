//
// Created by hegeda on 2021-11-01.
//

#include "Shader.h"
#include <iostream>
#include "glew.h"

unsigned int Shader::compileShader(unsigned int type, const std::string& src) {
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

void Shader::createShader() {
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, m_vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, m_fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    m_shaderProgramId = program;
}

void Shader::setColor(const glm::vec4& color) const {
    int colorLocation = glGetUniformLocation(m_shaderProgramId, "color");
    glUniform4f(colorLocation, color.x, color.y, color.z, color.w);
}

void Shader::use() const {
    glUseProgram(m_shaderProgramId);
}

Shader::~Shader() {
    glDeleteProgram(m_shaderProgramId);
}

void Shader::setViewProjMatrix(const glm::mat4 &viewMx) const {
    const GLfloat matrix[16] = {
            viewMx[0][0], viewMx[0][1], viewMx[0][2], viewMx[0][3],
            viewMx[1][0], viewMx[1][1], viewMx[1][2], viewMx[1][3],
            viewMx[2][0], viewMx[2][1], viewMx[2][2], viewMx[2][3],
            viewMx[3][0], viewMx[3][1], viewMx[3][2], viewMx[3][3]
    };
    int colorLocation = glGetUniformLocation(m_shaderProgramId, "viewProjMatrix");
    glUniformMatrix4fv(colorLocation, 1, GL_TRUE, matrix);
}
