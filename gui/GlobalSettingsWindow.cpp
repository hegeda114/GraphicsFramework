//
// Created by hegeda on 2021-11-01.
//

#include <imgui.h>

#include <utility>
#include "GlobalSettingsWindow.h"

void GlobalSettingsWindow::create() {
    if(ImGui::Begin("Global Settings")) {
        auto timestep = (float) m_scene->getGlobalSimulationSettings()->getTimestep();
        ImGui::Text("Timestep: ");
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

        bool hideHelpers = m_scene->getHideHelperVectors();
        ImGui::Text("Hide all vector: ");
        ImGui::SameLine();
        ImGui::Checkbox("##hidehelperschb", &hideHelpers);
        m_scene->setHideHelperVectors(hideHelpers);

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        const char* sim_approach[] = {"Mass Spring System", "Position Based Dynamics", "Shape Matching"};
        int sim_approach_curr = m_scene->getGlobalSimulationSettings()->getSimApproach();
        ImGui::Text("Simulation Approach: ");
        ImGui::Spacing();
        ImGui::PushItemWidth(160);
        ImGui::Combo("##combo_approach", &sim_approach_curr, sim_approach, IM_ARRAYSIZE(sim_approach));
        ImGui::PopItemWidth();
        m_scene->getGlobalSimulationSettings()->setSimApproach(static_cast<SimulationApproach>(sim_approach_curr));

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Mass-Spring System Settings");
        ImGui::Spacing();
        const char* items[] = {"Explicit Euler", "Semi-Implicit Euler", "Runge Kutta Second Order", "Runge Kutta Fourth Order" };
        int item_current = m_scene->getGlobalSimulationSettings()->getSimMode();
        ImGui::Text("Integrator: ");
        ImGui::SameLine();
        ImGui::PushItemWidth(160);
        ImGui::Combo("##combo_integr", &item_current, items, IM_ARRAYSIZE(items));
        ImGui::PopItemWidth();
        m_scene->getGlobalSimulationSettings()->setSimMode(static_cast<SimulationMode>(item_current));
        ImGui::Spacing();

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Position Based Dynamics Settings");
        ImGui::Spacing();
        auto iter_num = m_scene->getGlobalSimulationSettings()->getPBDIterNum();
        ImGui::Text("Iteration Number: ");
        ImGui::SameLine();
        ImGui::PushItemWidth(130);
        ImGui::InputInt("##iter_num", &iter_num, 1, 10, ImGuiInputTextFlags_AutoSelectAll);
        ImGui::PopItemWidth();
        if(iter_num < 1) {
            iter_num = 1;
        }
        m_scene->getGlobalSimulationSettings()->setPBDIterNum(iter_num);

        auto system_stiffness = m_scene->getGlobalSimulationSettings()->getPBDSystemStiffness();
        ImGui::Text("System Stiffness: ");
        ImGui::SameLine();
        ImGui::PushItemWidth(130);
        ImGui::InputFloat("##system_stiffness", &system_stiffness, 0.001f, 0.1f, "%.03f", ImGuiInputTextFlags_AutoSelectAll);
        ImGui::PopItemWidth();
        if(system_stiffness < 0) {
            iter_num = 0;
        }
        if(system_stiffness > 1.0f) {
            iter_num = 1.0f;
        }
        m_scene->getGlobalSimulationSettings()->setPBDSystemStiffness(system_stiffness);

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Shape Matching Settings");
        ImGui::Spacing();
        auto beta = m_scene->getGlobalSimulationSettings()->getBeta();
        ImGui::Text("Beta: ");
        ImGui::SameLine();
        ImGui::PushItemWidth(130);
        ImGui::InputFloat("##beta", &beta, 0.01f, 0.1f, "%.3f", ImGuiInputTextFlags_AutoSelectAll);
        ImGui::PopItemWidth();
        if(beta < 0) {
            beta = 0;
        }
        if(beta > 1) {
            beta = 1;
        }
        m_scene->getGlobalSimulationSettings()->setBeta(beta);

//        if(m_guiState->renderStop) {
//            if(ImGui::Button("Modify All Spring")) {
//                ImGui::OpenPopup("Modify All Spring");
//            }
//        }

//        if (ImGui::BeginPopupModal("Modify All Spring", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
//            m_guiState->blockViewportActions = true;
//            static float stretching = 10;
//            static float damping = 0.2;
//            static float defaultLength = 0.2;
//
//            ImGui::PushItemWidth(100);
//            stretching = floatInput("Stretching: ", stretching, 1, 10, "%.2f");
//            damping = floatInput("Damping Coefficient: ", damping, 1, 10, "%.2f");
//            defaultLength = floatInput("Default Length: ", defaultLength, 0.001f, 0.01f);
//
//            if (ImGui::Button("Apply Settings")) {
//                m_scene->modifyAllSpring(stretching, damping, defaultLength);
//                ImGui::CloseCurrentPopup();
//                m_guiState->blockViewportActions = false;
//            }
//            ImGui::SameLine();
//            if (ImGui::Button("Cancel")) {
//                ImGui::CloseCurrentPopup();
//                m_guiState->blockViewportActions = false;
//            }
//
//            ImGui::PopItemWidth();
//            ImGui::EndPopup();
//        }

        ImGui::End();
    }
}

GlobalSettingsWindow::GlobalSettingsWindow(std::shared_ptr<Scene> scene, std::shared_ptr<GuiState> guiState)
        : GuiWindow(std::move(scene), std::move(guiState)) {

}
