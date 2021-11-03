//
// Created by hegeda on 2021-11-01.
//

#ifndef GRAPHICSFRAMEWORK_SCENEWINDOW_H
#define GRAPHICSFRAMEWORK_SCENEWINDOW_H

#include "GuiWindow.h"

class SceneWindow : public GuiWindow {
public:
    SceneWindow(std::shared_ptr<Scene> scene, std::shared_ptr<GuiState> guiState);
    virtual void create();
};


#endif //GRAPHICSFRAMEWORK_SCENEWINDOW_H
