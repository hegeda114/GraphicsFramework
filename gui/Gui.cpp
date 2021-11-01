//
// Created by hegeda on 2021-11-01.
//

#include "Gui.h"
#include "OutlinerWindow.h"

void Gui::init(std::shared_ptr<Scene> scene) {
    this->m_guiState = std::make_shared<GuiState>();
    this->m_scene = scene;
}

void Gui::renderGui() {
    ImGui::PopStyleVar(3);
    createMenuBar();

    OutlinerWindow::create();

//    ImGui::Begin("InvisibleWindow", nullptr);
//        ImGui::AlignTextToFramePadding();
//        //ImGui::SetWindowSize({300, m_viewport->Size.y});
//        ImGui::PopStyleVar(3);
//
//        ImGui::Text("juhéj");
//    ImGui::End();
}

std::shared_ptr<GuiState> Gui::getGuiState() const {
    return m_guiState;
}

void Gui::createMenuBar() {
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New Empty Scene")) {}
            if (ImGui::MenuItem("Open Scene")) {}
            if (ImGui::MenuItem("Save Scene")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}
