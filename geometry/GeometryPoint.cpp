//
// Created by hegeda on 2021-02-11.
//

#include "GeometryPoint.h"
#include "glm.hpp"
#include <iostream>

GeometryPoint::GeometryPoint(glm::vec2 position, double radius):
    m_radius(radius) {
    m_position = position;
    m_defaultColor = {0.87f, 0.9f, 0.4f, 1.0f};
    m_color = m_defaultColor;
}

void GeometryPoint::create() {
    glm::vec2 vertices[100];
    for (size_t i = 0; i < 100; i++) {
        float fi = (float) i * (float) (2 * M_PI) / (float) 100;
        vertices[i] = glm::vec2(cosf(fi) * m_radius + m_position.x, sinf(fi) * m_radius + m_position.y);
    }

    glBufferData(GL_ARRAY_BUFFER, 100 * sizeof(glm::vec2), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void GeometryPoint::draw() {
    int colorLocation = glGetUniformLocation(Shaders::shaderProgramId, "color");
    glUniform4f(colorLocation, m_color[0], m_color[1], m_color[2], m_color[3]);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 100);
}