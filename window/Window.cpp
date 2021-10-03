//
// Created by hegeda on 2021-09-28.
//

#include <iostream>
#include <glew.h>
#include <GLFW/glfw3.h>
#include "Window.h"

bool Window::init(int width, int height) {
    this->width = width;
    this->height = height;
    this->running = true;

    /* Initialize the library */
    if (!glfwInit()) {
        std::cerr << "Error: GLFW Window couldn't be initialized" << std::endl;
        return false;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(this->width, this->height, this->title.c_str(), nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        std::cerr << "Error: GLFW Window couldn't be created" << std::endl;
        return false;
    }

    glfwSetWindowUserPointer(window, this);
//    glfwSetKeyCallback(glWindow, on_key_callback);
//    glfwSetScrollCallback(glWindow, on_scroll_callback);
//    glfwSetWindowSizeCallback(glWindow, on_window_size_callback);
//    glfwSetWindowCloseCallback(glWindow, on_window_close_callback);
//    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
    glfwSetWindowCloseCallback(window, on_window_close_callback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK)
        std::cout << "Error: glewInit()!" << std::endl;

    glEnable(GL_DEPTH_TEST);
    return true;
}

void Window::pre_render() const {
    glViewport(0, 0, width, height);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::post_render() {
    glfwPollEvents();
    glfwSwapBuffers(window);
}

void Window::on_window_close_callback(GLFWwindow *window) {
    auto windowPtr = static_cast<Window*>(glfwGetWindowUserPointer(window));
    windowPtr->running = false;
}

GLFWwindow* Window::getGLFWWindow() {
    return this->window;
}
