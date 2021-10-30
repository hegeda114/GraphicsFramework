//
// Created by hegeda on 2021-10-03.
//

#include "SimulationState.h"

SimulationMode SimulationState::getSimMode() const {
    return m_simMode;
}

void SimulationState::setSimMode(SimulationMode simulationMode) {
    m_simMode = simulationMode;
}

double SimulationState::getTimestep() const {
    return m_timestep;
}

void SimulationState::setTimestep(double timestep) {
    m_timestep = timestep;
}

glm::vec2 SimulationState::getGravity() const {
    return m_gravity;
}

void SimulationState::setGravity(glm::vec2 gravity) {
    m_gravity = gravity;
}

std::vector<glm::vec2> SimulationState::getGlobalForces() const {
    std::vector<glm::vec2> forces;
    forces.push_back(m_gravity);
    return forces;
}

void SimulationState::setBoundingBox(double top, double right, double bottom, double left) {
    m_boundigBox.insert({Direction::Top, top});
    m_boundigBox.insert({Direction::Right, right});
    m_boundigBox.insert({Direction::Bottom, bottom});
    m_boundigBox.insert({Direction::Left, left});
}

std::map<Direction, double> SimulationState::getBoundigBox() const {
    return m_boundigBox;
}

double SimulationState::getBoundingTop() const {
    return m_boundigBox.at(Direction::Top);
}

double SimulationState::getBoundingRight() const {
    return m_boundigBox.at(Direction::Right);
}

double SimulationState::getBoundingBottom() const {
    return m_boundigBox.at(Direction::Bottom);
}

double SimulationState::getBoundingLeft() const {
    return m_boundigBox.at(Direction::Left);
}

SimulationState::SimulationState(SimulationMode simulationMode, double timestep) {
    m_simMode = simulationMode;
    m_timestep = timestep;
}

SimulationState::SimulationState() {
    m_simMode = SimulationMode::ExplicitEuler;
    m_timestep = 1.0/60.0;
    m_gravity = {0, -9.8};
    setBoundingBox(1, 1, -1, -1);
}
