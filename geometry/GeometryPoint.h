//
// Created by hegeda on 2021-02-11.
//

#ifndef GRAPHICSFRAMEWORK_GEOMETRY_POINT_H
#define GRAPHICSFRAMEWORK_GEOMETRY_POINT_H

#include "Geometry.h"
#include "glm.hpp"

class GeometryPoint : public Geometry {
private:
    double m_radius = 0.01;

public:
    explicit GeometryPoint(glm::vec2 position, double radius);

    void create() final;
    void draw() final;
};


#endif //GRAPHICSFRAMEWORK_GEOMETRY_POINT_H
