//
// Created by hegeda on 2021-09-29.
//

#ifndef GRAPHICSFRAMEWORK_SCENE_H
#define GRAPHICSFRAMEWORK_SCENE_H


#include "../geometry/Point.h"
#include "../window/MouseButton.h"

class Scene {
public:
    Scene() = default;
    void render();

    void init();

    void on_mouse_move(double x, double y, MouseButton button);

    void move_to_home(double x, double y);

    void setSimulationState(SimulationState simulationState);

private:
    SimulationState simulationState;
    std::unique_ptr<Point> testPoint;
    std::unique_ptr<Vector> testVector;

    vec2 buttonLastPos = {0, 0};
    bool grabActive = false;
};


#endif //GRAPHICSFRAMEWORK_SCENE_H
