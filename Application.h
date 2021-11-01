//
// Created by hegeda on 2021-09-28.
//

#ifndef GRAPHICSFRAMEWORK_APPLICATION_H
#define GRAPHICSFRAMEWORK_APPLICATION_H


#include <string>
#include <memory>
#include <chrono>
#include <thread>

#include "window/Window.h"
#include "window/UIContext.h"
#include "Scene.h"
#include "gui/Gui.h"

class Application {
public:
    explicit Application(const std::string& app_name);
    void loop();

private:
    void handleInput();

    std::shared_ptr<Window> m_mainWindow;
    std::unique_ptr<UIContext> m_uiContext;
    std::unique_ptr<Gui> m_gui;
    std::shared_ptr<GuiState> m_guiState;
    std::shared_ptr<Scene> m_sceneView;

    ViewportMode m_mode = ViewportMode::Selection;
    int m_width;
    int m_height;
};


#endif //GRAPHICSFRAMEWORK_APPLICATION_H
