//
// Created by hegeda on 2021-09-29.
//

#ifndef GRAPHICSFRAMEWORK_SCENE_H
#define GRAPHICSFRAMEWORK_SCENE_H


#include <vector>
#include <memory>
#include "../geometry/Point.h"
#include "../window/MouseButton.h"

class Scene {
public:
    Scene() = default;
    void render(bool simulateOn);

    void init();

    void on_mouse_move(double x, double y, MouseButton button);

    void move_to_home(double x, double y);

    void setSimulationState(SimulationState simulationState);

    void addPoint(vec2 position);

    void addStaticPoint(vec2 position);

    std::map<size_t, std::string> getGeometries() const;

    void setActiveGeom(size_t activeGeomId);

    const std::unique_ptr<Geometry>& getActiveGeom() const;

private:
    SimulationState simulationState;
    std::map<size_t, std::unique_ptr<Geometry>> geomMap;
    size_t activeGeomId = -1;

    vec2 buttonLastPos = {0, 0};
    bool grabActive = false;
};


#endif //GRAPHICSFRAMEWORK_SCENE_H
