//
// Created by hegeda on 2021-11-01.
//

#ifndef GRAPHICSFRAMEWORK_SELECTEDOBJECTSETTINGSWINDOW_H
#define GRAPHICSFRAMEWORK_SELECTEDOBJECTSETTINGSWINDOW_H

#include "GuiWindow.h"

class SelectedObjectSettingsWindow : public GuiWindow {
private:
    void createPointSettings(Point* activePoint) const;
    void createSpringSettings(Spring* activeSpring) const;

    static void coordOutput(const std::string& title, float x, float y);
    static glm::vec2 coordInput(const std::string& title, float x, float y);
    static void floatOutput(const std::string& title, float value);
    static float floatInput(const std::string& title, float value);

    int m_lastActiveObjectId = -1;
    bool m_editMode = false;
public:
    SelectedObjectSettingsWindow(std::shared_ptr<Scene> scene, std::shared_ptr<GuiState> guiState);
    virtual void create();
};


#endif //GRAPHICSFRAMEWORK_SELECTEDOBJECTSETTINGSWINDOW_H
