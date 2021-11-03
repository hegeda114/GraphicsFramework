//
// Created by hegeda on 2021-11-01.
//

#ifndef GRAPHICSFRAMEWORK_OUTLINERWINDOW_H
#define GRAPHICSFRAMEWORK_OUTLINERWINDOW_H

#include "GuiWindow.h"

class OutlinerWindow : public GuiWindow {
public:
    OutlinerWindow(std::shared_ptr<Scene> scene, std::shared_ptr<GuiState> guiState);
    virtual void create();
};


#endif //GRAPHICSFRAMEWORK_OUTLINERWINDOW_H
