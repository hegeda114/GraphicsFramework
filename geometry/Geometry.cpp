//
// Created by hegeda on 2021-10-03.
//

#include "Geometry.h"

size_t Geometry::current_id = 0;

bool Geometry::isFix() const {
    return fix;
}
void Geometry::setFix(bool isFix) {
    fix = isFix;
}

void Geometry::simulate(SimulationState simState) {
    if(fix || is_static) {
        return;
    }
    if(simState.getSimMode() == SimulationMode::ExplicitEuler) {
        explicitEuler(simState);
    }
}

void Geometry::setColor(double red, double green, double blue, double alpha) {
    color = {red, green, blue, alpha};
}

size_t Geometry::getNextId() {
    return current_id++;
}

std::string Geometry::getName() const {
    return name;
}

size_t Geometry::getId() const {
    return id;
}

void Geometry::setColorToDefault() {
    color = defaultColor;
}

void Geometry::setVel(double x, double y) {
    vel.x = x;
    vel.y = y;
}

bool Geometry::isStatic() const {
    return is_static;
}

void Geometry::setStatic(bool isStatic) {
    is_static = isStatic;
}
