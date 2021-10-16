//
// Created by hegeda on 2021-09-29.
//

#ifndef GRAPHICSFRAMEWORK_SCENE_H
#define GRAPHICSFRAMEWORK_SCENE_H


#include <vector>
#include <memory>
#include "../window/MouseButton.h"
#include "../SimulationState.h"
#include "../object/Object.h"

class Scene {
public:
    Scene() = default;
    void render(bool simulateOn);

    void init();

    void on_mouse_move(double x, double y, MouseButton button);

    void move_to_home(double x, double y);

    void setSimulationState(SimulationState simulationState);

    void addPoint(glm::vec2 position);

    void addStaticPoint(glm::vec2 position);

    std::map<size_t, std::string> getObjects() const;

    void setActiveObject(size_t activeObjectId);

    const std::unique_ptr<Object>& getActiveObject() const;

private:
    SimulationState simulationState;
    std::map<size_t, std::unique_ptr<Object>> objects;
    size_t activeObjectId = -1;

    glm::vec2 buttonLastPos = {0, 0};
    bool grabActive = false;
};


#endif //GRAPHICSFRAMEWORK_SCENE_H
