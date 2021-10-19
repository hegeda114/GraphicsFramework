//
// Created by hegeda on 2021-10-12.
//

#include "PhysicalProperties.h"

PhysicalProperties::PhysicalProperties(glm::vec2 position) {
    m_position = position;
}

void PhysicalProperties::setVelocity(double x, double y) {
    m_velocity.x = (float) x;
    m_velocity.y = (float) y;
}

void PhysicalProperties::setVelocity(const glm::vec2 &velocity) {
    setVelocity(velocity.x, velocity.y);
}

void PhysicalProperties::addForce(double x, double y) {
    m_forces.emplace_back(glm::vec2(x, y));
}

void PhysicalProperties::addForce(const glm::vec2 &force) {
    m_forces.push_back(force);
}

glm::vec2 PhysicalProperties::getResultaltForces() const {
    glm::vec2 forcesSum = {0, 0};
    for (const auto& force : m_forces) {
        forcesSum += force;
    }
    return forcesSum;
}

void PhysicalProperties::explicitEuler(const SimulationState &simState) {
    double timestep = simState.getTimestep();
    glm::vec2 resultaltForce = getResultaltForces();

    m_velocity.x += resultaltForce.x * (float) timestep;
    m_velocity.y += resultaltForce.y * (float) timestep;
    m_position.x += m_velocity.x * (float) timestep;
    m_position.y += m_velocity.y * (float) timestep;

    if (m_position.x < simState.getBoundingLeft()) {
        m_position.x = 2 * simState.getBoundingLeft() - m_position.x;
        m_velocity.x = -m_velocity.x;
    }
    if (m_position.x > simState.getBoundingRight()) {
        m_position.x = 2 * simState.getBoundingRight() - m_position.x;
        m_velocity.x = -m_velocity.x;
    }
    if (m_position.y < simState.getBoundingBottom()) {
        m_position.y = 2 * simState.getBoundingBottom() - m_position.y;
        m_velocity.y = -m_velocity.y;
    }
    m_forces.clear();
}

const glm::vec2 &PhysicalProperties::getVelocity() const {
    return m_velocity;
}

const glm::vec2& PhysicalProperties::getPosition() const {
    return m_position;
}

void PhysicalProperties::setPosition(double x, double y) {
    setPosition({x, y});
}

void PhysicalProperties::setPosition(const glm::vec2 &position) {
    m_position = position;
}
