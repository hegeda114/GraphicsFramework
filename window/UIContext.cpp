//
// Created by hegeda on 2021-09-28.
//

#include "UIContext.h"
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

void UIContext::pre_render() {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Create the docking environment
    windowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;

    viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(3.0f, 3.0f));
}

void UIContext::post_render() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool UIContext::init(Window* parentWindow) {
    this->parentWindow = parentWindow;
    const char* glsl_version = "#version 410";

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    auto& colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.1f, 0.1f, 1.0f };

    colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.2f, 0.2f, 1.0f };
    colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.3f, 0.3f, 1.0f };
    colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };

    colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.2f, 0.2f, 1.0f };
    colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.3f, 0.3f, 1.0f };
    colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };

    colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.2f, 0.2f, 1.0f };
    colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.3f, 0.3f, 1.0f };
    colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };

    colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };
    colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.38f, 0.38f, 1.0f };
    colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.28f, 0.28f, 1.0f };
    colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.2f, 0.2f, 1.0f };

    colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };
    colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.15f, 0.15f, 1.0f };

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(this->parentWindow->getGLFWWindow(), true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    return true;
}

void UIContext::render() {
    ImGui::AlignTextToFramePadding();
    ImGui::Begin("InvisibleWindow", nullptr, windowFlags);
        ImGui::SetWindowSize({300, viewport->Size.y});
        ImGui::PopStyleVar(3);

        guiGlobalSettings();
        guiOutput();

    ImGui::End();
}

SimulationState UIContext::getCurrentSimState() const {
    return currentSimState;
}

bool UIContext::isSimStateChanged() {
    bool res = simStateChanged;
    simStateChanged = false;
    return res;
}

void UIContext::guiGlobalSettings() {
    if (ImGui::CollapsingHeader("Global Settings", ImGuiTreeNodeFlags_DefaultOpen)) {
        static float timestep = 1.0/60.0;
        ImGui::Text("Stepsize: ");
        ImGui::SameLine();
        ImGui::DragFloat("", &timestep, 0.00001f, 0.0f, 1.0f, "%.05f");

        ImGui::Spacing();

        static float gravity[2] = {0.0, -9.8};
        ImGui::Text("Gravity: ");
        ImGui::SameLine();
        ImGui::DragFloat2("", gravity, 0.005f);

        ImGui::Spacing();

        ImGui::Text("Simulation mode:");
        ImGui::SameLine();
        const char* items[] = {"Explicit Euler", "Implicit Euler" };
        static int item_current = 0;
        ImGui::Combo("combo", &item_current, items, IM_ARRAYSIZE(items));

        ImGui::Spacing();

        if(ImGui::Button("Save changes")) {
            currentSimState.setGravity({gravity[0], gravity[1]});
            currentSimState.setTimestep(timestep);
            currentSimState.setSimMode(static_cast<SimulationMode>(item_current));
            simStateChanged = true;
        }

        ImGui::Spacing();
    }
}

void UIContext::guiOutput() {
    if (ImGui::CollapsingHeader("Output", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Text("FPS:");
        ImGui::SameLine();
        ImGui::Text("%d", this->fps);
    }
}

void UIContext::setFPS(size_t currentFPS) {
    this->fps = currentFPS;
}
