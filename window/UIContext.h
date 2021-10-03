//
// Created by hegeda on 2021-09-28.
//

#ifndef GRAPHICSFRAMEWORK_UICONTEXT_H
#define GRAPHICSFRAMEWORK_UICONTEXT_H


#include "Window.h"
#include "../SimulationState.h"
#include <memory>
#include <imgui.h>

class UIContext {
public:
    bool init(Window* parentWindow);
    void pre_render();
    void render();
    void post_render();

    bool isSimStateChanged();
    SimulationState getCurrentSimState() const;
    void setFPS(size_t currentFPS);
//    void end;
private:
    Window* parentWindow;
    ImGuiWindowFlags windowFlags;
    ImGuiViewport* viewport;
    SimulationState currentSimState;
    bool simStateChanged = false;
    size_t fps = 0;

    void guiGlobalSettings();
    void guiOutput();
};


#endif //GRAPHICSFRAMEWORK_UICONTEXT_H
