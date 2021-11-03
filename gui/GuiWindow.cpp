//
// Created by hegeda on 2021-11-03.
//

#include "GuiWindow.h"

GuiWindow::GuiWindow(std::shared_ptr<Scene> scene, std::shared_ptr<GuiState> guiState) {
    m_scene = std::move(scene);
    m_guiState = std::move(guiState);
}
