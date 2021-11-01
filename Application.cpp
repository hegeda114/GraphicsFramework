//
// Created by hegeda on 2021-09-28.
//

#include "Application.h"

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

//    // The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
//    FramebufferName = 0;
//    glGenFramebuffers(1, &FramebufferName);
//    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
//
//    // The texture we're going to render to
//    GLuint renderedTexture;
//    glGenTextures(1, &renderedTexture);
//
//    // "Bind" the newly created texture : all future texture functions will modify this texture
//    glBindTexture(GL_TEXTURE_2D, renderedTexture);
//
//    // Give an empty image to OpenGL ( the last "0" )
//    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, 1024, 768, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);
//
//    // Poor filtering. Needed !
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//
//    // Render to our framebuffer
//    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
//    glViewport(0,0,1024,768); // Render on the whole framebuffer, complete from the lower left corner to the upper right
//
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
        //m_uiContext->render(); //TODO mPropertyPanel->render(mSceneView.get());

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
    auto *winPtr = m_mainWindow->getGLFWWindow();

    double x, y;
    glfwGetCursorPos(winPtr, &x, &y);
    int curr_width, curr_height;
    glfwGetWindowSize(winPtr, &curr_width, &curr_height);
    double wxPos = (x / curr_width) * 2 - 1;
    double wyPos = - ((y / curr_height) * 2 - 1);

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

    m_sceneView->inputEvent(wxPos, wyPos, Input::GetPressedButton(winPtr), m_mode);

    //TODO m_sceneView->setGlobalSimulationSettings(std::make_unique<GlobalSimulationSettings>(m_guiState->currentSimState));
}
