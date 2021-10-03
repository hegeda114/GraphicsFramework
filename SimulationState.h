//
// Created by hegeda on 2021-10-03.
//

#ifndef GRAPHICSFRAMEWORK_SIMULATIONSTATE_H
#define GRAPHICSFRAMEWORK_SIMULATIONSTATE_H


#include <vector>
#include <vec2.hpp>
#include <map>
#include "SimulationMode.h"
#include "Direction.h"

class SimulationState {
private:
    SimulationMode simMode;
    double timestep;
    glm::vec2 gravity = {0, -9.8};

    std::map<Direction, double> boundigBox;
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
