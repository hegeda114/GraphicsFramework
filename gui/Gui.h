//
// Created by hegeda on 2021-11-01.
//

#ifndef GRAPHICSFRAMEWORK_GUI_H
#define GRAPHICSFRAMEWORK_GUI_H

#include "../Scene.h"
#include "../simulation/GlobalSimulationSettings.h"
#include "GuiState.h"
#include <memory>
#include <imgui.h>

class Gui {
private:
    std::shared_ptr<Scene> m_scene{};
    std::shared_ptr<GuiState> m_guiState;
    int m_selectedObjectId = -1;

    static void createMenuBar() ;

public:
    void init(std::shared_ptr<Scene> scene);
    void renderGui();
    std::shared_ptr<GuiState> getGuiState() const;
};


#endif //GRAPHICSFRAMEWORK_GUI_H
