//
// Created by hegeda on 2021-11-01.
//

#ifndef GRAPHICSFRAMEWORK_GUI_H
#define GRAPHICSFRAMEWORK_GUI_H

#include "../Scene.h"
#include "../simulation/GlobalSimulationSettings.h"
#include "GuiState.h"
#include "SelectedObjectSettingsWindow.h"
#include "OutlinerWindow.h"
#include "SceneWindow.h"
#include "GlobalSettingsWindow.h"
#include "SettingsWindow.h"
#include <memory>
#include <imgui.h>

class Gui {
private:
    std::shared_ptr<Scene> m_scene{};
    std::shared_ptr<GuiState> m_guiState;
    int m_selectedObjectId = -1;

    std::unique_ptr<OutlinerWindow> m_outlinerWin;
    std::unique_ptr<SceneWindow> m_sceneWin;
    std::unique_ptr<SelectedObjectSettingsWindow> m_selectedObjectWin;
    std::unique_ptr<SettingsWindow> m_settingsWin;
    std::unique_ptr<GlobalSettingsWindow> m_globalSettingsWin;

public:
    static float createMenuBar();
    void init(std::shared_ptr<Scene> scene);
    void renderGui();
    std::shared_ptr<GuiState> getGuiState() const;
};


#endif //GRAPHICSFRAMEWORK_GUI_H
