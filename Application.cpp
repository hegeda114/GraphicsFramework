//
// Created by hegeda on 2021-09-28.
//

#include "Application.h"

using namespace std::chrono;


Application::Application(const std::string& app_name) {
    m_width = 800;
    //m_width = 1200;
    m_height = 800;

    m_mainWindow = std::make_unique<Window>(app_name);
    m_mainWindow->init(m_width, m_height);

    m_sceneView = std::make_unique<Scene>();
    m_sceneView->init();

    m_uiContext = std::make_unique<UIContext>();
    m_uiContext->init(m_mainWindow, m_sceneView);

    m_guiState = m_uiContext->getGuiState();

    m_basicShaders = std::make_unique<Shaders>();
    m_basicShaders->CreateShader();
    glUseProgram(Shaders::shaderProgramId);
}

void Application::loop() {
    auto start = high_resolution_clock::now();
    size_t counter = 0;
    float past_time = 0;
    while (m_mainWindow->isRunning())
    {
        counter++;
        start = std::chrono::high_resolution_clock::now();

        // pre render
        m_mainWindow->pre_render();
        m_uiContext->pre_render();

        // simulation and render
        if(!m_guiState->renderStop && (!m_guiState->delayOn || (m_guiState->delayOn && past_time < 0))) {
            m_sceneView->simulate();
        }
        m_sceneView->render();
        m_uiContext->render();

        // post render
        m_uiContext->post_render();
        m_mainWindow->post_render();

        handleInput();

        duration<float> duration = (high_resolution_clock::now() - start);
        if(counter > 20) {
            counter = 0;
            m_uiContext->getGuiState()->fps = (int) (1.0f / duration.count());
        }

        if(m_guiState->delayOn) {
            if (past_time > 0) {
                past_time -= duration.count() * 10000;
            } else {
                past_time = (float) m_guiState->delay;
            }
        }
    }
}

void Application::handleInput() {
    auto *winPtr = m_mainWindow->getGLFWWindow();

    double x, y;
    glfwGetCursorPos(winPtr, &x, &y);
    int curr_width, curr_height;
    glfwGetWindowSize(winPtr, &curr_width, &curr_height);
    double wxPos = (x / curr_width) * 2 - 1;
    double wyPos = - ((y / curr_height) * 2 - 1);

    if (glfwGetKey(winPtr, GLFW_KEY_H) == GLFW_PRESS)
    {
        m_sceneView->move_to_home(wxPos, wyPos);
    }
    m_sceneView->on_mouse_move(wxPos, wyPos, Input::GetPressedButton(winPtr));

    if(m_uiContext->isSimStateChanged()) {
        m_sceneView->setSimulationState(m_guiState->currentSimState);
    }
}
