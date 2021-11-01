//
// Created by hegeda on 2021-11-01.
//

#include "Gui.h"
#include "OutlinerWindow.h"
#include "SceneWindow.h"
#include "SelectedObjectSettingsWindow.h"
#include "SettingsWindow.h"
#include "GlobalSettingsWindow.h"

void Gui::init(std::shared_ptr<Scene> scene) {
    this->m_guiState = std::make_shared<GuiState>();
    this->m_scene = std::move(scene);
}

void Gui::renderGui() {
    OutlinerWindow::create(m_scene.get());
    SceneWindow::create(*m_scene);
    SelectedObjectSettingsWindow::create(m_scene.get());
    SettingsWindow::create(m_scene.get(), m_guiState.get());
    GlobalSettingsWindow::create(m_scene.get());
}

std::shared_ptr<GuiState> Gui::getGuiState() const {
    return m_guiState;
}

float Gui::createMenuBar() {
    ImVec2 size;
    if (ImGui::BeginMainMenuBar())
    {
        size = ImGui::GetWindowSize();
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New Empty Scene")) {}
            if (ImGui::MenuItem("Open Scene")) {}
            if (ImGui::MenuItem("Save Scene")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
    return size.y;
}
