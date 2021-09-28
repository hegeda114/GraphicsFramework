//
// Created by hegeda on 2021-09-28.
//

#ifndef GRAPHICSFRAMEWORK_APPLICATION_H
#define GRAPHICSFRAMEWORK_APPLICATION_H


#include <string>
#include <memory>
#include "window/Window.h"
#include "window/UIContext.h"

class Application {
public:
    explicit Application(const std::string& app_name);
    void loop();

private:
    std::unique_ptr<Window> mainWindow;
    std::unique_ptr<UIContext> uiContext;
};


#endif //GRAPHICSFRAMEWORK_APPLICATION_H
