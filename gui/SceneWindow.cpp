//
// Created by hegeda on 2021-11-01.
//

#include <imgui.h>
#include "SceneWindow.h"

ImVec2 SceneWindow::sceneWindowCurrentPos = {0, 0};
ImVec2 SceneWindow::sceneWindowCurrentSize = {0, 0};

void SceneWindow::create(const Scene& scene) {
    unsigned int textureID = scene.getRenderTextureId();
    if(ImGui::Begin("Scene")) {
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

        sceneWindowCurrentPos = ImGui::GetCursorScreenPos();
        sceneWindowCurrentSize = viewportPanelSize;

        glm::vec2 mSize = {viewportPanelSize.x, viewportPanelSize.y};
        scene.updateCamera(mSize.x, mSize.y);

        ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ mSize.x, mSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

        ImGui::End();
    }
}
