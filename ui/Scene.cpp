//
// Created by hegeda on 2021-09-29.
//

#include <memory>
#include "Scene.h"
#include "../object/Point.h"

void Scene::init() {
    simulationState = SimulationState(SimulationMode::ExplicitEuler, 1.0/60.0);
    simulationState.setBoundingBox(1.0, 1.0, -1.0, -1.0);

    this->addPoint({0, 0});
}

void Scene::render(bool simulateOn) {
    for(const auto &objectPair : objects) {
        const auto &object = objectPair.second;
        if(simulateOn) {
            object->simulate(simulationState);
        }
        object->createAndDraw();
        object->showHelpers();
    }
}

void Scene::on_mouse_move(double x, double y, MouseButton button)
{
    if(this->activeObjectId == -1) {
        return;
    }
    const auto& currentObject = getActiveObject();
    if(button == MouseButton::LeftPress && (currentObject->isInside(x, y) || grabActive)) {
        grabActive = true;
        buttonLastPos = {x, y};
        currentObject->move(x, y);
        currentObject->setFix(true);
    }

    if(button == MouseButton::LeftRelease && grabActive) {
        grabActive = false;
        glm::vec2 diff = glm::vec2(x, y) - buttonLastPos;
        diff *= 15;
        currentObject->getPhysicalProperties()->setVelocity(diff.x, diff.y);
        currentObject->setFix(false);
    }
}

void Scene::move_to_home(double x, double y) {
    if(this->activeObjectId == -1) {
        return;
    }
    const auto& currentObject = objects.find(this->activeObjectId)->second;
    currentObject->move(x, y);
    currentObject->setFix(true);
}

void Scene::setSimulationState(SimulationState simulationState) {
    this->simulationState = simulationState;
}

void Scene::addPoint(glm::vec2 position) {
    auto object = std::make_unique<Point>(position);
    objects.insert(std::make_pair(object->getId(), std::move(object)));
}

std::map<size_t, std::string> Scene::getObjects() const {
    std::map<size_t, std::string> geometries;
    for(const auto& object : objects) {
        geometries.insert({object.first, object.second->getName()});
    }
    return geometries;
}

void Scene::setActiveObject(size_t activeObjectId) {
    if (this->activeObjectId != -1) {
        getActiveObject()->getGeometry()->setColorToDefault();
    }
    this->activeObjectId = activeObjectId;
    getActiveObject()->getGeometry()->setColor(1.0f, 0.4f, 0.4f, 1.0f);
}

const std::unique_ptr<Object> &Scene::getActiveObject() const {
    if(activeObjectId >= 0) {
        return objects.find(this->activeObjectId)->second;
    }
}

void Scene::addStaticPoint(glm::vec2 position) {
    auto object = std::make_unique<Point>(position);
    object->setStatic(true);
    objects.insert(std::make_pair(object->getId(), std::move(object)));
}
