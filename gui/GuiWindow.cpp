//
// Created by hegeda on 2021-11-03.
//

#include <imgui.h>
#include "GuiWindow.h"

GuiWindow::GuiWindow(std::shared_ptr<Scene> scene, std::shared_ptr<GuiState> guiState) {
    m_scene = std::move(scene);
    m_guiState = std::move(guiState);
}

void GuiWindow::floatOutput(const std::string &title, float value) {
    ImGui::Text("%s", title.c_str()); ImGui::SameLine(); ImGui::Text("%.4f", value);
}

float GuiWindow::floatInput(const std::string &title, float value, float step, float step_fast, const char* format) {
    float input_value = value;
    ImGui::Text("%s", title.c_str()); ImGui::SameLine();
    std::string label = "##value" + title;
    ImGui::PushItemWidth(100);
    ImGui::InputFloat(label.c_str(), &input_value, step, step_fast, format, ImGuiInputTextFlags_AutoSelectAll);
    ImGui::PopItemWidth();
    return input_value;
}