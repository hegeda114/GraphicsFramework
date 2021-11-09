//
// Created by hegeda on 2021-11-06.
//

#include <imgui.h>
#include "ImageViewer.h"
#include "../IO.h"

ImageViewer::ImageViewer(std::shared_ptr<Scene> scene, std::shared_ptr<GuiState> guiState)
        : GuiWindow(std::move(scene), std::move(guiState)) {

}

void ImageViewer::create() {
    if(ImGui::Begin("Image Viewer")) {
        m_guiState->viewportIsActive = false;
        int availHeight = (int) ImGui::GetContentRegionAvail().y;

        if(!m_hasImage) {
            if(ImGui::Button("Load")) {
                IO::loadTextureFromFile(R"(E:\Programming\Projects\GraphicsFramework_Simulation\saved_videos\test.png)", &m_imageTexture, &m_imageWidth, &m_imageHeight);
                m_hasImage = true;
            }
        } else {
            int currentImageWidth = m_imageWidth / 2;
            int currentImageHeight = m_imageHeight / 2;

            if(availHeight < m_imageHeight) {
                float scale = (float) availHeight / (float) m_imageHeight;
                currentImageWidth = (int) (m_imageWidth * scale);
                currentImageHeight = (int) (m_imageHeight * scale);
            }

            ImVec2 image_size = ImVec2((float)currentImageWidth, (float)currentImageHeight);
            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - image_size.x) * 0.5f);
            ImGui::Image((void*)(intptr_t)m_imageTexture, image_size);
        }


    }
    ImGui::End();
}
