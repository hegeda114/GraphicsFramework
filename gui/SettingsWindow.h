//
// Created by hegeda on 2021-11-01.
//

#ifndef GRAPHICSFRAMEWORK_SETTINGSWINDOW_H
#define GRAPHICSFRAMEWORK_SETTINGSWINDOW_H


#include "../Scene.h"
#include "GuiState.h"

class SettingsWindow {
private:
    static ViewportMode viewportMode;
    static std::string selectedFile;
    static bool savePopup(Scene *scene);
    static bool loadPopup(Scene *scene);
public:
    static void create(Scene *scene, GuiState *guiState);
};


#endif //GRAPHICSFRAMEWORK_SETTINGSWINDOW_H
