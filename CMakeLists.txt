cmake_minimum_required(VERSION 3.17)
project(GraphicsFramework)

set(CMAKE_CXX_STANDARD 14)

set(IMGUI_SOURCES imgui/imgui.cpp imgui/imgui_draw.cpp imgui/imgui_widgets.cpp imgui/imgui_tables.cpp imgui/backends/imgui_impl_opengl3.cpp imgui/backends/imgui_impl_glfw.cpp)

set(SOURCE_FILES main.cpp Shaders.h Shaders.cpp Circle.cpp Circle.h Geometry.h Scene.cpp Scene.h Point.cpp Point.h GuiWidget.cpp GuiWidget.h)

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
