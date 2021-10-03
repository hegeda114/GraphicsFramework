//
// Created by hegeda on 2021-10-03.
//

#include "Geometry.h"

bool Geometry::isFix() const {
    return fix;
}
void Geometry::setFix(bool isFix) {
    fix = isFix;
}

void Geometry::simulate(SimulationState simState) {
    if(fix) {
        return;
    }
    if(simState.getSimMode() == SimulationMode::ExplicitEuler) {
        explicitEuler(simState);
    }
}

void Geometry::setColor(double red, double green, double blue, double alpha) {
    this->color[0] = red;
    this->color[0] = green;
    this->color[0] = blue;
    this->color[0] = alpha;
}
