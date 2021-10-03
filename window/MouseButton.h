//
// Created by hegeda on 2021-09-29.
//

#ifndef GRAPHICSFRAMEWORK_MOUSEBUTTON_H
#define GRAPHICSFRAMEWORK_MOUSEBUTTON_H

#include <glew.h>
#include <GLFW/glfw3.h>

enum class MouseButton
{
    LeftPress = 0,
    RightPress = 1,
    MiddlePress = 2,
    LeftRelease = 3,
    RightRelease = 4,
    MiddleRelease = 5,
    None = 9
};

class Input {
public:
    static MouseButton GetPressedButton(GLFWwindow* window) {
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            return MouseButton::LeftPress;
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
            return MouseButton::LeftRelease;
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
            return MouseButton::RightPress;
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
            return MouseButton::RightRelease;
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
            return MouseButton::MiddlePress;
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE) {
            return MouseButton::MiddleRelease;
        }
        return MouseButton::None;
    }
};


#endif //GRAPHICSFRAMEWORK_MOUSEBUTTON_H
