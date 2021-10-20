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
    const int count = 30;
    glm::vec2 step = (endPoint - startPoint) / (float) count;
    glm::vec2 prepend = glm::normalize(glm::vec2(-step.y, step.x)) * 0.01f;
    glm::vec2 vertices[count];
    vertices[0] = startPoint;
    vertices[1] = startPoint + step;
    for(int i = 2; i < count - 1; i++) {
        switch (i % 4) {
            case 1: vertices[i] = startPoint + step * (float) i + prepend;
                break;
            case 3: vertices[i] = startPoint + step * (float) i - prepend;
                break;
            default:
                vertices[i] = startPoint + step * (float) i;
        }
    }
    vertices[count-2] = startPoint + step * (float) (count - 1);
    vertices[count-1] = endPoint;

    //glm::vec2 vertices[2] = {startPoint, endPoint};

    glBufferData(GL_ARRAY_BUFFER, count * sizeof(glm::vec2), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void GeometryLine::draw() {
    int colorLocation = glGetUniformLocation(Shaders::shaderProgramId, "color");
    glUniform4f(colorLocation, m_color[0], m_color[1], m_color[2], m_color[3]);

    glLineWidth(lineWidth);
    glBindVertexArray(vao);
    glDrawArrays(GL_LINE_STRIP, 0, 30);
}
