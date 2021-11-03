//
// Created by hegeda on 2021-11-01.
//

#include "Gui.h"
#include "OutlinerWindow.h"
#include "SceneWindow.h"
#include "SettingsWindow.h"
#include "GlobalSettingsWindow.h"

void Gui::init(std::shared_ptr<Scene> scene) {
    m_guiState = std::make_shared<GuiState>();
    m_scene = std::move(scene);

    m_outlinerWin = std::make_unique<OutlinerWindow>(m_scene, m_guiState);
    m_sceneWin = std::make_unique<SceneWindow>(m_scene, m_guiState);
    m_selectedObjectWin = std::make_unique<SelectedObjectSettingsWindow>(m_scene, m_guiState);
    m_settingsWin = std::make_unique<SettingsWindow>(m_scene, m_guiState);
    m_globalSettingsWin = std::make_unique<GlobalSettingsWindow>(m_scene, m_guiState);
}

void Gui::renderGui() {
    m_outlinerWin->create();
    m_sceneWin->create();
    m_selectedObjectWin->create();
    m_settingsWin->create();
    m_globalSettingsWin->create();
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
        if (ImGui::BeginMenu("Add"))
        {
            if (ImGui::MenuItem("Add Point")) {}
            if (ImGui::MenuItem("Add Static Point")) {}
            if (ImGui::MenuItem("Add Spring")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
    return size.y;
}
