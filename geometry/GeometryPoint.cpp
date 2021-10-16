//
// Created by hegeda on 2021-02-11.
//

#include "GeometryPoint.h"
#include "glm.hpp"
#include <iostream>

GeometryPoint::GeometryPoint(glm::vec2 position, double radius):
    m_radius(radius) {
    m_position = position;
    m_defaultColor = {0.65f, 0.65f, 0.8f, 1.0f};
    m_color = m_defaultColor;
}

void GeometryPoint::create() {
    glm::vec2 vertices[m_samples];
    for (size_t i = 0; i < m_samples; i++) {
        float fi = (float) i * (float) (2 * M_PI) / (float) m_samples;
        vertices[i] = glm::vec2(cosf(fi) * m_radius + m_position.x, sinf(fi) * m_radius + m_position.y);
    }

    glBufferData(GL_ARRAY_BUFFER, m_samples * sizeof(glm::vec2), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void GeometryPoint::draw() {
    int colorLocation = glGetUniformLocation(Shaders::shaderProgramId, "color");
    glUniform4f(colorLocation, m_color[0], m_color[1], m_color[2], m_color[3]);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, m_samples);
}