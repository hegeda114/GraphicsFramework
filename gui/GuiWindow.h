//
// Created by hegeda on 2021-11-03.
//

#ifndef GRAPHICSFRAMEWORK_GUIWINDOW_H
#define GRAPHICSFRAMEWORK_GUIWINDOW_H

#include "../Scene.h"
#include "GuiState.h"

class GuiWindow {
protected:
    std::shared_ptr<Scene> m_scene;
    std::shared_ptr<GuiState> m_guiState;
public:
    GuiWindow(std::shared_ptr<Scene> scene, std::shared_ptr<GuiState> guiState);
};


#endif //GRAPHICSFRAMEWORK_GUIWINDOW_H
