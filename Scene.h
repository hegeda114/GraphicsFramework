//
// Created by hegeda on 2021-02-11.
//

#ifndef CHERNO01_SCENE_H
#define CHERNO01_SCENE_H

#include <glew.h>
#include <iostream>
#include <vector>
#include "glm.hpp"
#include "Geometry.h" //TODO itt inkább Object legyen?
using namespace glm;

class Scene {
    std::vector<Geometry*> geometries;
public:
    void Build();
    void Render() const;

    Geometry* getTopGeometry(vec2 position) const;
    void addPoint(Geometry* geom);

    void Animate();
};

#endif //CHERNO01_SCENE_H
