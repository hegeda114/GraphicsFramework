//
// Created by hegeda on 2021-11-01.
//

#include <imgui.h>

#include <utility>
#include "SceneWindow.h"

void SceneWindow::create() {
    unsigned int textureID = m_scene->getRenderTextureId();
    if(ImGui::Begin("Scene")) {
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

        m_guiState->sceneWindowCurrentPos = {ImGui::GetCursorScreenPos().x, ImGui::GetCursorScreenPos().y};
        m_guiState->sceneWindowCurrentSize = {viewportPanelSize.x, viewportPanelSize.y};

        glm::vec2 mSize = {viewportPanelSize.x, viewportPanelSize.y};
        m_scene->updateCamera(mSize.x, mSize.y);

        ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ mSize.x, mSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

        ImGui::End();
    }
}

SceneWindow::SceneWindow(std::shared_ptr<Scene> scene, std::shared_ptr<GuiState> guiState) :
    GuiWindow(std::move(scene),std::move(guiState)) {

}
