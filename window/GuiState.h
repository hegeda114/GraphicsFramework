//
// Created by hegeda on 2021-10-04.
//

#ifndef GRAPHICSFRAMEWORK_GUISTATE_H
#define GRAPHICSFRAMEWORK_GUISTATE_H

#include "../SimulationState.h"

struct GuiState {
    SimulationState currentSimState = SimulationState();
    size_t fps = 0;
    bool renderStop = false;
    bool delayOn = false;
    int delay = 100;
};

#endif //GRAPHICSFRAMEWORK_GUISTATE_H
