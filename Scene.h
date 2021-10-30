//
// Created by hegeda on 2021-09-29.
//

#ifndef GRAPHICSFRAMEWORK_SCENE_H
#define GRAPHICSFRAMEWORK_SCENE_H

#include <vector>
#include <memory>
#include "window/MouseButton.h"
#include "simulation/SimulationState.h"
#include "object/Object.h"
#include "object/Point.h"
#include "object/Spring.h"

class Scene {
public:
    Scene() = default;

    void init();
    void simulate();
    void render();

    void inputEvent(double x, double y, MouseButton button, ViewportMode mode);
    void move_to_home(double x, double y);

    void setSimulationState(SimulationState simulationState);

    std::map<size_t, std::string> getObjects() const;
    std::vector<std::shared_ptr<Point>> getPoints() const;
    std::vector<std::shared_ptr<Spring>> getSprings() const;

    void setActiveObject(int activeObjectId);
    const std::shared_ptr<Object>& getActiveObject() const;
    const std::shared_ptr<Object>& getObjectByName(const std::string& objectName) const;

    // Add functions:
    std::shared_ptr<Point> addPoint(glm::vec2 position);
    std::shared_ptr<Point> addPoint(std::shared_ptr<Point> object);
    void addStaticPoint(glm::vec2 position);
    void addSpring(const std::shared_ptr<Point>& i, const std::shared_ptr<Point>& j, float stretchnig, float dampingCoeffitient, float defaultLengeth);
    void addSpring(std::shared_ptr<Spring> object);

    void clearAllObject();
private:
    SimulationState m_simulationState;
    std::map<size_t, std::shared_ptr<Object>> m_objects;
    std::vector<std::shared_ptr<Point>> m_points;
    std::vector<std::shared_ptr<Spring>> m_springs;
    int m_activeObjectId = -1;

    glm::vec2 m_mouseLastPosition = {0, 0};
    bool m_mouseLeftPressActive = false;
};


#endif //GRAPHICSFRAMEWORK_SCENE_H
