cmake_minimum_required(VERSION 3.17)
project(GraphicsFramework)

set(CMAKE_CXX_STANDARD 14)

set(IMGUI_SOURCES imgui/imgui.cpp imgui/imgui_draw.cpp imgui/imgui_widgets.cpp imgui/imgui_tables.cpp imgui/backends/imgui_impl_opengl3.cpp imgui/backends/imgui_impl_glfw.cpp)

set(SOURCE_FILES Shaders.h Shaders.cpp geometry/Geometry.h geometry/Point.cpp geometry/Point.h GuiWidget.cpp GuiWidget.h Application.cpp Application.h main.cpp window/Window.cpp window/Window.h window/UIContext.cpp window/UIContext.h window/MouseButton.h ui/Scene.cpp ui/Scene.h geometry/Geometry.cpp SimulationMode.h SimulationState.cpp SimulationState.h Direction.h helper_geometry/Vector.cpp helper_geometry/Vector.h helper_geometry/HelperGeometry.h window/GuiState.h)

include_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLEW/include)
include_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLFW/include)
include_directories(${PROJECT_SOURCE_DIR}/Dependencies/glm)
include_directories(${PROJECT_SOURCE_DIR}/imgui)

link_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLEW/lib)
link_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLFW/lib)

#add_compile_definitions(GLEW_STATIC)

find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${IMGUI_SOURCES})
target_link_libraries(${PROJECT_NAME} glew32 glfw3 OpenGL::GL)
