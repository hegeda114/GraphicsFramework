//
// Created by hegeda on 2021-02-10.
//

#include "Circle.h"
#include <glew.h>
#include "glm.hpp"
#include <vector>
#include <iostream>
#include "Shaders.h"
using namespace glm;

Circle::Circle(vec2 center, int radius, vec4 color) {
    c = center;
    r = radius;
    this->color = color;
}

void Circle::create() {
    std::vector<float> positions = {
            -0.5f + c.x, -0.5f + c.y,
            0.0f + c.x, 0.5f + c.y,
            0.5f + c.x, -0.5f + c.y
    };

    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), &positions[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); //csak pozíciónk van még
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr);
}

void Circle::Draw() {
    int colorLocation = glGetUniformLocation(Shaders::shaderProgramId, "color");
    glUniform4f(colorLocation, color[0], color[1], color[2], color[3]);

    glBindVertexArray(vao);
    glPointSize(7);
    glDrawArrays(GL_POINTS, 0, 3);
}

void Circle::Grab(float toX, float toY)  {
    //TODO implement
}

bool Circle::isInside(float x, float y) const {
    false; //TODO javítani
}

void Circle::toString() const {
    std::cout << "Circle" << std::endl;
};