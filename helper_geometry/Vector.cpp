//
// Created by hegeda on 2021-10-03.
//

#include "Vector.h"

Vector::Vector(vec2 start, vec2 end) : startPoint(start), endPoint(end) { }

void Vector::setStartPoint(vec2 start) {
    this->startPoint = start;
}

void Vector::setEndPoint(vec2 end) {
    this->endPoint = end;
}

void Vector::setLineWidth(double width) {
 this->lineWidth = width;
}

void Vector::create() {
    vec2 vertices[2] = {startPoint, endPoint};

    glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(vec2), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void Vector::draw() {
    int colorLocation = glGetUniformLocation(Shaders::shaderProgramId, "color");
    glUniform4f(colorLocation, color[0], color[1], color[2], color[3]);

    //glLineWidth(this->lineWidth);
    glBindVertexArray(vao);
    glDrawArrays(GL_LINES, 0, 2);
}
