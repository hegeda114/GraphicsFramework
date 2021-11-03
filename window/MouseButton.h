//
// Created by hegeda on 2021-09-29.
//

#ifndef GRAPHICSFRAMEWORK_MOUSEBUTTON_H
#define GRAPHICSFRAMEWORK_MOUSEBUTTON_H

#include <glew.h>
#include <GLFW/glfw3.h>
#include <vec2.hpp>

class MouseState {
private:
    glm::vec2 m_mouseLastPosition = {0, 0};
    bool m_prevLeftPressActive = false;
    bool m_prevRightPressActive = false;
    bool m_prevMiddlePressActive = false;

    bool m_mouseLeftPressActive = false;
    bool m_mouseRightPressActive = false;
    bool m_mouseMiddlePressActive = false;
public:
    void buttonPressed(GLFWwindow* window);
    bool leftIsActive() const;
    bool rightIsActive() const;
    bool middleIsActive() const;
    bool leftButtonStateChanged() const;
    bool rightButtonStateChanged() const;
    bool middleButtonStateChanged() const;
};


#endif //GRAPHICSFRAMEWORK_MOUSEBUTTON_H
