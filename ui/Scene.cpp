//
// Created by hegeda on 2021-09-29.
//

#include <memory>
#include "Scene.h"

void Scene::init() {
    simulationState = SimulationState(SimulationMode::ExplicitEuler, 1.0/60.0);
    simulationState.setBoundingBox(1.0, 1.0, -1.0, -1.0);

    this->addPoint({0, 0});
}

void Scene::render(bool simulateOn) {
    for(const auto &geomPair : geomMap) {
        const auto &geom = geomPair.second;
        if(simulateOn) {
            geom->simulate(simulationState);
        }
        geom->create();
        geom->draw();
        geom->showHelpers();
    }
}

void Scene::on_mouse_move(double x, double y, MouseButton button)
{
    if(this->activeGeomId == -1) {
        return;
    }
    const auto& currentGeom = getActiveGeom();
    if(button == MouseButton::LeftPress && (currentGeom->isInside(x, y) || grabActive)) {
        grabActive = true;
        buttonLastPos = {x, y};
        currentGeom->move(x, y);
        currentGeom->setFix(true);
    }

    if(button == MouseButton::LeftRelease && grabActive) {
        grabActive = false;
        vec2 diff = vec2(x, y) - buttonLastPos;
        diff *= 15;
        currentGeom->setVel(diff.x, diff.y);
        currentGeom->setFix(false);
    }
}

void Scene::move_to_home(double x, double y) {
    if(this->activeGeomId == -1) {
        return;
    }
    const auto& currentGeom = geomMap.find(this->activeGeomId)->second;
    currentGeom->move(x, y);
    currentGeom->setFix(true);
}

void Scene::setSimulationState(SimulationState simulationState) {
    this->simulationState = simulationState;
}

void Scene::addPoint(vec2 position) {
    auto geom = std::make_unique<Point>(position);
    geomMap.insert(std::make_pair(geom->getId(), std::move(geom)));
}

std::map<size_t, std::string> Scene::getGeometries() const {
    std::map<size_t, std::string> geometries;
    for(const auto& geom : geomMap) {
        geometries.insert({geom.first, geom.second->getName()});
    }
    return geometries;
}

void Scene::setActiveGeom(size_t activeGeomId) {
    if (this->activeGeomId != -1) {
        getActiveGeom()->setColorToDefault();
    }
    this->activeGeomId = activeGeomId;
    getActiveGeom()->setColor(1.0f, 0.7f, 0.7f, 1.0f);
}

const std::unique_ptr<Geometry> &Scene::getActiveGeom() const {
    if(activeGeomId >= 0) {
        return geomMap.find(this->activeGeomId)->second;
    }
}

void Scene::addStaticPoint(vec2 position) {
    auto geom = std::make_unique<Point>(position);
    geom->setStatic(true);
    geomMap.insert(std::make_pair(geom->getId(), std::move(geom)));
}
