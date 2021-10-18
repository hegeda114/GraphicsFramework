//
// Created by hegeda on 2021-10-12.
//

#include "Object.h"

size_t Object::lastId = 0;

size_t Object::nextId() {
    return lastId++;
}

Object::Object(std::unique_ptr<Geometry> geometry, std::unique_ptr<PhysicalProperties> physicalProperties) :
        m_velocityVector({m_pivot, m_pivot}), m_forceVector({m_pivot, m_pivot}){
    m_geometry = std::move(geometry);
    m_physicalProperties = std::move(physicalProperties);
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

size_t Object::getId() const {
    return m_id;
}

void Object::setName(const std::string &newName) {
    m_name = newName;
}

const std::unique_ptr<Geometry> &Object::getGeometry() const {
    return m_geometry;
}

const std::unique_ptr<PhysicalProperties> &Object::getPhysicalProperties() const {
    return m_physicalProperties;
}

void Object::move(const glm::vec2 &targetPosition) {
    move(targetPosition.x, targetPosition.y);
}

void Object::move(double toX, double toY) {
    m_pivot.x = (float) toX;
    m_pivot.y = (float) toY;
    m_physicalProperties->setPosition(m_pivot);
    m_geometry->setPosition(m_pivot);
    for(const auto& connection : m_connections) {
        connection->connectionChangedEvent();
    }
}

void Object::simulate(SimulationState simState) {
    if(m_fix || m_static) {
        return;
    }
    glm::vec2 forceFromConnection = {0, 0};
    for(const auto& connection : m_connections) {
        forceFromConnection = connection->getExertedForce(reinterpret_cast<const Geometry *>(this));
    }
    if(simState.getSimMode() == SimulationMode::ExplicitEuler) {
        m_physicalProperties->addForce(forceFromConnection);
        m_physicalProperties->explicitEuler(simState);
    }

    m_pivot = m_physicalProperties->getPosition();
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
        m_velocityVector.setEndPoint(m_pivot + 0.05f*m_physicalProperties->getVelocity());
        m_velocityVector.create();

        m_velocityVector.draw();
    }
    if(m_showForces) {
        m_forceVector.setStartPoint(m_pivot);
        glm::vec2 forcesSum = m_physicalProperties->getResultaltForces();
        m_forceVector.setEndPoint(m_pivot + 0.05f*forcesSum);
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

glm::vec2 Object::getPosition() const {
    return m_pivot;
}

void Object::addConnection(std::shared_ptr<Object> object) {
    m_connections.emplace_back(object);
}

glm::vec2 Object::getVelocity() const {
    return m_physicalProperties->getVelocity();
}
