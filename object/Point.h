//
// Created by hegeda on 2021-10-12.
//

#ifndef GRAPHICSFRAMEWORK_POINT_H
#define GRAPHICSFRAMEWORK_POINT_H


#include "Object.h"
#include "glm.hpp"

class Point : public Object {
private:
    double m_radius;
public:
    explicit Point(glm::vec2 pivotPoint, double radius = 0.01);

    bool isInside(double x, double y) const override;

};


#endif //GRAPHICSFRAMEWORK_POINT_H
