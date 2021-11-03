//
// Created by hegeda on 2021-11-01.
//

#ifndef GRAPHICSFRAMEWORK_SETTINGSWINDOW_H
#define GRAPHICSFRAMEWORK_SETTINGSWINDOW_H

#include "GuiWindow.h"

class SettingsWindow : public GuiWindow {
private:
    ViewportMode viewportMode;
    std::string selectedFile;
    bool savePopup();
    bool loadPopup();
public:
    SettingsWindow(std::shared_ptr<Scene> scene, std::shared_ptr<GuiState> guiState);
    virtual void create();
};


#endif //GRAPHICSFRAMEWORK_SETTINGSWINDOW_H
