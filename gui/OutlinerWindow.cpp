//
// Created by hegeda on 2021-11-01.
//

#include <imgui.h>
#include "OutlinerWindow.h"

void OutlinerWindow::create(Scene* scene) {
    int activeObjectId = scene->getActiveObjectId();
    if(ImGui::Begin("Outliner")) {
        if (ImGui::CollapsingHeader("Points")) {
            if (ImGui::BeginTable("PointTable", 1)) {
                int i = 0;
                for (const auto &point: scene->getPoints()) {
                    char label[32];
                    sprintf(label, "%s##%d", point->getName().c_str(), i);
                    const bool item_is_selected = (activeObjectId == (int) point->getId());

                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);

                    ImGuiSelectableFlags selectable_flags =
                            ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowItemOverlap;
                    if (ImGui::Selectable(label, item_is_selected, selectable_flags)) {
                        if (!item_is_selected) {
                            scene->setActiveObject(point->getId());
                        }
                    }
                    i++;
                }
                ImGui::EndTable();
            }
        }

        if (ImGui::CollapsingHeader("Springs")) {
            if (ImGui::BeginTable("SpringTable", 1)) {
                int i = 0;
                for (const auto &point: scene->getSprings()) {
                    char label[32];
                    sprintf(label, "%s##%d", point->getName().c_str(), i);
                    const bool item_is_selected = (activeObjectId == (int) point->getId());

                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);

                    ImGuiSelectableFlags selectable_flags =
                            ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowItemOverlap;
                    if (ImGui::Selectable(label, item_is_selected, selectable_flags)) {
                        if (!item_is_selected) {
                            scene->setActiveObject(point->getId());
                        }
                    }
                    i++;
                }
                ImGui::EndTable();
            }
        }
        ImGui::End();
    }
}
