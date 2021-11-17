//
// Created by hegeda on 2021-11-01.
//

#include <imgui.h>

#include <utility>
#include <iomanip>
#include "SceneWindow.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../Dependencies/stb_image_write.h"
#include "../IO.h"

void SceneWindow::create() {
    unsigned int textureID = m_scene->getRenderTextureId();
    if(ImGui::Begin("Scene")) {
        m_guiState->viewportIsActive = true;
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

        m_guiState->sceneWindowCurrentPos = {ImGui::GetCursorScreenPos().x, ImGui::GetCursorScreenPos().y};
        m_guiState->sceneWindowCurrentSize = {viewportPanelSize.x, viewportPanelSize.y};

        glm::vec2 mSize = {viewportPanelSize.x, viewportPanelSize.y};
        m_scene->updateCamera(mSize.x, mSize.y);

        ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ mSize.x, mSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

        if(m_guiState->recordOn) {
            std::string folder_name = "image";
            m_guiState->recordFrameCounter++;
            GLubyte* data = new GLubyte[3 * 800 * 800];
            memcpy(data, m_scene->getFrameBuffer().getData(), 3 * 800 * 800);
            stbi_flip_vertically_on_write(true);

            std::stringstream ss;
            ss << std::setw(4) << std::setfill('0') << std::to_string(m_guiState->recordFrameCounter);
            std::string number = ss.str();
            std::string file_name = m_guiState->recordPath + "/image_" + number + ".png";
            stbi_write_png(file_name.c_str(), 800, 800, 3, data, 800 * 3);
            m_savedSimTimes.push_back(m_scene->getSimulationTime());
        }
        if(m_guiState->recordFrameCounter - 1 > m_guiState->recordLength) {
            m_guiState->recordOn = false;
            m_guiState->renderStop = true;
            m_guiState->recordFrameCounter = 0;

            IO::save_record_info(m_guiState->recordPath, m_guiState.get(), m_scene.get(), m_savedSimTimes);

            m_savedSimTimes.clear();
        }

    }
    ImGui::End();
}

SceneWindow::SceneWindow(std::shared_ptr<Scene> scene, std::shared_ptr<GuiState> guiState) :
    GuiWindow(std::move(scene),std::move(guiState)) {

}
