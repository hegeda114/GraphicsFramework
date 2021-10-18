//
// Created by hegeda on 2021-09-29.
//

#include <memory>
#include "Scene.h"
#include "../object/Spring.h"

void Scene::init() {
    simulationState = SimulationState(SimulationMode::ExplicitEuler, 1.0/60.0);
    simulationState.setBoundingBox(1.0, 1.0, -1.0, -1.0);

    auto point1 = this->addPoint({0, 0});
    point1->setStatic(true);
    auto point2 = this->addPoint({0.2, 0.1});
    this->addSpring(point1, point2);
    auto point3 = this->addPoint({0.4, 0.2});
    this->addSpring(point2, point3);
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

std::shared_ptr<Point> Scene::addPoint(glm::vec2 position) {
    auto object = std::make_shared<Point>(position);
    objects.insert(std::make_pair(object->getId(), object));
    return object;
}

void Scene::addSpring(const std::shared_ptr<Point>& i, const std::shared_ptr<Point>& j) {
    auto object = std::make_shared<Spring>(i, j, 0.1, 0.1, 0.1);
    i->addConnection(object);
    j->addConnection(object);
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
    this->activeObjectId = activeObjectId;
    getActiveObject()->getGeometry()->setColor(1.0f, 0.4f, 0.4f, 1.0f);
}


const std::shared_ptr<Object> &Scene::getActiveObject() const {
    if(activeObjectId >= 0) {
        return objects.find(this->activeObjectId)->second;
    }
}

void Scene::addStaticPoint(glm::vec2 position) {
    auto object = std::make_shared<Point>(position);
    object->setStatic(true);
    objects.insert(std::make_pair(object->getId(), std::move(object)));
}

void Scene::disableActiveObject() {
    if (this->activeObjectId != -1) {
        getActiveObject()->getGeometry()->setColorToDefault();
    }
}
