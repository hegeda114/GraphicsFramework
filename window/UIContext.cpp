//
// Created by hegeda on 2021-09-28.
//

#include "UIContext.h"
#include <imgui.h>
#include <imconfig.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <cmath>

void UIContext::pre_render() {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Create the docking environment
    windowFlags = /*ImGuiWindowFlags_NoTitleBar |*/ ImGuiWindowFlags_NoResize;

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

bool UIContext::init(std::shared_ptr<Window> parentWindow, std::shared_ptr<Scene> scene) {
    this->guiState = std::make_shared<GuiState>();
    this->parentWindow = parentWindow;
    this->scene = scene;
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
    ImGui::Begin("InvisibleWindow", nullptr, windowFlags);
        ImGui::AlignTextToFramePadding();
        ImGui::SetWindowSize({300, viewport->Size.y});
        ImGui::PopStyleVar(3);

        guiAddElements();
        guiGlobalSettings();
        guiOutput();
        guiGeometriesList();
        guiCurrentGeomSettings();

    ImGui::End();
}

std::shared_ptr<GuiState> UIContext::getGuiState() const {
    return this->guiState;
}

bool UIContext::isSimStateChanged() {
    bool res = simStateChanged;
    simStateChanged = false;
    return res;
}

void UIContext::guiAddElements() {
    if (ImGui::CollapsingHeader("Add Elements", ImGuiTreeNodeFlags_DefaultOpen)) {
        if(ImGui::Button("Create Point")) {
            scene->addPoint({0, 0});
        }
        if(ImGui::Button("Create Static Point")) {
            scene->addStaticPoint({0, 0});
        }
    }
}

void UIContext::guiGlobalSettings() {
    if (ImGui::CollapsingHeader("Global Settings", ImGuiTreeNodeFlags_DefaultOpen)) {
        static float timestep = 1.0/60.0;
        ImGui::Text("Stepsize: ");
        ImGui::SameLine();
        ImGui::DragFloat("##3", &timestep, 0.00001f, 0.0f, 1.0f, "%.05f");

        ImGui::Spacing();

        static float gravity[2] = {0.0, -9.8};
        ImGui::Text("Gravity: ");
        ImGui::SameLine();
        ImGui::DragFloat2("##1", gravity, 0.005f);

        ImGui::Spacing();

        ImGui::Text("Simulation mode:");
        ImGui::SameLine();
        const char* items[] = {"Explicit Euler", "Implicit Euler" };
        static int item_current = 0;
        ImGui::Combo("combo", &item_current, items, IM_ARRAYSIZE(items));

        ImGui::Spacing();

        if(ImGui::Button("Save changes")) {
            guiState->currentSimState.setGravity({gravity[0], gravity[1]});
            guiState->currentSimState.setTimestep(timestep);
            guiState->currentSimState.setSimMode(static_cast<SimulationMode>(item_current));
            simStateChanged = true;
        }

        ImGui::Spacing();

        std::string start_stop_label = guiState->renderStop ? "Start" : "Stop";
        if(ImGui::Button(start_stop_label.c_str())) {
            guiState->renderStop = !guiState->renderStop;
        }

        ImGui::Spacing();

        ImGui::Checkbox("Delay", &guiState->delayOn);
        ImGui::SameLine();
        ImGui::SliderInt("##2", &guiState->delay, 1, 1000);

    }
}

void UIContext::guiOutput() {
    if (ImGui::CollapsingHeader("Output", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Text("FPS:");
        ImGui::SameLine();
        ImGui::Text("%d", guiState->fps);

//        static float values[90] = { 0 };
//        static int values_offset = 0;
//        static double refresh_time = 0.0;
//        if (false || refresh_time == 0.0)
//            refresh_time = ImGui::GetTime();
//        while (10 < ImGui::GetTime()) // Create dummy data at fixed 60 hz rate for the demo
//        {
//            static float phase = 0.0f;
//            values[values_offset] = cosf(phase);
//            values_offset = (values_offset+1) % IM_ARRAYSIZE(values);
//            phase += 0.10f*values_offset;
//            refresh_time += 1.0f/60.0f;
//        }
//        // Plots can display overlay texts
//        // (in this example, we will display an average value)
//        {
//            float average = 0.0f;
//            for (int n = 0; n < IM_ARRAYSIZE(values); n++)
//                average += values[n];
//            average /= (float)IM_ARRAYSIZE(values);
//            char overlay[32];
//            sprintf(overlay, "avg %f", average);
//            ImGui::PlotLines("Lines", values, IM_ARRAYSIZE(values), values_offset, overlay, -1.0f, 1.0f, ImVec2(0,80));
//        }
    }
}

void UIContext::guiGeometriesList() {
    auto geomMap = scene->getObjects();
//    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4{ 0.4f, 0.15f, 0.15f, 1.0f });
//    ImGui::PushStyleColor(ImGuiCol_Header, ImVec4{  0.7f, 0.15f, 0.15f, 1.0f });
    if (ImGui::CollapsingHeader("Geometries", ImGuiTreeNodeFlags_DefaultOpen)) {
        if (ImGui::BeginTable("geom_table", 1))
        {
            int i = 0;
            for (const auto& geom: geomMap)
            {
                char label[32];
                sprintf(label, "%s##%d", geom.second.c_str(), i);
                const bool item_is_selected = !selection.empty() && selection[0] == geom.first;

                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);

                ImGuiSelectableFlags selectable_flags = ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowItemOverlap;
                if (ImGui::Selectable(label, item_is_selected, selectable_flags))
                {
                    selection.clear();
                    scene->disableActiveObject();
                    selection.push_back(geom.first);
                    scene->setActiveObject(geom.first);
//                    if(selection[0] != item_is_selected) {
//                        selection.push_back(geom.first);
//                        scene->setActiveObject(geom.first);
//                    }
                }
                i++;
            }
            ImGui::EndTable();
        }
    }
}

void UIContext::guiCurrentGeomSettings() {
    if (selection.empty()) {
        return;
    }
    if (ImGui::CollapsingHeader("Active Geometry Settings", ImGuiTreeNodeFlags_DefaultOpen)) {
        const auto& currentGeom = scene->getActiveObject();
        ImGui::Text("Name: %s", currentGeom->getName().c_str());
    }
}
