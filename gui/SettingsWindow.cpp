//
// Created by hegeda on 2021-11-01.
//

#include <imgui.h>
#include "SettingsWindow.h"
#include "../IO.h"
#include <iostream>
#include <utility>
#include <dirent.h>

void SettingsWindow::create() {
    if(ImGui::Begin("Settings")) {
        if (ImGui::CollapsingHeader("Viewport Mode", ImGuiTreeNodeFlags_DefaultOpen)) {
            if(ImGui::Button("Point Creation Mode")) {

            }
            if(ImGui::Button("Spring Creation Mode")) {

            }
        }
        if (ImGui::CollapsingHeader("Add Elements", ImGuiTreeNodeFlags_DefaultOpen)) {
            if(ImGui::Button("Create Point")) {
                m_scene->addPoint(glm::vec2(0, 0));
            }
            if(ImGui::Button("Create Static Point")) {
                m_scene->addStaticPoint({0, 0});
            }
        }
        if (ImGui::CollapsingHeader("Save/Load", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

            if(ImGui::Button("New Empty Scene")) {
                m_scene->clearAllObject();
                m_guiState->currentSceneName = "";
            }
            if(ImGui::Button("Save Scene")) {
                m_guiState->renderStop = true;
                ImGui::OpenPopup("Save File Dialog");
            }
            bool savePopupVisible = !savePopup();

            if(ImGui::Button("Load Scene")) {
                m_guiState->renderStop = true;
                ImGui::OpenPopup("Open File Dialog");
            }
            bool loadPopupVisible = !loadPopup();
            m_guiState->blockViewportActions = savePopupVisible || loadPopupVisible;
        }
        if (ImGui::CollapsingHeader("Simulation", ImGuiTreeNodeFlags_DefaultOpen)) {
            std::string start_stop_label = m_guiState->renderStop ? "Start" : "Stop";
            if(ImGui::Button(start_stop_label.c_str())) {
                m_guiState->renderStop = !m_guiState->renderStop;
            }

            ImGui::Spacing();

            ImGui::Text("Delay:");
            ImGui::SameLine();
            ImGui::Checkbox("##delay", &m_guiState->delayOn);
            ImGui::SameLine();
            ImGui::SliderInt("##2", &m_guiState->delay, 1, 1000);
        }

        ImGui::End();
    }
}

bool SettingsWindow::loadPopup() {
    bool res = true;
    if (ImGui::BeginPopupModal("Open File Dialog", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        res = false;
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
            res = true;
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel")) {
            ImGui::CloseCurrentPopup();
            res = true;
        }
        ImGui::EndPopup();
    }
    return res;
}

bool SettingsWindow::savePopup() {
    bool res = true;
    if (ImGui::BeginPopupModal("Save File Dialog", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        res = false;
        static char buf[30] = {0};
        std::string name = m_guiState->currentSceneName;
        strcpy(buf, name.substr(0, name.length()-4).c_str());
        ImGui::InputText("File path", buf, IM_ARRAYSIZE(buf));

        ImGui::Spacing();

        bool validFileName = std::string(buf).find('.') == std::string::npos &&
                std::string(buf).find('\\') == std::string::npos &&
                std::string(buf).find('/') == std::string::npos;

        if (ImGui::Button("Save File") && validFileName ) {
            m_guiState->currentSceneName = buf;
            IO::save_scene(m_scene.get(), buf);
            ImGui::CloseCurrentPopup();
            res = true;
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel")) {
            ImGui::CloseCurrentPopup();
            res = true;
        }
        ImGui::EndPopup();
    }
    return res;
}

SettingsWindow::SettingsWindow(std::shared_ptr<Scene> scene, std::shared_ptr<GuiState> guiState)
    : GuiWindow(std::move(scene),std::move(guiState)), viewportMode(ViewportMode::Selection) {

}
