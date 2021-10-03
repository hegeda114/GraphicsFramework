//
// Created by hegeda on 2021-10-03.
//

#ifndef GRAPHICSFRAMEWORK_HELPERGEOMETRY_H
#define GRAPHICSFRAMEWORK_HELPERGEOMETRY_H

#include "../geometry/Geometry.h"

class HelperGeometry : public Geometry {
    void create() override = 0;
    void draw() override = 0;

private:
    bool isInside(double x, double y) const override {};
    void move(double toX, double toY) override {};
    void explicitEuler(SimulationState simState) override {};
};

#endif //GRAPHICSFRAMEWORK_HELPERGEOMETRY_H
