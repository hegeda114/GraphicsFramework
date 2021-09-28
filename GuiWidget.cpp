//
// Created by hegeda on 2021-02-13.
//

#include "GuiWidget.h"
#include "imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

GuiWidget::GuiWidget() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GuiWidget::setUp() {
    bool my_tool_active;
    ImGuiWindowFlags f = ImGuiWindowFlags_NoResize + ImGuiWindowFlags_NoMove;
    ImGui::Begin("Settings", &my_tool_active, f);
        ImGui::SetWindowPos({0, 0});
        ImGui::SetWindowSize({300, 300});
        /*ImGui::SetWindowFontScale(2);*/

        static float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
        ImGui::ColorEdit4("Szín", color);

        if(ImGui::Button("Add Point") && addPointFun != nullptr) {
            addPointFun(color);
        }
    ImGui::End();
}

void GuiWidget::Render() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GuiWidget::setUpAddPointFunction(void (*addPointFunction)(float* color)) {
    addPointFun = addPointFunction;
}

void GuiWidget::initGui(GLFWwindow *window) {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

