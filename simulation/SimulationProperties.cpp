//
// Created by hegeda on 2021-10-12.
//

#include "SimulationProperties.h"

SimulationProperties::SimulationProperties(glm::vec2 position) {
    m_position = position;
}

void SimulationProperties::setVelocity(float x, float y) {
    m_velocity.x = x;
    m_velocity.y = y;
}

void SimulationProperties::setVelocity(const glm::vec2 &velocity) {
    setVelocity(velocity.x, velocity.y);
}

void SimulationProperties::addForce(float x, float y) {
    m_forces.emplace_back(glm::vec2(x, y));
}

void SimulationProperties::addForce(const glm::vec2 &force) {
    m_forces.push_back(force);
}

glm::vec2 SimulationProperties::getResultantForces() const {
    glm::vec2 forcesSum = {0, 0};
    for (const auto& force : m_forces) {
        forcesSum += force;
    }
    return forcesSum;
}

void SimulationProperties::explicitEuler(const GlobalSimulationSettings* globalSimulationSettings) {
    double timestep = globalSimulationSettings->getTimestep();
    glm::vec2 resultantForce = getResultantForces();

    m_velocity.x += resultantForce.x * (float) timestep;
    m_velocity.y += resultantForce.y * (float) timestep;
    m_position.x += m_velocity.x * (float) timestep;
    m_position.y += m_velocity.y * (float) timestep;

    m_resultantForcesForHelper = resultantForce;
    clearForces();
}

void SimulationProperties::rungeKuttaSecondOrder(const GlobalSimulationSettings* globalSimulationSettings) {
    double timestep = globalSimulationSettings->getTimestep();
//    glm::vec2 resultantForce = getResultantForces();

    m_velocity.x += m_b1.x * (float) timestep;
    m_velocity.y += m_b1.y * (float) timestep;
    m_position.x += m_b2.x * (float) timestep;
    m_position.y += m_b2.y * (float) timestep;

//    m_resultantForcesForHelper = resultantForce;
    clearForces();
}

const glm::vec2 &SimulationProperties::getVelocity() const {
    return m_velocity;
}

const glm::vec2& SimulationProperties::getPosition() const {
    return m_position;
}

void SimulationProperties::setPosition(float x, float y) {
    setPosition({x, y});
}

void SimulationProperties::setPosition(const glm::vec2 &position) {
    m_position = position;
}

void SimulationProperties::clearForces() {
    m_forces.clear();
}

glm::vec2 SimulationProperties::getResultantForcesForHelpers() const {
    return m_resultantForcesForHelper;
}

void SimulationProperties::setA1(const glm::vec2 &value) {
    m_a1 = value;
}

void SimulationProperties::setA2(const glm::vec2 &value) {
    m_a2 = value;
}

void SimulationProperties::setB1(const glm::vec2 &value) {
    m_b1 = value;
}

void SimulationProperties::setB2(const glm::vec2 &value) {
    m_b2 = value;
}
