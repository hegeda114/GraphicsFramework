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
    glm::vec2 m_velocity = {0, 0};
    glm::vec2 m_position = {0, 0};
    glm::vec2 m_predictedPosition = {0, 0};
    glm::vec2 m_deltaPredictedPos = {0, 0};

    std::vector<glm::vec2> m_forces;
    glm::vec2 m_resultantForcesForHelper = {0, 0};
    float m_inverse_mass = 1;

    std::pair<glm::vec2, glm::vec2> m_a = std::pair<glm::vec2, glm::vec2>(glm::vec2(0, 0), glm::vec2(0, 0));
    std::pair<glm::vec2, glm::vec2> m_b = std::pair<glm::vec2, glm::vec2>(glm::vec2(0, 0), glm::vec2(0, 0));
    std::pair<glm::vec2, glm::vec2> m_c = std::pair<glm::vec2, glm::vec2>(glm::vec2(0, 0), glm::vec2(0, 0));
    std::pair<glm::vec2, glm::vec2> m_d = std::pair<glm::vec2, glm::vec2>(glm::vec2(0, 0), glm::vec2(0, 0));

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

    void setPredictedPosition(float x, float y);
    void setPredictedPosition(const glm::vec2& position);
    const glm::vec2& getPredictedPosition() const;

    void setVelocity(float x, float y);
    void setVelocity(const glm::vec2& velocity);
    const glm::vec2& getVelocity() const;

    void setDeltaPredictedPos(const glm::vec2& deltaPredPos);
    const glm::vec2& getDeltaPredictedPos() const;

    float getInvMass() const;
    void setInvMass(float invMass);

    void addToA(const glm::vec2& a1, const glm::vec2& a2);
    void addToB(const glm::vec2& a1, const glm::vec2& a2);
    void addToC(const glm::vec2& a1, const glm::vec2& a2);
    void addToD(const glm::vec2& a1, const glm::vec2& a2);
    void multiplyA(float multiplierA1, float multiplierA2);
    void multiplyB(float multiplierB1, float multiplierB2);
    void multiplyC(float multiplierC1, float multiplierC2);
    void multiplyD(float multiplierD1, float multiplierD2);
    void clearABCD();

    std::pair<glm::vec2, glm::vec2> getA() const;
    std::pair<glm::vec2, glm::vec2> getB() const;
    std::pair<glm::vec2, glm::vec2> getC() const;
    std::pair<glm::vec2, glm::vec2> getD() const;

    void explicitEuler(const GlobalSimulationSettings* globalSimulationSettings);
    void semiImplicitEuler(const GlobalSimulationSettings* globalSimulationSettings);
    void rungeKuttaSecondOrder(const GlobalSimulationSettings* globalSimulationSettings);
    void rungeKuttaFourthOrder(const GlobalSimulationSettings* globalSimulationSettings);
    void pbdConstraint(const GlobalSimulationSettings* globalSimulationSettings);
};


#endif //GRAPHICSFRAMEWORK_SIMULATIONPROPERTIES_H
