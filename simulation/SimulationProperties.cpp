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

    m_position.x += m_b.first.x * (float) timestep;
    m_position.y += m_b.first.y * (float) timestep;
    m_velocity.x += m_b.second.x * (float) timestep;
    m_velocity.y += m_b.second.y * (float) timestep;

//    m_resultantForcesForHelper = resultantForce;
//    clearForces();
}


void SimulationProperties::rungeKuttaFourthOrder(const GlobalSimulationSettings *globalSimulationSettings) {
    double timestep = globalSimulationSettings->getTimestep();
//    glm::vec2 resultantForce = getResultantForces();

    m_position.x +=  (m_a.first.x + 2.0f * m_b.first.x + 2.0f * m_c.first.x + m_d.first.x) * (float) timestep / 6.0f;
    m_position.y += (m_a.first.y + 2.0f * m_b.first.y + 2.0f * m_c.first.y + m_d.first.y) * (float) timestep / 6.0f;
    m_velocity.x += (m_a.second.x + 2.0f * m_b.second.x + 2.0f * m_c.second.x + m_d.second.x) * (float) timestep / 6.0f;
    m_velocity.y += (m_a.second.y + 2.0f * m_b.second.y + 2.0f * m_c.second.y + m_d.second.y) * (float) timestep / 6.0f;

//    m_resultantForcesForHelper = resultantForce;
//    clearForces();
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

void SimulationProperties::addToA(const glm::vec2 &a1, const glm::vec2 &a2) {
    m_a.first += a1;
    m_a.second += a2;
}

void SimulationProperties::addToB(const glm::vec2 &b1, const glm::vec2 &b2) {
    m_b.first += b1;
    m_b.second += b2;
}

void SimulationProperties::addToC(const glm::vec2 &c1, const glm::vec2 &c2) {
    m_c.first += c1;
    m_c.second += c2;
}

void SimulationProperties::addToD(const glm::vec2 &d1, const glm::vec2 &d2) {
    m_d.first += d1;
    m_d.second += d2;
}

void SimulationProperties::clearABCD() {
    m_a = std::pair<glm::vec2, glm::vec2>(glm::vec2(0, 0), glm::vec2(0, 0));
    m_b = std::pair<glm::vec2, glm::vec2>(glm::vec2(0, 0), glm::vec2(0, 0));
    m_c = std::pair<glm::vec2, glm::vec2>(glm::vec2(0, 0), glm::vec2(0, 0));
    m_d = std::pair<glm::vec2, glm::vec2>(glm::vec2(0, 0), glm::vec2(0, 0));
}

std::pair<glm::vec2, glm::vec2> SimulationProperties::getA() const {
    return m_a;
}

std::pair<glm::vec2, glm::vec2> SimulationProperties::getB() const {
    return m_b;
}

std::pair<glm::vec2, glm::vec2> SimulationProperties::getC() const {
    return m_c;
}

std::pair<glm::vec2, glm::vec2> SimulationProperties::getD() const {
    return m_d;
}

