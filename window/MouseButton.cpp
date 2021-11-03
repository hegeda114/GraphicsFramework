//
// Created by hegeda on 2021-11-03.
//

#include "MouseButton.h"

void MouseState::buttonPressed(GLFWwindow *window) {
    m_prevLeftPressActive = m_mouseLeftPressActive;
    m_prevRightPressActive = m_mouseRightPressActive;
    m_prevMiddlePressActive = m_mouseMiddlePressActive;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        m_mouseLeftPressActive = true;
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        m_mouseLeftPressActive = false;
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        m_mouseRightPressActive = true;
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
        m_mouseRightPressActive = false;
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
        m_mouseMiddlePressActive = true;
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE) {
        m_mouseMiddlePressActive = false;
    }
    //m_currentButtonType = MouseButton::None;
}

bool MouseState::leftIsActive() const {
    return m_mouseLeftPressActive;
}

bool MouseState::rightIsActive() const {
    return m_mouseRightPressActive;
}

bool MouseState::middleIsActive() const {
    return m_mouseMiddlePressActive;
}

bool MouseState::leftButtonStateChanged() const {
    return m_mouseLeftPressActive != m_prevLeftPressActive;
}

bool MouseState::rightButtonStateChanged() const {
    return m_mouseRightPressActive != m_prevRightPressActive;
}

bool MouseState::middleButtonStateChanged() const {
    return m_mouseMiddlePressActive != m_prevMiddlePressActive;
}

