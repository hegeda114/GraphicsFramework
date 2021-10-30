//
// Created by hegeda on 2021-10-12.
//

#include "SimulationProperties.h"

SimulationProperties::SimulationProperties(glm::vec2 position) {
    m_position = position;
}

void SimulationProperties::setVelocity(double x, double y) {
    m_velocity.x = (float) x;
    m_velocity.y = (float) y;
}

void SimulationProperties::setVelocity(const glm::vec2 &velocity) {
    setVelocity(velocity.x, velocity.y);
}

void SimulationProperties::addForce(double x, double y) {
    m_forces.emplace_back(glm::vec2(x, y));
}

void SimulationProperties::addForce(const glm::vec2 &force) {
    m_forces.push_back(force);
}

glm::vec2 SimulationProperties::getResultaltForces() const {
    glm::vec2 forcesSum = {0, 0};
    for (const auto& force : m_forces) {
        forcesSum += force;
    }
    return forcesSum;
}

void SimulationProperties::explicitEuler(const SimulationState &simState) {
    double timestep = simState.getTimestep();
    glm::vec2 resultaltForce = getResultaltForces();

    m_velocity.x += resultaltForce.x * (float) timestep;
    m_velocity.y += resultaltForce.y * (float) timestep;
    m_position.x += m_velocity.x * (float) timestep;
    m_position.y += m_velocity.y * (float) timestep;
    m_forces.clear();
}

const glm::vec2 &SimulationProperties::getVelocity() const {
    return m_velocity;
}

const glm::vec2& SimulationProperties::getPosition() const {
    return m_position;
}

void SimulationProperties::setPosition(double x, double y) {
    setPosition({x, y});
}

void SimulationProperties::setPosition(const glm::vec2 &position) {
    m_position = position;
}

void SimulationProperties::clearForces() {
    m_forces.clear();
}
