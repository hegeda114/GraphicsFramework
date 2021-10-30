//
// Created by hegeda on 2021-10-03.
//

#ifndef GRAPHICSFRAMEWORK_SIMULATIONSTATE_H
#define GRAPHICSFRAMEWORK_SIMULATIONSTATE_H


#include <vector>
#include <vec2.hpp>
#include <map>
#include "../CommonEnums.h"

class SimulationState {
private:
    SimulationMode m_simMode;
    double m_timestep;
    glm::vec2 m_gravity = {0, 0};

    std::map<Direction, double> m_boundigBox;
public:
    SimulationState();
    SimulationState(SimulationMode simulationMode, double timestep);
    SimulationMode getSimMode() const;
    void setSimMode(SimulationMode simulationMode);

    double getTimestep() const;
    void setTimestep(double timestep);

    glm::vec2 getGravity() const;
    void setGravity(glm::vec2 gravity);

    std::vector<glm::vec2> getGlobalForces() const;

    void setBoundingBox(double top, double right, double bottom, double left);
    std::map<Direction, double> getBoundigBox() const;

    double getBoundingTop() const;
    double getBoundingRight() const;
    double getBoundingBottom() const;
    double getBoundingLeft() const;
};


#endif //GRAPHICSFRAMEWORK_SIMULATIONSTATE_H
