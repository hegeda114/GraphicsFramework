//
// Created by hegeda on 2021-11-01.
//

#include <imgui.h>
#include <utility>
#include "SelectedObjectSettingsWindow.h"

void SelectedObjectSettingsWindow::create() {
    if(ImGui::Begin("Selected Object Settings")) {
        if(m_scene->getActiveObjectId() != -1) {
            const auto& activeObject = m_scene->getActiveObject();
            if(m_lastActiveObjectId != activeObject->getId() || !m_guiState->renderStop) {
                m_editMode = false;
            }
            m_lastActiveObjectId = activeObject->getId();

            ImGui::Text("Name: ");
            ImGui::SameLine();
            ImGui::Text("%s", activeObject->getName().c_str());
            ImGui::SameLine();
            std::string button_text;
            if(m_editMode) {
                button_text = "View Mode";
            } else {
                button_text = "Edit Mode";
            }
            if(m_guiState->renderStop && ImGui::Button(button_text.c_str())) {
                m_editMode = !m_editMode;
            }
            ImGui::Spacing();

            if(activeObject->getType() == ObjectType::PointObject) {
                createPointSettings(std::dynamic_pointer_cast<Point>(activeObject).get());
            }
            if(activeObject->getType() == ObjectType::SpringObject) {
                createSpringSettings(std::dynamic_pointer_cast<Spring>(activeObject).get());
            }
        }
        ImGui::End();
    }
}

void SelectedObjectSettingsWindow::createPointSettings(Point* activePoint) const {
    const auto& simProp = activePoint->getSimulationProperties();
    bool velocityShow = activePoint->getVelocityHelper()->getVisibility();
    bool forceShow = activePoint->getForceHelper()->getVisibility();

    ImGui::Separator();
    if(!m_editMode) {
        coordOutput("Position", simProp->getPosition().x, simProp->getPosition().y);
        coordOutput("Velocity", simProp->getVelocity().x, simProp->getVelocity().y);
        coordOutput("Forces", simProp->getResultantForcesForHelpers().x, simProp->getResultantForcesForHelpers().y);
        if(activePoint->isStatic()) {
            ImGui::Text("Static Point");
        } else {
            ImGui::Text("Non Static Point");
        }
    } else {
        bool is_static = activePoint->isStatic();
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

void SelectedObjectSettingsWindow::createSpringSettings(Spring* activeSpring) const {
    float stretching = activeSpring->getStretching();
    float damping = activeSpring->getDampingCoefficient();
    float defaultLength = activeSpring->getDefaultLength();
    float currentLength = activeSpring->getCurrentLength();

    if(!m_editMode) {
        floatOutput("Stretching: ", stretching);
        floatOutput("Damping Coefficient: ", damping);
        floatOutput("Default Length: ", defaultLength);
        floatOutput("Current Length: ", currentLength);
    } else {
        stretching = floatInput("Stretching: ", stretching, 1, 10, "%.2f");
        damping = floatInput("Damping Coefficient: ", damping, 1, 10, "%.2f");
        defaultLength = floatInput("Default Length: ", defaultLength, 0.00001f, 0.001f);
        activeSpring->setStretching(stretching);
        activeSpring->setDampingCoefficient(damping);
        activeSpring->setDefaultLength(defaultLength);
    }
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
    ImGui::InputFloat(label.c_str(), &input_x, 0.0001f, 0.001f, "%.4f", ImGuiInputTextFlags_AutoSelectAll);
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::Text("Y: "); ImGui::SameLine();
    label = "##y" + title;
    ImGui::PushItemWidth(100);
    ImGui::InputFloat(label.c_str(), &input_y, 0.0001f, 0.001f, "%.4f", ImGuiInputTextFlags_AutoSelectAll);
    ImGui::PopItemWidth();
    return {input_x, input_y};
}

SelectedObjectSettingsWindow::SelectedObjectSettingsWindow(std::shared_ptr<Scene> scene, std::shared_ptr<GuiState> guiState)
    : GuiWindow(std::move(scene), std::move(guiState)) {
}

void SelectedObjectSettingsWindow::floatOutput(const std::string &title, float value) {
    ImGui::Text("%s", title.c_str()); ImGui::SameLine(); ImGui::Text("%.4f", value);
}

float SelectedObjectSettingsWindow::floatInput(const std::string &title, float value, float step, float step_fast, const char* format) {
    float input_value = value;
    ImGui::Text("%s", title.c_str()); ImGui::SameLine();
    std::string label = "##value" + title;
    ImGui::PushItemWidth(100);
    ImGui::InputFloat(label.c_str(), &input_value, step, step_fast, format, ImGuiInputTextFlags_AutoSelectAll);
    ImGui::PopItemWidth();
    return input_value;
}
