//
// Created by hegeda on 2021-10-03.
//

#ifndef GRAPHICSFRAMEWORK_GLOBALSIMULATIONSETTINGS_H
#define GRAPHICSFRAMEWORK_GLOBALSIMULATIONSETTINGS_H


#include <vector>
#include <vec2.hpp>
#include <map>
#include <memory>
#include "../CommonEnums.h"

class GlobalSimulationSettings {
private:
    SimulationMode m_simMode;
    SimulationApproach m_simApproach;
    PBDConstraint m_pbsConstraint;

    int m_pbdIterNum = 10;
    float m_pbdSystemStiffness = 0.01f;

    float m_beta = 0.0f;

    double m_timestep;
    glm::vec2 m_gravity = {0, -9.8};

    std::map<Direction, double> m_borderBox;
    bool m_gravityEnabled = false;
    bool m_bordersEnabled = false;
public:
    GlobalSimulationSettings(SimulationMode simulationMode, double timestep);
    SimulationMode getSimMode() const;
    void setSimMode(SimulationMode simulationMode);

    SimulationApproach getSimApproach() const;
    void setSimApproach(SimulationApproach simApproach);

    PBDConstraint getPBDConstraint() const;
    void setPBDConstaint(PBDConstraint constraint);

    float getBeta() const;
    void setBeta(float beta);

    double getTimestep() const;
    void setTimestep(double timestep);

    glm::vec2 getGravity() const;
    void setGravity(const glm::vec2& gravity);

    int getPBDIterNum() const;
    void setPBDIterNum(int iterNum);

    float getPBDSystemStiffness() const;
    void setPBDSystemStiffness(float systemStiffness);

    /**
     * Returns the sum of global forces, e.g. gravity and wind.
     * @return The sum of global forces.
     */
    std::vector<glm::vec2> getSumOfGlobalForces() const;

    void setBorders(double top, double right, double bottom, double left);
    std::map<Direction, double> getBorders() const;

    double getBorderTop() const;
    double getBorderRight() const;
    double getBorderBottom() const;
    double getBorderLeft() const;

    bool isBordersEnabled() const;
    bool isGravityEnabled() const;
    void setBordersEnabled(bool bordersEnabled);
    void setGravityEnabled(bool gravityEnabled);

    std::string getSerializedData() const;

    static std::unique_ptr<GlobalSimulationSettings> createFromSavedData(const std::string& serializedData);
};


#endif //GRAPHICSFRAMEWORK_GLOBALSIMULATIONSETTINGS_H
