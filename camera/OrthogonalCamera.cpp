//
// Created by hegeda on 2021-11-01.
//

#include <ext/matrix_transform.hpp>
#include "OrthogonalCamera.h"

void OrthogonalCamera::setAspectRation(float aspectRatio) {
    glm::vec3 windowSize = {2.0f, 2.0f, 1.0f};
    windowSize.x = windowSize.y * aspectRatio;
    m_viewProjMatrix = {1, 0, 0, 0,
                        0, 1, 0, 0,
                        0, 0, 1, 0,
                        0, 0, 0, 1};

    m_viewProjMatrix = glm::scale(m_viewProjMatrix, glm::vec3(0.5, 0.5, 1));
    m_viewProjMatrix = glm::scale(m_viewProjMatrix, windowSize);
    m_viewProjMatrix = glm::translate(m_viewProjMatrix, position);
    m_viewProjMatrix = glm::inverse(m_viewProjMatrix);
}

void OrthogonalCamera::update(const Shader* shader) const {
    shader->setViewProjMatrix(m_viewProjMatrix);
}
