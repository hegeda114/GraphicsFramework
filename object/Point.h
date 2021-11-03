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
    static int lastPointId;

    /**
     * Returns the next free point id based on lastId.
     * @return The next free point id.
     */
    static int nextPointId();
    double m_radius;
public:
    /**
     *
     * @param pivotPoint The pivot point of the object.
     * @param radius The radius of the point.
     */
    explicit Point(glm::vec2 pivotPoint, double radius = 0.01);

    Point(const Point& point);

    /**
     * Returns true if the given position is inside of the point, otherwise false.
     * @param x The x coordinate of the tested position.
     * @param y The y coordinate of the tested position.
     * @return True if the position is inside of the point, otherwise false.
     */
    bool isInside(double x, double y) const final;

    ObjectType getType() const final;

    std::string getSerializedData() const final;

    static std::shared_ptr<Point> createPointFromSavedData(const std::string& serializedData);

    void connectionChangedEvent() const final {};

};


#endif //GRAPHICSFRAMEWORK_POINT_H
