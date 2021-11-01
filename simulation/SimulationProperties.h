//
// Created by hegeda on 2021-10-12.
//

#ifndef GRAPHICSFRAMEWORK_SIMULATIONPROPERTIES_H
#define GRAPHICSFRAMEWORK_SIMULATIONPROPERTIES_H

#include <vector>
#include "glm.hpp"
#include "GlobalSimulationSettings.h"

class SimulationProperties {
protected:
    glm::vec2 m_velocity = {0.0, 0.0};
    glm::vec2 m_position = {0.0, 0.0};
    std::vector<glm::vec2> m_forces;
    double m_mass = 1;

public:
    explicit SimulationProperties(glm::vec2 position);

    void addForce(double x, double y);
    void addForce(const glm::vec2& force);
    void clearForces();
    glm::vec2 getResultantForces() const;

    void setPosition(double x, double y);
    void setPosition(const glm::vec2& position);
    const glm::vec2& getPosition() const;

    void setVelocity(double x, double y);
    void setVelocity(const glm::vec2& velocity);
    const glm::vec2& getVelocity() const;

    void explicitEuler(const GlobalSimulationSettings* globalSimulationSettings);
};


#endif //GRAPHICSFRAMEWORK_SIMULATIONPROPERTIES_H
