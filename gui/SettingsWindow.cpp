//
// Created by hegeda on 2021-11-01.
//

#include <imgui.h>
#include "SettingsWindow.h"
#include "../IO.h"

void SettingsWindow::create() {
    if(ImGui::Begin("Settings")) {
        ImVec2 size = ImVec2(25.0f, 25.0f);

        if(m_scene->getMode() == ViewportMode::Default) {
            ImGui::ImageButton((void*)(intptr_t)m_selectOnImage, size, ImVec2(0, 0), ImVec2(1, 1), 0);
        } else {
            if(ImGui::ImageButton((void*)(intptr_t)m_selectOffImage, size, ImVec2(0, 0), ImVec2(1, 1), 0)) {
                m_scene->setMode(ViewportMode::Default);
            }
        }
        ImGui::SameLine();
        if(m_scene->getMode() == ViewportMode::Grab) {
            ImGui::ImageButton((void*)(intptr_t)m_grabOnImage, size, ImVec2(0, 0), ImVec2(1, 1), 0);
        } else {
            if(ImGui::ImageButton((void*)(intptr_t)m_grabOffImage, size, ImVec2(0, 0), ImVec2(1, 1), 0)) {
                m_scene->setMode(ViewportMode::Grab);
            }
        }
        ImGui::SameLine();
        if(m_scene->getMode() == ViewportMode::PointCreation) {
            ImGui::ImageButton((void*)(intptr_t)m_addPointOnImage, size, ImVec2(0, 0), ImVec2(1, 1), 0);
        } else {
            if(ImGui::ImageButton((void*)(intptr_t)m_addPointOffImage, size, ImVec2(0, 0), ImVec2(1, 1), 0)) {
                m_scene->setMode(ViewportMode::PointCreation);
            }
        }
        ImGui::SameLine();
        if(m_scene->getMode() == ViewportMode::SpringCreation) {
            ImGui::ImageButton((void*)(intptr_t)m_addSpringOnImage, size, ImVec2(0, 0), ImVec2(1, 1), 0);
        } else {
            if(ImGui::ImageButton((void*)(intptr_t)m_addSpringOffImage, size, ImVec2(0, 0), ImVec2(1, 1), 0)) {
                m_scene->setMode(ViewportMode::SpringCreation);
            }
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        std::string start_stop_label = m_guiState->renderStop ? "Start" : "Stop";
        if(ImGui::Button(start_stop_label.c_str())) {
            m_guiState->renderStop = !m_guiState->renderStop;
        }

        if(ImGui::Button("Reset Scene")) {
            m_guiState->renderStop = true;
            m_guiState->recordOn = false;
            if(!m_guiState->currentSceneName.empty()) {
                IO::open_scene("../saved_scenes/" + m_guiState->currentSceneName, m_scene.get());
            }
        }

        ImGui::Spacing();

        ImGui::Text("Delay:");
        ImGui::SameLine();
        ImGui::Checkbox("##delay", &m_guiState->delayOn);
        ImGui::SameLine();
        ImGui::SliderInt("##2", &m_guiState->delay, 1, 4000);

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        std::string start_stop_record = m_guiState->recordOn ? "Recording..." : "Start Recording";
        if(ImGui::Button(start_stop_record.c_str())) {
            m_guiState->recordOn = !m_guiState->recordOn;
            if(m_guiState->recordOn) {
                m_guiState->renderStop = false;
            }
        }
        ImGui::Text("Frame Number:"); ImGui::SameLine();
        ImGui::InputInt("##3", &m_guiState->recordLength, 10, 100);
        if(m_guiState->recordLength < 0) { m_guiState->recordLength = 0; }
        if(m_guiState->recordLength > 500) { m_guiState->recordLength = 500; }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("FPS:");
        ImGui::SameLine();
        ImGui::Text("%zu", m_guiState->fps);

    }
    ImGui::End();
}

SettingsWindow::SettingsWindow(std::shared_ptr<Scene> scene, std::shared_ptr<GuiState> guiState)
    : GuiWindow(std::move(scene),std::move(guiState)), viewportMode(ViewportMode::Default) {
    int width, height;
    IO::loadTextureFromFile("images/select_on.png", &m_selectOnImage, &width, &height);
    IO::loadTextureFromFile("images/select_off.png", &m_selectOffImage, &width, &height);
    IO::loadTextureFromFile("images/move_on.png", &m_grabOnImage, &width, &height);
    IO::loadTextureFromFile("images/move_off.png", &m_grabOffImage, &width, &height);
    IO::loadTextureFromFile("images/add_point_on.png", &m_addPointOnImage, &width, &height);
    IO::loadTextureFromFile("images/add_point_off.png", &m_addPointOffImage, &width, &height);
    IO::loadTextureFromFile("images/add_spring_on.png", &m_addSpringOnImage, &width, &height);
    IO::loadTextureFromFile("images/add_spring_off.png", &m_addSpringOffImage, &width, &height);
    m_imagesHeight = height;
    m_imagesWidth = width;
}
