//
// Created by hegeda on 2021-11-01.
//

#ifndef GRAPHICSFRAMEWORK_GLOBALSETTINGSWINDOW_H
#define GRAPHICSFRAMEWORK_GLOBALSETTINGSWINDOW_H


#include "GuiWindow.h"

class GlobalSettingsWindow : public GuiWindow{
public:
    GlobalSettingsWindow(std::shared_ptr<Scene> scene, std::shared_ptr<GuiState> guiState);
    void create() override;
};


#endif //GRAPHICSFRAMEWORK_GLOBALSETTINGSWINDOW_H
