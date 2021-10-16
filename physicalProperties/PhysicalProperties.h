//
// Created by hegeda on 2021-10-12.
//

#ifndef GRAPHICSFRAMEWORK_PHYSICALPROPERTIES_H
#define GRAPHICSFRAMEWORK_PHYSICALPROPERTIES_H

#include <vector>
#include "glm.hpp"
#include "../SimulationState.h"

class PhysicalProperties {
protected:
    glm::vec2 m_velocity = {0.0, 0.0};
    glm::vec2 m_position = {0.0, 0.0};
    std::vector<glm::vec2> m_forces;
    double m_mass = 1;

public:
    explicit PhysicalProperties(glm::vec2 position);

    void addForce(double x, double y);
    void addForce(const glm::vec2& force);

    glm::vec2 getResultaltForces() const;

    void setPosition(double x, double y);
    void setPosition(const glm::vec2& position);

    const glm::vec2& getPosition() const;

    void setVelocity(double x, double y);
    void setVelocity(const glm::vec2& velocity);


    const glm::vec2& getVelocity() const;

    void explicitEuler(const SimulationState& simState);
};


#endif //GRAPHICSFRAMEWORK_PHYSICALPROPERTIES_H
