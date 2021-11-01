//
// Created by hegeda on 2021-11-01.
//

#include <imgui.h>
#include "OutlinerWindow.h"

void OutlinerWindow::create() {
    if(ImGui::Begin("Outliner", nullptr)) {
        ImGui::SetWindowSize({300, 100});
    }
    ImGui::End();
}
