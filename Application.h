//
// Created by hegeda on 2021-09-28.
//

#ifndef GRAPHICSFRAMEWORK_APPLICATION_H
#define GRAPHICSFRAMEWORK_APPLICATION_H


#include <string>
#include <memory>
#include "window/Window.h"
#include "window/UIContext.h"
#include "ui/Scene.h"

class Application {
public:
    explicit Application(const std::string& app_name);
    void loop();

private:
    void handleInput();

    std::shared_ptr<Window> mainWindow;
    std::unique_ptr<UIContext> uiContext;
    std::shared_ptr<Scene> sceneView;
    std::shared_ptr<GuiState> guiState;
    Shaders basicShaders = Shaders();

    int width;
    int height;
};


#endif //GRAPHICSFRAMEWORK_APPLICATION_H
