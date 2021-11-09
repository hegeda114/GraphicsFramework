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
    static void floatOutput(const std::string& title, float value);
    static float floatInput(const std::string& title, float value, float step, float step_fast, const char* format = "%.4f");
public:
    GuiWindow(std::shared_ptr<Scene> scene, std::shared_ptr<GuiState> guiState);
    virtual void create() = 0;
};


#endif //GRAPHICSFRAMEWORK_GUIWINDOW_H
