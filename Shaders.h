//
// Created by hegeda on 2021-02-10.
//

#ifndef CHERNO01_SHADERS_H
#define CHERNO01_SHADERS_H
#include <iostream>

class Shaders {
public:
    static unsigned int shaderProgramId;
    const std::string vertexShader = R"(
        #version 330 core
        layout(location = 0) in vec4 position;

        void main()
        {
           gl_Position = position;
        }
    )";
    const std::string fragmentShader  = R"(
        #version 330 core
        precision highp float;

        uniform vec4 color;
        out vec4 outColor;

        void main()
        {
           outColor = color;
        }
    )";
    static unsigned int CompileShader(unsigned int type, const std::string& src);
    void CreateShader();
    void Bind();
};

#endif //CHERNO01_SHADERS_H
