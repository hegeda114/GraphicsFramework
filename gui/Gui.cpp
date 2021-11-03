//
// Created by hegeda on 2021-11-01.
//

#include "Gui.h"
#include "../IO.h"
#include <iostream>
#include <dirent.h>

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
    createMenuBar();
    m_outlinerWin->create();
    m_sceneWin->create();
    m_selectedObjectWin->create();
    m_settingsWin->create();
    m_globalSettingsWin->create();
}

std::shared_ptr<GuiState> Gui::getGuiState() const {
    return m_guiState;
}

void Gui::createMenuBar() {
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    MenuCommand command = MenuCommand::None;
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New Empty Scene")) {
                m_scene->clearAllObject();
                m_guiState->currentSceneName = "";
            }
            if (ImGui::MenuItem("Open Scene")) {
                command = MenuCommand::OpenScene;
            }

            if (ImGui::MenuItem("Save Scene")) {
                command = MenuCommand::SaveScene;
            }

            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Add"))
        {
            if (ImGui::MenuItem("Add Point")) { command = MenuCommand::AddPoint; }
            if (ImGui::MenuItem("Add Static Point")) { command = MenuCommand::AddStaticPoint; }
            if (ImGui::MenuItem("Add Spring")) { command = MenuCommand::AddSpring;}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
    switch (command) {
        case OpenScene: {
            m_guiState->renderStop = true;
            ImGui::OpenPopup("Open File Dialog");
        }
            break;
        case SaveScene: {
            m_guiState->renderStop = true;
            ImGui::OpenPopup("Save File Dialog");
        }
            break;
        case AddPoint: {
            m_scene->addPoint(glm::vec2(0, 0));
        }
            break;
        case AddStaticPoint: {
            m_scene->addStaticPoint({0, 0});
        }
            break;
        case AddSpring:
            break;
        case None:
            break;
    }
    bool openPopupVisible = openPopup();
    bool savePopupVisible = savePopup();
    m_guiState->blockViewportActions = savePopupVisible || openPopupVisible;
}

bool Gui::openPopup() {
    bool res = false;
    if (ImGui::BeginPopupModal("Open File Dialog", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        res = true;
        struct dirent *d;
        DIR *dr;
        dr = opendir("../saved_scenes");
        if(dr!=nullptr)
        {
            if (ImGui::BeginTable("FileList", 1)) {
                int i = 0;
                for (d = readdir(dr); d != nullptr; d = readdir(dr)) {
                    if(d->d_name[0] == '.') {
                        continue;
                    }

                    char label[300];
                    sprintf(label, "%s##%d", d->d_name, i);
                    const bool item_is_selected = (selectedFile == d->d_name);

                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);

                    ImGuiSelectableFlags selectable_flags =
                            ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_DontClosePopups;
                    if (ImGui::Selectable(label, item_is_selected, selectable_flags)) {
                        if (!item_is_selected) {
                            selectedFile = d->d_name;
                        }
                    }
                    i++;
                }
                ImGui::EndTable();
                closedir(dr);
            }
        }

        ImGui::Spacing();

        if (ImGui::Button("Open File")) {
            m_guiState->currentSceneName = selectedFile;
            IO::open_scene("../saved_scenes/" + selectedFile, m_scene.get());
            ImGui::CloseCurrentPopup();
            res = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel")) {
            ImGui::CloseCurrentPopup();
            res = false;
        }
        ImGui::EndPopup();
    }
    return res;
}

bool Gui::savePopup() {
    bool res = false;
    if (ImGui::BeginPopupModal("Save File Dialog", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        res = true;
        static char buf[30] = {0};
        std::string name = m_guiState->currentSceneName;
        if(name != "") {
            strcpy(buf, name.substr(0, name.length()-4).c_str());
        }
        ImGui::InputText("File path", buf, IM_ARRAYSIZE(buf));

        ImGui::Spacing();

        bool validFileName = std::string(buf).find('.') == std::string::npos &&
                             std::string(buf).find('\\') == std::string::npos &&
                             std::string(buf).find('/') == std::string::npos;

        if (ImGui::Button("Save File") && validFileName ) {
            IO::save_scene(m_scene.get(), buf);
            m_guiState->currentSceneName = buf;
            ImGui::CloseCurrentPopup();
            res = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel")) {
            ImGui::CloseCurrentPopup();
            res = false;
        }
        ImGui::EndPopup();
    }
    return res;
}