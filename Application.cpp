//
// Created by hegeda on 2021-09-28.
//

#include "Application.h"
#include <chrono>
#include <thread>
using namespace std::chrono;

Application::Application(const std::string& app_name) {
    width = 800;
    //width = 1200;
    height = 800;

    mainWindow = std::make_unique<Window>(app_name);
    mainWindow->init(width, height);
    uiContext = std::make_unique<UIContext>();
    uiContext->init(mainWindow.get());

    sceneView = std::make_unique<Scene>();
    sceneView->init();
}

void Application::loop() {
    auto start = high_resolution_clock::now();
    size_t frameCounter = 0;
    while (mainWindow->isRunning())
    {
        mainWindow->pre_render();
        uiContext->pre_render();

        sceneView->render();

        uiContext->render();
        uiContext->post_render();
        mainWindow->post_render();

        handleInput();

        frameCounter++;
        if(duration_cast<seconds>(high_resolution_clock::now() - start) > seconds(1)) {
            uiContext->setFPS(frameCounter);
            start = std::chrono::high_resolution_clock::now();
            frameCounter = 0;
        }
    }
}

void Application::handleInput() {
    auto *winPtr = mainWindow->getGLFWWindow();

    double x, y;
    glfwGetCursorPos(winPtr, &x, &y);
    int curr_width, curr_height;
    glfwGetWindowSize(winPtr, &curr_width, &curr_height);
    double wxPos = (x / curr_width) * 2 - 1;
    double wyPos = - ((y / curr_height) * 2 - 1);

//    if (glfwGetKey(winPtr, GLFW_KEY_W) == GLFW_PRESS)
//    {
//        mSceneView->on_mouse_wheel(-0.4f);
//    }
//
//    if (glfwGetKey(winPtr, GLFW_KEY_S) == GLFW_PRESS)
//    {
//        mSceneView->on_mouse_wheel(0.4f);
//    }
//
    if (glfwGetKey(winPtr, GLFW_KEY_H) == GLFW_PRESS)
    {
        sceneView->move_to_home(wxPos, wyPos);
    }
    sceneView->on_mouse_move(wxPos, wyPos, Input::GetPressedButton(winPtr));

    if(uiContext->isSimStateChanged()) {
        sceneView->setSimulationState(uiContext->getCurrentSimState());
    }
}
