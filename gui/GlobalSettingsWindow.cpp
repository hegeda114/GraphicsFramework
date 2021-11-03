//
// Created by hegeda on 2021-11-01.
//

#include <imgui.h>

#include <utility>
#include "GlobalSettingsWindow.h"

void GlobalSettingsWindow::create() {
    if(ImGui::Begin("Global Settings")) {
        auto timestep = (float) m_scene->getGlobalSimulationSettings()->getTimestep();
        ImGui::Text("Stepsize: ");
        ImGui::SameLine();
        ImGui::PushItemWidth(130);
        ImGui::InputFloat("##timestep", &timestep, 0.0001f, 0.001f, "%.06f", ImGuiInputTextFlags_AutoSelectAll);
        ImGui::PopItemWidth();
        if(timestep < 0.0f) {
            timestep = 0.000001f;
        }
        m_scene->getGlobalSimulationSettings()->setTimestep(timestep);
        ImGui::Spacing();

        glm::vec2 glmGravity = m_scene->getGlobalSimulationSettings()->getGravity();
        float gravity[2] = {glmGravity.x, glmGravity.y};
        bool gravityEnabled = m_scene->getGlobalSimulationSettings()->isGravityEnabled();
        ImGui::Text("Gravity: ");
        ImGui::SameLine();
        ImGui::Checkbox("##gravityChb", &gravityEnabled);
        ImGui::SameLine();
        ImGui::PushItemWidth(130);
        ImGui::DragFloat2("##gravity", gravity, 0.005f);
        ImGui::PopItemWidth();
        m_scene->getGlobalSimulationSettings()->setGravityEnabled(gravityEnabled);
        m_scene->getGlobalSimulationSettings()->setGravity({gravity[0], gravity[1]});
        ImGui::Spacing();

        const char* items[] = {"Explicit Euler", "Implicit Euler" };
        int item_current = m_scene->getGlobalSimulationSettings()->getSimMode();
        ImGui::Text("Simulation mode: ");
        ImGui::SameLine();
        ImGui::PushItemWidth(120);
        ImGui::Combo("##combo", &item_current, items, IM_ARRAYSIZE(items));
        ImGui::PopItemWidth();
        m_scene->getGlobalSimulationSettings()->setSimMode(static_cast<SimulationMode>(item_current));
        ImGui::Spacing();

        bool hideHelpers = m_scene->getHideHelperVectors();
        ImGui::Text("Hide all helper: ");
        ImGui::SameLine();
        ImGui::Checkbox("##hidehelperschb", &hideHelpers);
        m_scene->setHideHelperVectors(hideHelpers);

        ImGui::End();
    }
}

GlobalSettingsWindow::GlobalSettingsWindow(std::shared_ptr<Scene> scene, std::shared_ptr<GuiState> guiState)
        : GuiWindow(std::move(scene), std::move(guiState)) {

}
