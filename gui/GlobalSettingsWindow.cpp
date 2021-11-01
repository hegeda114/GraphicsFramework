//
// Created by hegeda on 2021-11-01.
//

#include <imgui.h>
#include "GlobalSettingsWindow.h"

void GlobalSettingsWindow::create(Scene *scene) {
    if(ImGui::Begin("Global Settings")) {
        static float timestep = 1.0/60.0;
        ImGui::Text("Stepsize: ");
        ImGui::SameLine();
        ImGui::DragFloat("##timestep", &timestep, 0.00001f, 0.0f, 1.0f, "%.05f");
        scene->getGlobalSimulationSettings()->setTimestep(timestep);

        ImGui::Spacing();

        glm::vec2 glmGravity = scene->getGlobalSimulationSettings()->getGravity();
        static float gravity[2] = {glmGravity.x, glmGravity.y};
        static bool gravityEnabled = scene->getGlobalSimulationSettings()->isGravityEnabled();
        ImGui::Text("Gravity: ");
        ImGui::SameLine();
        ImGui::Checkbox("##gravityChb", &gravityEnabled);
        ImGui::SameLine();
        ImGui::DragFloat2("##gravity", gravity, 0.005f);
        scene->getGlobalSimulationSettings()->setGravityEnabled(gravityEnabled);
        scene->getGlobalSimulationSettings()->setGravity({gravity[0], gravity[1]});

        ImGui::Spacing();

        ImGui::Text("Simulation mode:");
        ImGui::SameLine();
        const char* items[] = {"Explicit Euler", "Implicit Euler" };
        static int item_current = 0;
        ImGui::Combo("combo", &item_current, items, IM_ARRAYSIZE(items));
        scene->getGlobalSimulationSettings()->setSimMode(static_cast<SimulationMode>(item_current));

        ImGui::End();
    }
}
