//
// Created by hegeda on 2021-11-01.
//

#include <imgui.h>
#include "SelectedObjectSettingsWindow.h"

void SelectedObjectSettingsWindow::create(Scene *scene) {
    if(ImGui::Begin("Selected Object Settings")) {
        if(scene->getActiveObjectId() != -1) {
            const auto& activeObject = scene->getActiveObject();
            static bool editMode = false;

            ImGui::Text("Name: ");
            ImGui::SameLine();
            ImGui::Text("%s", activeObject->getName().c_str());
            ImGui::SameLine();
            std::string button_text;
            if(editMode) {
                button_text = "View Mode";
            } else {
                button_text = "Edit Mode";
            }
            if(ImGui::Button(button_text.c_str())) {
                editMode = !editMode;
            }
            ImGui::Spacing();

            if(activeObject->getType() == ObjectType::PointObject) {
                createPointSettings(std::dynamic_pointer_cast<Point>(activeObject).get(), editMode);
            }
            if(activeObject->getType() == ObjectType::SpringObject) {
                createSpringSettings(std::dynamic_pointer_cast<Spring>(activeObject).get(), editMode);
            }
        }
        ImGui::End();
    }
}

void SelectedObjectSettingsWindow::createPointSettings(Point* activePoint, bool editMode) {
    const auto& simProp = activePoint->getSimulationProperties();
    static bool velocityShow = activePoint->getVelocityHelper()->getVisibility();
    static bool forceShow = activePoint->getForceHelper()->getVisibility();

    ImGui::Separator();
    if(!editMode) {
        coordOutput("Position", simProp->getPosition().x, simProp->getPosition().y);
        coordOutput("Velocity", simProp->getVelocity().x, simProp->getVelocity().y);
        coordOutput("Forces", simProp->getResultantForcesForHelpers().x, simProp->getResultantForcesForHelpers().y);
        if(activePoint->isStatic()) {
            ImGui::Text("Static Point");
        } else {
            ImGui::Text("Non Static Point");
        }
    } else {
        static bool is_static = activePoint->isStatic();
        glm::vec2 new_pos = coordInput("Position", simProp->getPosition().x, simProp->getPosition().y);
        ImGui::Text("Static");
        ImGui::SameLine();
        ImGui::Checkbox("##static", &is_static);
        activePoint->move(new_pos);
        activePoint->setStatic(is_static);
    }
    ImGui::Separator();

    ImGui::Text("Show Velocity Vector");
    ImGui::SameLine();
    ImGui::Checkbox("##velchbox", &velocityShow);
    ImGui::Text("Show Force Vector");
    ImGui::SameLine();
    ImGui::Checkbox("##forcechbox", &forceShow);

    activePoint->getVelocityHelper()->setVisibility(velocityShow);
    activePoint->getForceHelper()->setVisibility(forceShow);
}

void SelectedObjectSettingsWindow::createSpringSettings(Spring* activeSpring, bool editMode) {
    float stretching = activeSpring->getStretching();
    float damping = activeSpring->getDampingCoefficient();
    float defaultLength = activeSpring->getDefaultLength();
    float currentLength = activeSpring->getCurrentLength();

    ImGui::Separator();
    ImGui::Text("Stretching: "); ImGui::SameLine(); ImGui::Text("%.4f", stretching);
    ImGui::Text("Damping Coefficient: "); ImGui::SameLine(); ImGui::Text("%.4f", damping);
    ImGui::Text("Default Length: "); ImGui::SameLine(); ImGui::Text("%.4f", defaultLength);
    ImGui::Text("Current Length: "); ImGui::SameLine(); ImGui::Text("%.4f", currentLength);
}

void SelectedObjectSettingsWindow::coordOutput(const std::string &title, float x, float y) {
    ImGui::Text("%s: ", title.c_str());
    ImGui::SameLine();
    ImGui::Text("X: ");
    ImGui::SameLine();
    ImGui::Text("%.4f", x);
    ImGui::SameLine();
    ImGui::Text("Y: ");
    ImGui::SameLine();
    ImGui::Text("%.4f", y);
}

glm::vec2 SelectedObjectSettingsWindow::coordInput(const std::string &title, float x, float y) {
    float input_x = x;
    float input_y = y;
    ImGui::Text("%s", title.c_str()); ImGui::SameLine();
    ImGui::Text("X: "); ImGui::SameLine();
    std::string label = "##x" + title;
    ImGui::PushItemWidth(100);
    ImGui::InputFloat(label.c_str(), &input_x, 0.0001f, 0.001f, "%.5f", ImGuiInputTextFlags_AutoSelectAll);
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::Text("Y: "); ImGui::SameLine();
    label = "##y" + title;
    ImGui::PushItemWidth(100);
    ImGui::InputFloat(label.c_str(), &input_y, 0.0001f, 0.001f, "%.5f", ImGuiInputTextFlags_AutoSelectAll);
    ImGui::PopItemWidth();
    return {input_x, input_y};
}
