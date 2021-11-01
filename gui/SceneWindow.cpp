//
// Created by hegeda on 2021-11-01.
//

#include <imgui.h>
#include "SceneWindow.h"

void SceneWindow::create(const Scene& scene) {
    unsigned int textureID = scene.getRenderTextureId();
    if(ImGui::Begin("Scene")) {
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        glm::vec2 mSize = { viewportPanelSize.x, viewportPanelSize.y };

        //mCamera->set_aspect(mSize.x / mSize.y);
        //mCamera->update(mShader.get());

        ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ mSize.x, mSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

        ImGui::End();
    }
}
