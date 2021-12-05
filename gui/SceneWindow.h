//
// Created by hegeda on 2021-11-01.
//

#ifndef GRAPHICSFRAMEWORK_SCENEWINDOW_H
#define GRAPHICSFRAMEWORK_SCENEWINDOW_H

#include "GuiWindow.h"

class SceneWindow : public GuiWindow {
private:
    std::vector<long long> m_savedSimTimes;
    std::vector<glm::vec2> m_savedPosition;
    std::vector<glm::vec2> m_savedVelocity;
public:
    SceneWindow(std::shared_ptr<Scene> scene, std::shared_ptr<GuiState> guiState);
    void create() override;
};


#endif //GRAPHICSFRAMEWORK_SCENEWINDOW_H
