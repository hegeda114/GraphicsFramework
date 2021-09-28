#include <iostream>
#include <glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <fstream>
#include <string>
#include <sstream>
#include "Shaders.h"
#include "Scene.h"
#include "Point.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "glm.hpp"
#include "GuiWidget.h"

using namespace glm;

static Scene scene; //singleton
GLFWwindow* window;
static bool my_tool_active;
GuiWidget *gui;

static bool mouseLeftButtonDown = false;
Geometry* currentGeom = nullptr;

static vec2 convertToWorldCoord(double xpos, double ypos) {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    float wxPos = (xpos / width) * 2 - 1;
    float wyPos = (ypos / height) * 2 - 1;
    return { wxPos, -wyPos };
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        vec2 toPos = convertToWorldCoord(xpos, ypos);
        currentGeom = scene.getTopGeometry(toPos);

        mouseLeftButtonDown = true;
    }
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        currentGeom = nullptr;
        mouseLeftButtonDown = false;
    }
}

void addPointToScene(float* color) {
    auto* p = new Point({0, 0}, color);
    scene.addPoint(p);
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(mouseLeftButtonDown) {
        if(currentGeom != nullptr) {
            vec2 toPos = convertToWorldCoord(xpos, ypos);
            currentGeom->Grab(toPos.x, toPos.y);
        }
    }
}

static void renderGui() {
    gui = new GuiWidget();
    gui->setUpAddPointFunction(addPointToScene);
    gui->setUp();
    gui->Render();
}

int mainnnn()
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Test Program", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    GuiWidget::initGui(window);

    scene.Build(); //initialize build

    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    Shaders basicShaders = Shaders();
    basicShaders.CreateShader();

    glUseProgram(Shaders::shaderProgramId);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        glViewport(0, 0, width, height);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        basicShaders.Bind();
        scene.Animate();
        scene.Render();

        renderGui();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteShader(Shaders::shaderProgramId); //Todo ez kell?

    glfwTerminate();
    return 0;
}