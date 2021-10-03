//
// Created by hegeda on 2021-10-03.
//

#include "SimulationState.h"

SimulationMode SimulationState::getSimMode() const {
    return simMode;
}

void SimulationState::setSimMode(SimulationMode simulationMode) {
    simMode = simulationMode;
}

double SimulationState::getTimestep() const {
    return timestep;
}

void SimulationState::setTimestep(double timestep) {
    this->timestep = timestep;
}

glm::vec2 SimulationState::getGravity() const {
    return gravity;
}

void SimulationState::setGravity(glm::vec2 gravity) {
    this->gravity = gravity;
}

std::vector<glm::vec2> SimulationState::getGlobalForces() const {
    std::vector<glm::vec2> forces;
    forces.push_back(this->gravity);
    return forces;
}

void SimulationState::setBoundingBox(double top, double right, double bottom, double left) {
    boundigBox.insert({Direction::Top, top});
    boundigBox.insert({Direction::Right, right});
    boundigBox.insert({Direction::Bottom, bottom});
    boundigBox.insert({Direction::Left, left});
}

std::map<Direction, double> SimulationState::getBoundigBox() const {
    return boundigBox;
}

double SimulationState::getBoundingTop() const {
    return boundigBox.at(Direction::Top);
}

double SimulationState::getBoundingRight() const {
    return boundigBox.at(Direction::Right);
}

double SimulationState::getBoundingBottom() const {
    return boundigBox.at(Direction::Bottom);
}

double SimulationState::getBoundingLeft() const {
    return boundigBox.at(Direction::Left);
}

SimulationState::SimulationState(SimulationMode simulationMode, double timestep) {
    this->simMode = simulationMode;
    this->timestep = timestep;
}

SimulationState::SimulationState() {
    this->simMode = SimulationMode::ExplicitEuler;
    this->timestep = 1.0/60.0;
    this->gravity = {0, -9.8};
    this->setBoundingBox(1, 1, -1, -1);
}
