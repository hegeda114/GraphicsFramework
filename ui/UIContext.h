//
// Created by hegeda on 2021-09-28.
//

#ifndef GRAPHICSFRAMEWORK_UICONTEXT_H
#define GRAPHICSFRAMEWORK_UICONTEXT_H


#include "../window/Window.h"
#include "../Scene.h"
#include "../simulation/SimulationState.h"
#include "GuiState.h"
#include <memory>
#include <imgui.h>

class UIContext {
public:
    bool init(std::shared_ptr<Window> parentWindow, std::shared_ptr<Scene> scene);
    void pre_render();
    void render();
    void post_render();

    bool isSimStateChanged();
    std::shared_ptr<GuiState> getGuiState() const;
    int selectedObjectId = -1;

//    void end;
private:
    std::shared_ptr<Window> parentWindow{};
    std::shared_ptr<Scene> scene{};
    ImGuiWindowFlags windowFlags{};
    ImGuiViewport* viewport{};
    std::shared_ptr<GuiState> guiState;
    bool simStateChanged = false;

    void guiAddElements();
    void guiGlobalSettings();
    void guiOutput();
    void guiGeometriesList();
    void guiCurrentGeomSettings();
};


#endif //GRAPHICSFRAMEWORK_UICONTEXT_H
