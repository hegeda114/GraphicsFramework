//
// Created by hegeda on 2021-10-12.
//

#include "Object.h"

int Object::lastId = 0;

int Object::nextId() {
    return lastId++;
}

Object::Object(std::unique_ptr<Geometry> geometry, std::unique_ptr<SimulationProperties> physicalProperties) :
        m_velocityVector({m_pivot, m_pivot}), m_forceVector({m_pivot, m_pivot}){
    m_geometry = std::move(geometry);
    m_simulationProperties = std::move(physicalProperties);
    m_id = nextId();
    m_name = "object";
}

bool Object::isInside(const glm::vec2 &position) const {
    return isInside(position.x, position.y);
}

bool Object::isStatic() const {
    return m_static;
}

void Object::setStatic(bool isStatic) {
    m_static = isStatic;
    if(m_static) {
        m_geometry->setColor(0.4f, 0.7f, 0.96f, 1.0f);
    } else {
        m_geometry->setColorToDefault();
    }
}

bool Object::isFix() const {
    return m_fix;
}
void Object::setFix(bool isFix) {
    m_fix = isFix;
}

std::string Object::getName() const {
    return m_name;
}

int Object::getId() const {
    return m_id;
}

void Object::setName(const std::string &newName) {
    m_name = newName;
}

const std::unique_ptr<Geometry> &Object::getGeometry() const {
    return m_geometry;
}

const std::unique_ptr<SimulationProperties> &Object::getSimulationProperties() const {
    return m_simulationProperties;
}

void Object::move(const glm::vec2 &targetPosition) {
    move(targetPosition.x, targetPosition.y);
}

void Object::move(double toX, double toY) {
    m_simulationProperties->setVelocity(0, 0);
    m_simulationProperties->clearForces();
    m_pivot.x = (float) toX;
    m_pivot.y = (float) toY;
    m_simulationProperties->setPosition(m_pivot);
    m_geometry->setPosition(m_pivot);
    for(const auto& connection : m_connections) {
        connection->connectionChangedEvent();
    }
}

void Object::simulate(SimulationState simState) {
    if(m_fix || m_static) {
        return;
    }
    if(simState.getSimMode() == SimulationMode::ExplicitEuler) {
        m_simulationProperties->explicitEuler(simState);
    }

    m_pivot = m_simulationProperties->getPosition();
    m_geometry->setPosition(m_pivot);
    for(const auto& connection : m_connections) {
        connection->connectionChangedEvent();
    }
}

void Object::showHelpers() {
    if (m_fix) {
        return;
    }
    if(m_showVelocity) {
        m_velocityVector.setStartPoint(m_pivot);
        m_velocityVector.setEndPoint(m_pivot + 0.05f * m_simulationProperties->getVelocity());
        m_velocityVector.create();

        m_velocityVector.draw();
    }
    if(m_showForces) {
        m_forceVector.setStartPoint(m_pivot);
        glm::vec2 forcesSum = m_simulationProperties->getResultaltForces();
        m_forceVector.setEndPoint(m_pivot - 0.5f*forcesSum);
        m_forceVector.create();

        m_forceVector.draw();
    }
}

void Object::setShowVelocity(bool showVelocity) {
    this->m_showVelocity = showVelocity;
}

void Object::setShowForces(bool showForces) {
    this->m_showForces = showForces;
}

void Object::createAndDraw() {
    m_geometry->create();
    m_geometry->draw();
}

void Object::addConnection(std::shared_ptr<Object> object) {
    m_connections.emplace_back(object);
}

void Object::setPosition(glm::vec2 position) {
    m_pivot = position;
    m_simulationProperties->setPosition(position);
}
