//
// Created by hegeda on 2021-10-03.
//

#include "Geometry.h"

void Geometry::setColor(double red, double green, double blue, double alpha) {
    m_color = {red, green, blue, alpha};
}

void Geometry::setColorToDefault() {
    m_color = m_defaultColor;
}

void Geometry::setPosition(const glm::vec2 &position) {
    m_position = position;
}

void Geometry::update(const Shader* shader) const {
    shader->setColor(m_color);
}
