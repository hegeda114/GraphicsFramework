//
// Created by hegeda on 2021-02-11.
//

#ifndef GRAPHICSFRAMEWORK_POINT_H
#define GRAPHICSFRAMEWORK_POINT_H

#include "Geometry.h"
#include "glm.hpp"
using namespace glm;

class Point : public Geometry {
    vec2 p;
    float size = 7;
    float color[4] = {0.0, 0.0, 0.0, 0.0};

    vec2 vel = {0.3, 0.3};
    vec2 gravity = {0, -9.8};
public:
    Point(vec2 position);
    Point(vec2 position, const float* color);
    void create() override;
    void Draw() override;
    bool isInside(float x, float y) const override;
    void Grab(float toX, float toY) override;
    bool isMovable() const override;
    void changeSize(float size);
    void toString() const;
    void simulate(float timestep = 1.0/60);
};


#endif //GRAPHICSFRAMEWORK_POINT_H
