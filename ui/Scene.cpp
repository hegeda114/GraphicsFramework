//
// Created by hegeda on 2021-09-29.
//

#include <memory>
#include <iostream>
#include <winnt.h>
#include "Scene.h"

void Scene::init() {
    simulationState = SimulationState(SimulationMode::ExplicitEuler, 1.0/60.0);
    simulationState.setBoundingBox(1.0, 1.0, -1.0, -1.0);
    testPoint = std::make_unique<Point>(vec2{0.0f, 0.0f});
    testPoint->setFix(false);
    testVector = std::make_unique<Vector>(vec2{0.0f, 0.0f}, vec2{0.2f, 0.3f});
}

void Scene::render() {
    testPoint->simulate(simulationState);
    testPoint->showHelpers();
    testPoint->create();
    testPoint->draw();

}

void Scene::on_mouse_move(double x, double y, MouseButton button)
{
//    if(button == MouseButton::Left) {
//        printf("ok\t");
//        printf("x: %f, y: %f\n", x, y);
//    }
    if(button == MouseButton::LeftPress && (testPoint->isInside(x, y) || grabActive)) {
        grabActive = true;
        buttonLastPos = {x, y};
        testPoint->move(x, y);
        testPoint->setFix(true);
    }

    if(button == MouseButton::LeftRelease && grabActive) {
        grabActive = false;
        vec2 diff = vec2(x, y) - buttonLastPos;
        diff *= 15;
        testPoint->setVel(diff.x, diff.y);
        testPoint->setFix(false);
    }
}

void Scene::move_to_home(double x, double y) {
    testPoint->move(x, y);
    testPoint->setFix(true);
}

void Scene::setSimulationState(SimulationState simulationState) {
    this->simulationState = simulationState;
}
