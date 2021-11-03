//
// Created by hegeda on 2021-11-01.
//

#ifndef GRAPHICSFRAMEWORK_SELECTEDOBJECTSETTINGSWINDOW_H
#define GRAPHICSFRAMEWORK_SELECTEDOBJECTSETTINGSWINDOW_H


#include "../Scene.h"

class SelectedObjectSettingsWindow {
private:
    static void createPointSettings(Point* activePoint, bool editMode);
    static void createSpringSettings(Spring* activeSpring, bool editMode);

    static void coordOutput(const std::string& title, float x, float y);
    static glm::vec2 coordInput(const std::string& title, float x, float y);
public:
    static void create(Scene* scene);
};


#endif //GRAPHICSFRAMEWORK_SELECTEDOBJECTSETTINGSWINDOW_H
