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

    sceneView = std::make_unique<Scene>();
    sceneView->init();

    uiContext = std::make_unique<UIContext>();
    uiContext->init(mainWindow, sceneView);

    guiState = uiContext->getGuiState();

    basicShaders.CreateShader();
    glUseProgram(Shaders::shaderProgramId);
}

void Application::loop() {
    auto start = high_resolution_clock::now();
    int counter = 0;
    float past_time = 0;
    while (mainWindow->isRunning())
    {
        counter++;
        start = std::chrono::high_resolution_clock::now();
        mainWindow->pre_render();
        uiContext->pre_render();

        bool sim_flag = !guiState->renderStop && (!guiState->delayOn || (guiState->delayOn && past_time < 0));
        sceneView->render(sim_flag);

        uiContext->render();
        uiContext->post_render();
        mainWindow->post_render();

        handleInput();

        duration<float> duration = (high_resolution_clock::now() - start);
        if(counter > 20) {
            counter = 0;
            uiContext->getGuiState()->fps = (int) (1.0f / duration.count());
        }

        if(guiState->delayOn) {
            if (past_time > 0) {
                past_time -= duration.count() * 10000;
            } else {
                past_time = (float) guiState->delay;
            }
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
        sceneView->setSimulationState(guiState->currentSimState);
    }
}
