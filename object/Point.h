//
// Created by hegeda on 2021-10-12.
//

#ifndef GRAPHICSFRAMEWORK_POINT_H
#define GRAPHICSFRAMEWORK_POINT_H


#include "Object.h"
#include "glm.hpp"

class Point : public Object {
private:
    // Stores the currently last point id.
    static size_t lastPointId;

    /**
     * Returns the next free point id based on lastId.
     * @return The next free point id.
     */
    static size_t nextPointId();
    double m_radius;
public:
    /**
     *
     * @param pivotPoint The pivot point of the object.
     * @param radius The radius of the point.
     */
    explicit Point(glm::vec2 pivotPoint, double radius = 0.01);

    /**
     * Returns true if the given position is inside of the point, otherwise false.
     * @param x The x coordinate of the tested position.
     * @param y The y coordinate of the tested position.
     * @return True if the position is inside of the point, otherwise false.
     */
    bool isInside(double x, double y) const override;

    ObjectType getType() const override;

};


#endif //GRAPHICSFRAMEWORK_POINT_H
