//
// Created by hegeda on 2021-10-16.
//

#include "GeometryLine.h"

GeometryLine::GeometryLine(const glm::vec2& start, const glm::vec2& end) :
    Geometry(), m_startPoint(start), m_endPoint(end) {
    m_defaultColor = {0.3f, 0.8f, 0.3f, 1.0f};
    m_color = m_defaultColor;
}

void GeometryLine::setStartPoint(const glm::vec2& start) {
    m_startPoint = start;
}

void GeometryLine::setEndPoint(const glm::vec2& end) {
    m_endPoint = end;
}

void GeometryLine::setLineWidth(float width) {
    m_lineWidth = width;
}

void GeometryLine::create() {
    glm::vec2 vertices[2] = {m_startPoint, m_endPoint};

    glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(glm::vec2), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void GeometryLine::draw() const {
    glLineWidth(m_lineWidth);
    glBindVertexArray(vao);
    glDrawArrays(GL_LINE_STRIP, 0, 2);
}
