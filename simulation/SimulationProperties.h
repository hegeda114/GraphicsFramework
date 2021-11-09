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
    glm::vec2 m_a1 = {0.0, 0.0};
    glm::vec2 m_a2 = {0.0, 0.0};
    glm::vec2 m_b1 = {0.0, 0.0};
    glm::vec2 m_b2 = {0.0, 0.0};

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

    void setA1(const glm::vec2& value);
    void setA2(const glm::vec2& value);
    void setB1(const glm::vec2& value);
    void setB2(const glm::vec2& value);

    void explicitEuler(const GlobalSimulationSettings* globalSimulationSettings);
    void rungeKuttaSecondOrder(const GlobalSimulationSettings* globalSimulationSettings);
};


#endif //GRAPHICSFRAMEWORK_SIMULATIONPROPERTIES_H
