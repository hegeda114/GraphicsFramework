//
// Created by hegeda on 2021-02-11.
//

#include "Point.h"
#include "glm.hpp"
#include <iostream>
using namespace glm;

Point::Point(vec2 position) : Geometry(),
    center(position),
    velocityVector(center, center),
    forceVector(center, center) { }

Point::Point(vec2 position, const float *color) : Point(position) {
    for(int i = 0; i < 4; i++) {
        this->color[i] = color[i];
    }
}

void Point::create() {
    vec2 vertices[samples];
    for (size_t i = 0; i < samples; i++) {
        float fi = (float) i * (float) (2 * M_PI) / (float) samples;
        vertices[i] = vec2(cosf(fi) * radius + center.x, sinf(fi) * radius + center.y);
    }

    glBufferData(GL_ARRAY_BUFFER, samples * sizeof(vec2), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void Point::draw() {
    int colorLocation = glGetUniformLocation(Shaders::shaderProgramId, "color");
    glUniform4f(colorLocation, color[0], color[1], color[2], color[3]);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, samples);
}

bool Point::isInside(double x, double y) const {
    if(abs(x - center.x) < radius && abs(y - center.y) < radius) {
        return true;
    }
    return false;
}

void Point::move(double toX, double toY) {
    center.x = toX;
    center.y = toY;
}

void Point::setVel(double x, double y) {
    vel.x = x;
    vel.y = y;
}

void Point::explicitEuler(SimulationState simState) {
    double timestep = simState.getTimestep();
    vec2 gravity = simState.getGravity();

    vel.x += gravity.x * timestep;
    vel.y += gravity.y * timestep;
    center.x += vel.x * timestep;
    center.y += vel.y * timestep;

    if (center.x < simState.getBoundingLeft()) {
        center.x = 2 * simState.getBoundingLeft() - center.x;
        vel.x = -vel.x;
    }
    if (center.x > simState.getBoundingRight()) {
        center.x = 2 * simState.getBoundingRight() - center.x;
        vel.x = -vel.x;
    }
    if (center.y < simState.getBoundingBottom()) {
        center.y = 2 * simState.getBoundingBottom() - center.y;
        vel.y = -vel.y;
    }
}

void Point::showHelpers() {
    velocityVector.setStartPoint(center);
    velocityVector.setEndPoint(center + 0.05f*vel);
    velocityVector.create();

    velocityVector.draw();
}
