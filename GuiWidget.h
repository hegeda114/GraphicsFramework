//
// Created by hegeda on 2021-02-13.
//

#ifndef GRAPHICSFRAMEWORK_GUIWIDGET_H
#define GRAPHICSFRAMEWORK_GUIWIDGET_H

#include "GLFW/glfw3.h"

class GuiWidget {
    void (*addPointFun)(float* color) = nullptr;
public:
    GuiWidget();
    void Render();
    void setUp();
    void setUpAddPointFunction(void (*addPointFunction)(float* color));
    static void initGui(GLFWwindow* window);
};


#endif //GRAPHICSFRAMEWORK_GUIWIDGET_H
