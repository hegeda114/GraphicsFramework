//
// Created by hegeda on 2021-11-01.
//

#include <imgui.h>
#include "SettingsWindow.h"
#include "../IO.h"
#include <iostream>
#include <dirent.h>

ViewportMode SettingsWindow::viewportMode = ViewportMode::Selection;
std::string SettingsWindow::selectedFile = "";

void SettingsWindow::create(Scene *scene, GuiState *guiState) {
    if(ImGui::Begin("Settings")) {
        if (ImGui::CollapsingHeader("Viewport Mode", ImGuiTreeNodeFlags_DefaultOpen)) {
            if(ImGui::Button("Point Creation Mode")) {

            }
            if(ImGui::Button("Spring Creation Mode")) {

            }
        }
        if (ImGui::CollapsingHeader("Add Elements", ImGuiTreeNodeFlags_DefaultOpen)) {
            if(ImGui::Button("Create Point")) {
                scene->addPoint(glm::vec2(0, 0));
            }
            if(ImGui::Button("Create Static Point")) {
                scene->addStaticPoint({0, 0});
            }
        }
        if (ImGui::CollapsingHeader("Save/Load", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

            if(ImGui::Button("New Empty Scene")) {
                scene->clearAllObject();
            }
            if(ImGui::Button("Save Scene")) {
                guiState->renderStop = true;
                ImGui::OpenPopup("Save File Dialog");
            }
            bool savePopupVisible = !savePopup(scene);

            if(ImGui::Button("Load Scene")) {
                guiState->renderStop = true;
                ImGui::OpenPopup("Open File Dialog");
            }
            bool loadPopupVisible = !loadPopup(scene);
            guiState->blockViewportActions = savePopupVisible || loadPopupVisible;
        }
        if (ImGui::CollapsingHeader("Simulation", ImGuiTreeNodeFlags_DefaultOpen)) {
            std::string start_stop_label = guiState->renderStop ? "Start" : "Stop";
            if(ImGui::Button(start_stop_label.c_str())) {
                guiState->renderStop = !guiState->renderStop;
            }

            ImGui::Spacing();

            ImGui::Text("Delay:");
            ImGui::SameLine();
            ImGui::Checkbox("##delay", &guiState->delayOn);
            ImGui::SameLine();
            ImGui::SliderInt("##2", &guiState->delay, 1, 1000);
        }

        ImGui::End();
    }
}

bool SettingsWindow::loadPopup(Scene *scene) {
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

        static bool dont_ask_me_next_time = false;
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
        ImGui::Checkbox("Don't ask me next time", &dont_ask_me_next_time);
        ImGui::PopStyleVar();

        ImGui::Spacing();

        if (ImGui::Button("Open File")) {
            IO::open_scene("../saved_scenes/" + selectedFile, scene);
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

bool SettingsWindow::savePopup(Scene *scene) {
    bool res = true;
    if (ImGui::BeginPopupModal("Save File Dialog", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        res = false;
        static char buf[30] = { 0 };
        ImGui::InputText("File path", buf, IM_ARRAYSIZE(buf));

        ImGui::Spacing();

        bool validFileName = std::string(buf).find('.') == std::string::npos &&
                std::string(buf).find('\\') == std::string::npos &&
                std::string(buf).find('/') == std::string::npos;

        if (ImGui::Button("Save File") && validFileName ) {
            IO::save_scene(scene, buf);
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
