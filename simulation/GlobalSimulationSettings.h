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
    double m_timestep;
    glm::vec2 m_gravity = {0, -9.8};

    std::map<Direction, double> m_borderBox;
    bool m_gravityEnabled = false;
    bool m_bordersEnabled = false;
public:
    GlobalSimulationSettings(SimulationMode simulationMode, double timestep);
    SimulationMode getSimMode() const;
    void setSimMode(SimulationMode simulationMode);

    double getTimestep() const;
    void setTimestep(double timestep);

    glm::vec2 getGravity() const;
    void setGravity(const glm::vec2& gravity);

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
