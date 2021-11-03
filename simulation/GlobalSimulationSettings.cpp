//
// Created by hegeda on 2021-10-03.
//

#include <sstream>
#include "GlobalSimulationSettings.h"

SimulationMode GlobalSimulationSettings::getSimMode() const {
    return m_simMode;
}

void GlobalSimulationSettings::setSimMode(SimulationMode simulationMode) {
    m_simMode = simulationMode;
}

double GlobalSimulationSettings::getTimestep() const {
    return m_timestep;
}

void GlobalSimulationSettings::setTimestep(double timestep) {
    m_timestep = timestep;
}

glm::vec2 GlobalSimulationSettings::getGravity() const {
    return m_gravity;
}

void GlobalSimulationSettings::setGravity(const glm::vec2& gravity) {
    m_gravity = gravity;
}

std::vector<glm::vec2> GlobalSimulationSettings::getSumOfGlobalForces() const {
    std::vector<glm::vec2> forces;
    forces.push_back(m_gravity);
    return forces;
}

void GlobalSimulationSettings::setBorders(double top, double right, double bottom, double left) {
    m_borderBox.insert({Direction::Top, top});
    m_borderBox.insert({Direction::Right, right});
    m_borderBox.insert({Direction::Bottom, bottom});
    m_borderBox.insert({Direction::Left, left});
}

std::map<Direction, double> GlobalSimulationSettings::getBorders() const {
    return m_borderBox;
}

double GlobalSimulationSettings::getBorderTop() const {
    return m_borderBox.at(Direction::Top);
}

double GlobalSimulationSettings::getBorderRight() const {
    return m_borderBox.at(Direction::Right);
}

double GlobalSimulationSettings::getBorderBottom() const {
    return m_borderBox.at(Direction::Bottom);
}

double GlobalSimulationSettings::getBorderLeft() const {
    return m_borderBox.at(Direction::Left);
}

GlobalSimulationSettings::GlobalSimulationSettings(SimulationMode simulationMode, double timestep) {
    m_simMode = simulationMode;
    m_timestep = timestep;
}

bool GlobalSimulationSettings::isBordersEnabled() const {
    return m_bordersEnabled;
}

bool GlobalSimulationSettings::isGravityEnabled() const {
    return m_gravityEnabled;
}

void GlobalSimulationSettings::setBordersEnabled(bool bordersEnabled) {
    m_bordersEnabled = bordersEnabled;
}

void GlobalSimulationSettings::setGravityEnabled(bool gravityEnabled) {
    m_gravityEnabled = gravityEnabled;
}

std::string GlobalSimulationSettings::getSerializedData() const {
    char buffer [200];
    std::string gravityEnabled = "true";
    if(!m_gravityEnabled) gravityEnabled = "false";

    std::string simulationMode;
    switch (m_simMode) {
        case ExplicitEuler: simulationMode = "explicit_euler";
            break;
        case ImplicitEuler: simulationMode = "implicit_euler";
            break;
    }

    sprintf(buffer, "%f;%s;%f;%f;%s", m_timestep, gravityEnabled.c_str(), m_gravity.x, m_gravity.y, simulationMode.c_str());
    return buffer;
}

std::unique_ptr<GlobalSimulationSettings> GlobalSimulationSettings::createFromSavedData(const std::string &serializedData) {
    std::stringstream ss(serializedData);
    std::string val, val1, val2;

    getline(ss, val, ';');
    float timestep = std::stof(val);

    getline(ss, val, ';');
    bool gravityEnabled = (val == "true");

    getline(ss, val1, ';');
    getline(ss, val2, ';');
    glm::vec2 gravity(std::stof(val1), std::stof(val2));

    SimulationMode simMode;
    getline(ss, val, ';');
    if(val == "explicit_euler") simMode = SimulationMode::ExplicitEuler;
    if(val == "implicit_euler") simMode = SimulationMode::ImplicitEuler;

    std::unique_ptr<GlobalSimulationSettings> globSimSet = std::make_unique<GlobalSimulationSettings>(simMode, timestep);
    globSimSet->setGravityEnabled(gravityEnabled);
    globSimSet->setGravity(gravity);
    return globSimSet;
}
