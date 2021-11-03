//
// Created by hegeda on 2021-09-28.
//

#include "Application.h"
#include "gui/SceneWindow.h"
#include "gui/SettingsWindow.h"

using namespace std::chrono;


Application::Application(const std::string& app_name) {
    m_width = 1200;
    m_height = 800;

    m_mainWindow = std::make_unique<Window>(app_name);
    m_mainWindow->init(m_width, m_height);

    m_sceneView = std::make_unique<Scene>();
    m_sceneView->init();

    m_uiContext = std::make_unique<UIContext>();
    m_uiContext->init(m_mainWindow);

    m_gui = std::make_unique<Gui>();
    m_gui->init(m_sceneView);

    m_guiState = m_gui->getGuiState();
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
        //TODO mSceneView->render();
        if(!m_guiState->renderStop && (!m_guiState->delayOn || (m_guiState->delayOn && past_time < 0))) {
            m_sceneView->simulate();
        }
        m_sceneView->render();

        m_gui->renderGui();

        // post render
        m_uiContext->post_render();
        m_mainWindow->post_render();

        handleInput();

        duration<float> duration = (high_resolution_clock::now() - start);
        if(counter > 20) {
            counter = 0;
            m_gui->getGuiState()->fps = (int) (1.0f / duration.count());
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
    if(m_guiState->blockViewportActions) {
        return;
    }

    auto *winPtr = m_mainWindow->getGLFWWindow();

    double x, y;
    int pos_x, pos_y;
    glfwGetCursorPos(winPtr, &x, &y);

    glfwGetWindowPos(winPtr, &pos_x, &pos_y);
    glm::vec2 sceneWindowSize = m_guiState->sceneWindowCurrentSize;
    glm::vec2 sceneWindowPos = m_guiState->sceneWindowCurrentPos;

    float leftBorder = sceneWindowPos.x - (float)pos_x;
    float rightBorder = (sceneWindowPos.x - (float)pos_x) + sceneWindowSize.x;
    float topBorder = (sceneWindowPos.y - (float)pos_y);
    float bottomBorder = (sceneWindowPos.y - (float)pos_y) + sceneWindowSize.y;
    if(x < leftBorder || x > rightBorder || y < topBorder || y > bottomBorder) {
        return;
    }

    float as = (sceneWindowSize.x / sceneWindowSize.y);
    double wxPos = ((x - leftBorder) / sceneWindowSize.x) * 2.0 - 1;
    wxPos = wxPos * as;
    double wyPos = - (((y - topBorder) / sceneWindowSize.y) * 2.0 - 1);

    if (glfwGetKey(winPtr, GLFW_KEY_H) == GLFW_PRESS) {
        m_sceneView->move_to_home(wxPos, wyPos);
    }
    if (glfwGetKey(winPtr, GLFW_KEY_G) == GLFW_PRESS) {
        m_mode = ViewportMode::Grab;
    }
    if (glfwGetKey(winPtr, GLFW_KEY_S) == GLFW_PRESS) {
        m_mode = ViewportMode::Selection;
    }
    if (glfwGetKey(winPtr, GLFW_KEY_C) == GLFW_PRESS) {
        m_mode = ViewportMode::Creation;
    }
    if (glfwGetKey(winPtr, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        m_sceneView->inputEvent(wxPos, wyPos, Input::GetPressedButton(winPtr), ViewportMode::ViewPan);
    } else {
        m_sceneView->inputEvent(wxPos, wyPos, Input::GetPressedButton(winPtr), m_mode);
    }

    //TODO m_sceneView->setGlobalSimulationSettings(std::make_unique<GlobalSimulationSettings>(m_guiState->currentSimState));
}
