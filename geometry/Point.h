//
// Created by hegeda on 2021-02-11.
//

#ifndef GRAPHICSFRAMEWORK_POINT_H
#define GRAPHICSFRAMEWORK_POINT_H

#include "Geometry.h"
#include "glm.hpp"
#include "../helper_geometry/HelperGeometry.h"
#include "../helper_geometry/Vector.h"

using namespace glm;

class Point : public Geometry {
private:
    vec2 center = {0, 0};
    double radius = 0.01;
    size_t samples = 100;

    vec2 currentForces = {0, 0};

    Vector velocityVector;
    Vector forceVector;

    bool showVelocity = true;
    bool showForces = false;

public:
    explicit Point(vec2 position);  //TODO rádiusz-os konstruktor is kell

    void create() override;
    void draw() override;

    bool isInside(double x, double y) const override;

    void move(double toX, double toY) override;

    void showHelpers() override;

    void explicitEuler(SimulationState simState) override;

    void setShowVelocity(bool showVelocity);
    void setShowForces(bool showForces);
};


#endif //GRAPHICSFRAMEWORK_POINT_H
