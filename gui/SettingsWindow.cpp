//
// Created by hegeda on 2021-11-01.
//

#include <imgui.h>
#include "SettingsWindow.h"

void SettingsWindow::create() {
    if(ImGui::Begin("Settings")) {
        std::string modeName;
        switch (m_scene->getMode()) {
            case Default: modeName = "Selection Mode";
                break;
            case Grab: modeName = "Grab Mode";
                break;
            case PointCreation: modeName = "Point Creation Mode";
                break;
            case SpringCreation: modeName = "Spring Creation Mode";
                break;
            case ViewPan: modeName = "Viewport Pan Mode";
                break;
        }
        ImGui::Text("%s", modeName.c_str());

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

        ImGui::Spacing();

        ImGui::Text("FPS:");
        ImGui::SameLine();
        ImGui::Text("%zu", m_guiState->fps);

        ImGui::End();
    }
}

SettingsWindow::SettingsWindow(std::shared_ptr<Scene> scene, std::shared_ptr<GuiState> guiState)
    : GuiWindow(std::move(scene),std::move(guiState)), viewportMode(ViewportMode::Default) {

}
