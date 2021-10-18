//
// Created by hegeda on 2021-10-16.
//

#include "GeometryLine.h"

GeometryLine::GeometryLine(glm::vec2 start, glm::vec2 end) : Geometry(), startPoint(start), endPoint(end) {
    m_defaultColor = {0.3f, 0.8f, 0.3f, 1.0f};
    m_color = {0.3f, 0.8f, 0.3f, 1.0f};
}

void GeometryLine::setStartPoint(glm::vec2 start) {
    this->startPoint = start;
}

void GeometryLine::setEndPoint(glm::vec2 end) {
    this->endPoint = end;
}

void GeometryLine::setLineWidth(double width) {
    this->lineWidth = width;
}

void GeometryLine::create() {
    glm::vec2 vertices[2] = {startPoint, endPoint};

    glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(glm::vec2), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void GeometryLine::draw() {
    int colorLocation = glGetUniformLocation(Shaders::shaderProgramId, "color");
    glUniform4f(colorLocation, m_color[0], m_color[1], m_color[2], m_color[3]);

    glLineWidth(lineWidth);
    glBindVertexArray(vao);
    glDrawArrays(GL_LINES, 0, 2);
}
