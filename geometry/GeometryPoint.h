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
    static const size_t m_resolution = 100;

public:
    explicit GeometryPoint(const glm::vec2& position, double radius);

    void create() const final;
    void draw() const final;
};


#endif //GRAPHICSFRAMEWORK_GEOMETRY_POINT_H
