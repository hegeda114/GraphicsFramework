//
// Created by hegeda on 2021-02-11.
//

#include "Point.h"
#include "glm.hpp"
#include <iostream>
#include "Shaders.h"
using namespace glm;

Point::Point(vec2 position) : Geometry() {
    p = position;
}

void Point::create() {
    float positions[2] = { p.x, p.y };
    glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr);
}

void Point::Draw() {
    int colorLocation = glGetUniformLocation(Shaders::shaderProgramId, "color");
    glUniform4f(colorLocation, color[0], color[1], color[2], color[3]);

    glBindVertexArray(vao);
    glPointSize(size);
    glDrawArrays(GL_POINTS, 0, 1);
}

bool Point::isInside(float x, float y) const {
    if(abs(x - p.x) < 0.05 && abs(y - p.y) < 0.05) {
        return true;
    }
    return false;
}

void Point::Grab(float toX, float toY) {
    p.x = toX;
    p.y = toY;
}

bool Point::isMovable() const {
    return true;
}

void Point::changeSize(float size) {
    this->size = size;
}

void Point::toString() const {
    std::cout << "Point " << "\tposX: " << p.x << " posY: " << p.y;
}

Point::Point(vec2 position, const float *color) : Point(position) {
    for(int i = 0; i < 4; i++) {
        this->color[i] = color[i];
    }
}

void Point::simulate(float timestep) {
    vel.x += gravity.x * timestep;
    vel.y += gravity.y * timestep;
    p.x += vel.x * timestep;
    p.y += vel.y * timestep;

//    ball.vel.x += gravity.x * timeStep;
//    ball.vel.y += gravity.y * timeStep;
//    ball.pos.x += ball.vel.x * timeStep;
//    ball.pos.y += ball.vel.y * timeStep;
//
//    if (ball.pos.x < 0.0) {
//        ball.pos.x = 0.0;
//        ball.vel.x = -ball.vel.x;
//    }
//    if (ball.pos.x > simWidth) {
//        ball.pos.x = simWidth;
//        ball.vel.x = -ball.vel.x;
//    }
//    if (ball.pos.y < 0.0) {
//        ball.pos.y = 0.0;
//        ball.vel.y = -ball.vel.y;
//    }
}

