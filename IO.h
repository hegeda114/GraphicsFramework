//
// Created by hegeda on 2021-10-26.
//

#ifndef GRAPHICSFRAMEWORK_IO_H
#define GRAPHICSFRAMEWORK_IO_H


#include "Scene.h"

class IO {
public:
    static void save_scene(const Scene *scene, const std::string& filePath);
    static void open_scene(const std::string& filePath, Scene *scene);
};


#endif //GRAPHICSFRAMEWORK_IO_H
