//
// Created by hegeda on 2021-10-16.
//

#include "GeometryVector.h"


GeometryVector::GeometryVector(glm::vec2 start, glm::vec2 end) : Geometry(),
                                                 startPoint(start), endPoint(end) {
    m_defaultColor = {0.3f, 0.3f, 0.8f, 1.0f};
    m_color = {0.3f, 0.3f, 0.8f, 1.0f};
}

void GeometryVector::setStartPoint(glm::vec2 start) {
    this->startPoint = start;
}

void GeometryVector::setEndPoint(glm::vec2 end) {
    this->endPoint = end;
}

void GeometryVector::setLineWidth(double width) {
    this->lineWidth = width;
}

void GeometryVector::create() {
    float h = 0.015f;
    float w = 0.02f;
    glm::vec2 dir = normalize(startPoint - endPoint);
    glm::vec2 mid = endPoint + h * dir;
    glm::vec2 left = mid + w * glm::vec2(dir.y, -dir.x);
    glm::vec2 right = mid - w * glm::vec2(dir.y, -dir.x);
    glm::vec2 vertices[6] = {startPoint, endPoint,
                             endPoint, left,
                             right, endPoint};

    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec2), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void GeometryVector::draw() {
    int colorLocation = glGetUniformLocation(Shaders::shaderProgramId, "color");
    glUniform4f(colorLocation, m_color[0], m_color[1], m_color[2], m_color[3]);

    glLineWidth(lineWidth);
    glBindVertexArray(vao);
    glDrawArrays(GL_LINES, 0, 6);
}
