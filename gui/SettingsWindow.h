//
// Created by hegeda on 2021-11-01.
//

#ifndef GRAPHICSFRAMEWORK_SETTINGSWINDOW_H
#define GRAPHICSFRAMEWORK_SETTINGSWINDOW_H

#include "GuiWindow.h"

class SettingsWindow : public GuiWindow {
private:
    ViewportMode viewportMode;
    int m_imagesWidth = -1;
    int m_imagesHeight = -1;
    GLuint m_grabOnImage = -1;
    GLuint m_grabOffImage = -1;
    GLuint m_selectOnImage = -1;
    GLuint m_selectOffImage = -1;
    GLuint m_addPointOnImage = -1;
    GLuint m_addPointOffImage = -1;
    GLuint m_addSpringOnImage = -1;
    GLuint m_addSpringOffImage = -1;

public:
    SettingsWindow(std::shared_ptr<Scene> scene, std::shared_ptr<GuiState> guiState);
    void create() override;
};


#endif //GRAPHICSFRAMEWORK_SETTINGSWINDOW_H
