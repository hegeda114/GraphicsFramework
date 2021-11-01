//
// Created by hegeda on 2021-11-01.
//

#ifndef GRAPHICSFRAMEWORK_SCENEWINDOW_H
#define GRAPHICSFRAMEWORK_SCENEWINDOW_H


#include "../Scene.h"

struct SceneWindow {
    static void create(const Scene& scene);
    static ImVec2 sceneWindowCurrentPos;
    static ImVec2 sceneWindowCurrentSize;
};


#endif //GRAPHICSFRAMEWORK_SCENEWINDOW_H