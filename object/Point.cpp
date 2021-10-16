//
// Created by hegeda on 2021-10-12.
//

#include "Point.h"
#include "../geometry/GeometryPoint.h"

Point::Point(glm::vec2 pivotPoint, double radius) :
    Object(std::make_unique<GeometryPoint>(pivotPoint, radius),
            std::make_unique<PhysicalProperties>(pivotPoint)) {
    m_name = "point";
    m_pivot = pivotPoint;
    m_radius = radius;
}

bool Point::isInside(double x, double y) const {
    if(std::abs(x - m_pivot.x) < m_radius && std::abs(y - m_pivot.y) < m_radius) {
        return true;
    }
    return false;
}
