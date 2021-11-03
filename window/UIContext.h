//
// Created by hegeda on 2021-09-28.
//

#ifndef GRAPHICSFRAMEWORK_UICONTEXT_H
#define GRAPHICSFRAMEWORK_UICONTEXT_H


#include "Window.h"
#include "../Scene.h"
#include "../simulation/GlobalSimulationSettings.h"
#include "../gui/GuiState.h"
#include <memory>
#include <imgui.h>

class UIContext {
public:
    bool init(std::shared_ptr<Window> parentWindow);
    static void pre_render();
    void render();
    static void post_render();

    std::shared_ptr<GuiState> getGuiState() const;
    int m_selectedObjectId = -1;

private:
    std::shared_ptr<Window> m_parentWindow{};
    std::shared_ptr<Scene> m_scene{};
    ImGuiWindowFlags m_windowFlags{};
    ImGuiViewport* m_viewport{};
    std::shared_ptr<GuiState> m_guiState;

    void guiOutput();
};


#endif //GRAPHICSFRAMEWORK_UICONTEXT_H
