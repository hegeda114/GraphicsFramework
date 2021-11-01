//
// Created by hegeda on 2021-02-11.
//

#include "GeometryPoint.h"
#include "glm.hpp"
#include <iostream>

GeometryPoint::GeometryPoint(const glm::vec2& position, double radius):
    m_radius(radius) {
    m_position = position;
    m_defaultColor = {0.87f, 0.9f, 0.4f, 1.0f};
    m_color = m_defaultColor;
}

void GeometryPoint::create() {
    glm::vec2 vertices[m_resolution];
    for(size_t i = 0; i < m_resolution; i++) {
        float fi = (float) i * (float) (2 * M_PI) / (float) m_resolution;
        vertices[i] = glm::vec2(cosf(fi) * m_radius + m_position.x, sinf(fi) * m_radius + m_position.y);
    }

    glBufferData(GL_ARRAY_BUFFER, m_resolution * sizeof(glm::vec2), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void GeometryPoint::draw() const {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, m_resolution);
}