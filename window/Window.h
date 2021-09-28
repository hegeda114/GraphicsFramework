//
// Created by hegeda on 2021-09-28.
//

#ifndef GRAPHICSFRAMEWORK_WINDOW_H
#define GRAPHICSFRAMEWORK_WINDOW_H

#include <glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
    Window(const std::string &title) : title(title) { }

    bool init(int width, int height);
    void pre_render() const;
    void post_render();
//    void end();
    bool isRunning() const { return this->running; }

    GLFWwindow* getGLFWWindow();

private:
    static void on_window_close_callback(GLFWwindow* window);

    GLFWwindow* window;
    int width;
    int height;
    const std::string& title;
    bool running = false;
};


#endif //GRAPHICSFRAMEWORK_WINDOW_H
