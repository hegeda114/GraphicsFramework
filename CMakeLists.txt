cmake_minimum_required(VERSION 3.17)
project(GraphicsFramework)

set(CMAKE_CXX_STANDARD 14)

set(IMGUI_SOURCES imgui/imgui.cpp imgui/imgui_demo.cpp imgui/imgui_draw.cpp imgui/imgui_widgets.cpp imgui/imgui_tables.cpp imgui/backends/imgui_impl_opengl3.cpp imgui/backends/imgui_impl_glfw.cpp)

set(SOURCE_FILES Shaders.h Shaders.cpp geometry/Geometry.h geometry/GeometryPoint.cpp geometry/GeometryPoint.h Application.cpp Application.h main.cpp window/Window.cpp window/Window.h ui/UIContext.cpp ui/UIContext.h window/MouseButton.h Scene.cpp Scene.h geometry/Geometry.cpp simulation/SimulationState.cpp simulation/SimulationState.h CommonEnums.h ui/GuiState.h object/Object.cpp object/Object.h simulation/SimulationProperties.cpp simulation/SimulationProperties.h object/Point.cpp object/Point.h object/Spring.cpp object/Spring.h geometry/GeometryLine.cpp geometry/GeometryLine.h geometry/GeometryVector.cpp geometry/GeometryVector.h IO.cpp IO.h)

include_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLEW/include)
include_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLFW/include)
include_directories(${PROJECT_SOURCE_DIR}/Dependencies/glm)
include_directories(${PROJECT_SOURCE_DIR}/imgui)

if (${WIN32})
    link_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLEW/lib)
    link_directories(${PROJECT_SOURCE_DIR}/Dependencies/GLFW/lib)
endif()


#add_compile_definitions(GLEW_STATIC)

find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${IMGUI_SOURCES})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror -Wno-unused-variable -Wno-unused-parameter)

if (${WIN32})
    target_link_libraries(${PROJECT_NAME} glew32 glfw3 OpenGL::GL)
elseif(${UNIX})
    target_link_libraries(${PROJECT_NAME} GLEW glfw OpenGL::GL)
endif()
