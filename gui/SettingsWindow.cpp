//
// Created by hegeda on 2021-11-01.
//

#include <imgui.h>
#include "SettingsWindow.h"
#include "../IO.h"

ViewportMode SettingsWindow::viewportMode = ViewportMode::Selection;

void SettingsWindow::create(Scene *scene, GuiState *guiState) {
    static bool saveFileDialog = false;
    static bool openFileDialog = false;
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
            if(ImGui::Button("New Empty Scene")) {
                scene->clearAllObject();
            }
            if(ImGui::Button("Save Scene")) {
                saveFileDialog = true;
            }
            if(ImGui::Button("Load Scene")) {
                openFileDialog = true;
            }
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
    if(saveFileDialog) {
        saveFileDialog = savePopup(scene);
    }
    if(openFileDialog) {
        openFileDialog = loadPopup(scene);
    }
}

bool SettingsWindow::loadPopup(Scene *scene) {
    bool res = true;
    ImGui::OpenPopup("Open File Dialog");
    if (ImGui::BeginPopup("Open File Dialog")) {
        static char buf[30] = { 0 };
        ImGui::InputText("File path", buf, IM_ARRAYSIZE(buf));

        ImGui::Spacing();

        if (ImGui::Button("Open File")) {
            IO::open_scene(buf, scene);
            res = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel")) {
            res = false;
        }
        ImGui::EndPopup();
    }
    return res;
}

bool SettingsWindow::savePopup(Scene *scene) {
    bool res = true;
    ImGui::OpenPopup("Save File Dialog");
    if (ImGui::BeginPopup("Save File Dialog")) {
        static char buf[30] = { 0 };
        ImGui::InputText("File path", buf, IM_ARRAYSIZE(buf));

        ImGui::Spacing();

        if (ImGui::Button("Save File")) {
            IO::save_scene(scene, buf);
            res = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel")) {
            res = false;
        }
        ImGui::EndPopup();
    }
    return res;
}
