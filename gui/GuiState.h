//
// Created by hegeda on 2021-10-04.
//

#ifndef GRAPHICSFRAMEWORK_GUISTATE_H
#define GRAPHICSFRAMEWORK_GUISTATE_H

#include "../simulation/GlobalSimulationSettings.h"

struct GuiState {
    GlobalSimulationSettings currentSimState = GlobalSimulationSettings(SimulationMode::ExplicitEuler, 1.0/60.0);
    size_t fps = 0;
    bool renderStop = true;
    bool delayOn = false;
    bool blockViewportActions = false;
    int delay = 100;
    glm::vec2 sceneWindowCurrentPos = {0, 0};
    glm::vec2 sceneWindowCurrentSize = {0, 0};
    std::string currentSceneName = "";
};

#endif //GRAPHICSFRAMEWORK_GUISTATE_H
