//
// Created by hegeda on 2021-10-16.
//

#include "GeometryVector.h"


GeometryVector::GeometryVector(const glm::vec2& start, const glm::vec2& end) :
Geometry(), m_startPoint(start), m_endPoint(end) {
    m_defaultColor = {0.3f, 0.3f, 0.8f, 1.0f};
    m_color = m_defaultColor;
}

void GeometryVector::setStartPoint(const glm::vec2& start) {
    m_startPoint = start;
}

void GeometryVector::setEndPoint(const glm::vec2& end) {
    m_endPoint = end;
}

void GeometryVector::setLineWidth(float width) {
    m_lineWidth = width;
}

void GeometryVector::create() {
    float h = 0.015f;
    float w = 0.02f;
    glm::vec2 dir = normalize(m_startPoint - m_endPoint);
    glm::vec2 mid = m_endPoint + h * dir;
    glm::vec2 left = mid + w * glm::vec2(dir.y, -dir.x);
    glm::vec2 right = mid - w * glm::vec2(dir.y, -dir.x);
    glm::vec2 vertices[6] = {m_startPoint, m_endPoint,
                             m_endPoint, left,
                             right, m_endPoint};

    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec2), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void GeometryVector::draw() const {
    glLineWidth(m_lineWidth);
    glBindVertexArray(vao);
    glDrawArrays(GL_LINES, 0, 6);
}
