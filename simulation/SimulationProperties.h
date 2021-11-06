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
    glm::vec2 m_resultantForcesForHelper = {0.0, 0.0};
    double m_mass = 1;

public:
    explicit SimulationProperties(glm::vec2 position);

    void addForce(float x, float y);
    void addForce(const glm::vec2& force);
    void clearForces();
    glm::vec2 getResultantForces() const;
    glm::vec2 getResultantForcesForHelpers() const;

    void setPosition(float x, float y);
    void setPosition(const glm::vec2& position);
    const glm::vec2& getPosition() const;

    void setVelocity(float x, float y);
    void setVelocity(const glm::vec2& velocity);
    const glm::vec2& getVelocity() const;

    void explicitEuler(const GlobalSimulationSettings* globalSimulationSettings);
};


#endif //GRAPHICSFRAMEWORK_SIMULATIONPROPERTIES_H
