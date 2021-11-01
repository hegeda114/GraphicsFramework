//
// Created by hegeda on 2021-11-01.
//

#ifndef SHADER_H
#define SHADER_H
#include <iostream>
#include "glm.hpp"

class Shader {
private:
    unsigned int m_shaderProgramId = -1;
    const std::string m_vertexShader = R"(
        #version 330 core
        layout(location = 0) in vec4 position;

        void main()
        {
           gl_Position = position;
        }
    )";
    const std::string m_fragmentShader  = R"(
        #version 330 core
        precision highp float;

        uniform vec4 color;
        out vec4 outColor;

        void main()
        {
           outColor = color;
        }
    )";
    static unsigned int compileShader(unsigned int type, const std::string& src);
public:
    Shader() = default;
    ~Shader();

    void createShader();

    void setColor(const glm::vec4& color) const;

    void use() const;
};

#endif //SHADER_H
