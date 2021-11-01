//
// Created by hegeda on 2021-09-29.
//

#ifndef GRAPHICSFRAMEWORK_SCENE_H
#define GRAPHICSFRAMEWORK_SCENE_H

#include <vector>
#include <memory>
#include "window/MouseButton.h"
#include "simulation/GlobalSimulationSettings.h"
#include "object/Object.h"
#include "object/Point.h"
#include "object/Spring.h"
#include "FrameBuffer.h"

class Scene {
public:
    Scene() = default;

    void init();
    void simulate();
    void render();

    unsigned int getRenderTextureId() const;

    const std::shared_ptr<Object>& getObjectByName(const std::string& objectName) const;
    void inputEvent(double x, double y, MouseButton button, ViewportMode mode);

    void move_to_home(double x, double y);
    const std::unique_ptr<GlobalSimulationSettings>& getGlobalSimulationSettings() const;

    void setGlobalSimulationSettings(std::unique_ptr<GlobalSimulationSettings> globalSimulationSettings);
    std::map<size_t, std::string> getObjects() const;
    std::vector<std::shared_ptr<Point>> getPoints() const;

    std::vector<std::shared_ptr<Spring>> getSprings() const;
    void setActiveObject(int activeObjectId);
    const std::shared_ptr<Object>& getActiveObject() const;
    int getActiveObjectId() const;

    // Add functions:
    std::shared_ptr<Point> addPoint(const glm::vec2& position);
    std::shared_ptr<Point> addPoint(std::shared_ptr<Point> object);
    void addStaticPoint(glm::vec2 position);
    void addSpring(const std::shared_ptr<Point>& i, const std::shared_ptr<Point>& j, float stretchnig, float dampingCoeffitient, float defaultLengeth);
    void addSpring(std::shared_ptr<Spring> object);

    void clearAllObject();

private:
    std::map<size_t, std::shared_ptr<Object>> m_objects;
    std::vector<std::shared_ptr<Point>> m_points;
    std::vector<std::shared_ptr<Spring>> m_springs;
    std::unique_ptr<GlobalSimulationSettings> m_globalSimulationSettings;
    std::unique_ptr<Shader> m_shader;
    std::unique_ptr<FrameBuffer> m_frameBuffer;
    int m_activeObjectId = -1;

    glm::vec2 m_mouseLastPosition = {0, 0};
    bool m_mouseLeftPressActive = false;
};


#endif //GRAPHICSFRAMEWORK_SCENE_H
