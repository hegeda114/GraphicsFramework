//
// Created by hegeda on 2021-10-03.
//

#include "Vector.h"

Vector::Vector(vec2 start, vec2 end) : HelperGeometry(),
startPoint(start), endPoint(end) {
    defaultColor = {0.8f, 0.3f, 0.3f, 1.0f};
    color = {0.8f, 0.3f, 0.3f, 1.0f};
    name = "vector";
}

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
    float h = 0.015f;
    float w = 0.02f;
    vec2 dir = normalize(startPoint - endPoint);
    vec2 mid = endPoint + h * dir;
    vec2 left = mid + w * vec2(dir.y, -dir.x);
    vec2 right = mid - w * vec2(dir.y, -dir.x);
    //vec2 vertices[2] = {startPoint, endPoint};
    vec2 vertices[6] = {startPoint, endPoint,
                        endPoint, left,
                        right, endPoint};

    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(vec2), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void Vector::draw() {
    int colorLocation = glGetUniformLocation(Shaders::shaderProgramId, "color");
    glUniform4f(colorLocation, color[0], color[1], color[2], color[3]);

    glLineWidth(this->lineWidth);
    glBindVertexArray(vao);
    glDrawArrays(GL_LINES, 0, 6);
}
