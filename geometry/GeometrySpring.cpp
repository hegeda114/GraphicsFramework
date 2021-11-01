//
// Created by hegeda on 2021-11-01.
//

#include "GeometrySpring.h"

GeometrySpring::GeometrySpring(const glm::vec2& start, const glm::vec2& end) :
    Geometry(), m_startPoint(start), m_endPoint(end) {
    m_defaultColor = {0.3f, 0.8f, 0.3f, 1.0f};
    m_color = m_defaultColor;
}

void GeometrySpring::setStartPoint(const glm::vec2& start) {
    m_startPoint = start;
}

void GeometrySpring::setEndPoint(const glm::vec2& end) {
    m_endPoint = end;
}

void GeometrySpring::setLineWidth(float width) {
    m_lineWidth = width;
}

void GeometrySpring::create() {
    glm::vec2 step = (m_endPoint - m_startPoint) / (float) m_count;
    glm::vec2 prepend = glm::normalize(glm::vec2(-step.y, step.x)) * 0.01f;
    glm::vec2 vertices[m_count];
    vertices[0] = m_startPoint;
    vertices[1] = m_startPoint + step;
    for(size_t i = 2; i < m_count - 1; i++) {
        switch (i % 4) {
            case 1: vertices[i] = m_startPoint + step * (float) i + prepend;
                break;
            case 3: vertices[i] = m_startPoint + step * (float) i - prepend;
                break;
            default:
                vertices[i] = m_startPoint + step * (float) i;
        }
    }
    vertices[m_count-2] = m_startPoint + step * (float) (m_count - 1);
    vertices[m_count-1] = m_endPoint;

    glBufferData(GL_ARRAY_BUFFER, m_count * sizeof(glm::vec2), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void GeometrySpring::draw() const {
    glLineWidth(m_lineWidth);
    glBindVertexArray(vao);
    glDrawArrays(GL_LINE_STRIP, 0, m_count);
}
