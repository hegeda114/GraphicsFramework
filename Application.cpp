//
// Created by hegeda on 2021-09-28.
//

#include <iostream>
#include <imgui.h>
#include "Application.h"

Application::Application(const std::string& app_name) {
    mainWindow = std::make_unique<Window>(app_name);
    mainWindow->init(1200, 800);
    uiContext = std::make_unique<UIContext>();
    uiContext->init(mainWindow.get());
}

void Application::loop() {
    while (mainWindow->isRunning())
    {
        mainWindow->pre_render();
        uiContext->pre_render();

        uiContext->post_render();
        mainWindow->post_render();
    }
}
