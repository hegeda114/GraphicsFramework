//
// Created by hegeda on 2021-10-12.
//

#include "Object.h"

int Object::lastId = 0;

int Object::nextId() {
    return lastId++;
}

Object::Object(std::unique_ptr<Geometry> geometry, std::unique_ptr<SimulationProperties> physicalProperties) :
        m_velocityVector(std::make_unique<GeometryVector>(m_pivot, m_pivot)),
        m_forceVector(std::make_unique<GeometryVector>(m_pivot, m_pivot)){
    m_geometry = std::move(geometry);
    m_simulationProperties = std::move(physicalProperties);
    m_id = nextId();
    m_name = "object";
    m_velocityVector->setColor(0.3, 0.6, 0.7, 1.0);
    m_forceVector->setColor(0.7, 0.6, 0.3, 1.0);
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
        m_geometry->setDefaultColor(0.4f, 0.7f, 0.96f, 1.0f);
        m_geometry->setColor(0.4f, 0.7f, 0.96f, 1.0f);
        m_simulationProperties->setInvMass(0);
    } else {
        m_geometry->setDefaultColor(0.87f, 0.9f, 0.4f, 1.0f);
        m_geometry->setColorToDefault();
        m_simulationProperties->setInvMass(1);
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

bool Object::setName(const std::string &newName) {
    if(newName.find('\\') != std::string::npos || newName.find(';') != std::string::npos || newName.length() > 30) {
        return false;
    }
    m_name = newName;
    return true;
}

const std::unique_ptr<Geometry> &Object::getGeometry() const {
    return m_geometry;
}

const std::unique_ptr<SimulationProperties> &Object::getSimProp() const {
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

void Object::simulate(const GlobalSimulationSettings* globalSimulationSettings) {
    if(m_fix || m_static) {
        return;
    }
    if(globalSimulationSettings->getSimApproach() == SimulationApproach::MassSpringSystem) {
        if(globalSimulationSettings->getSimMode() == SimulationMode::ExplicitEuler) {
            m_simulationProperties->explicitEuler(globalSimulationSettings);
        }
        if(globalSimulationSettings->getSimMode() == SimulationMode::SemiImplicitEuler) {
            m_simulationProperties->semiImplicitEuler(globalSimulationSettings);
        }
        if(globalSimulationSettings->getSimMode() == SimulationMode::RungeKuttaSecondOrder) {
            m_simulationProperties->rungeKuttaSecondOrder(globalSimulationSettings);
        }
        if(globalSimulationSettings->getSimMode() == SimulationMode::RungeKuttaFourthOrder) {
            m_simulationProperties->rungeKuttaFourthOrder(globalSimulationSettings);
        }
    }
    if(globalSimulationSettings->getSimApproach() == SimulationApproach::PositionBasedDynamics) {
        if(globalSimulationSettings->getPBDConstraint() == PBDConstraint::Stretching) {
            m_simulationProperties->pbdConstraint(globalSimulationSettings);
        }
    }

    m_pivot = m_simulationProperties->getPosition();
    m_geometry->setPosition(m_pivot);
    for(const auto& connection : m_connections) {
        connection->connectionChangedEvent();
    }
}

void Object::renderHelpers(const Shader *shader) {
    if (m_fix) {
        return;
    }
    if(m_velocityVector->getVisibility()) {
        m_velocityVector->calculateVector(m_pivot, m_simulationProperties->getVelocity());
        m_velocityVector->renderHelper(shader);
    }
    if(m_forceVector->getVisibility()) {
        m_forceVector->calculateVector(m_pivot, m_simulationProperties->getResultantForcesForHelpers());
        m_forceVector->renderHelper(shader);
    }
}

void Object::render(const Shader* shader) const {
    m_geometry->update(shader);
    m_geometry->create();
    m_geometry->draw();
}

void Object::addConnection(const std::shared_ptr<Object>& object) {
    m_connections.emplace_back(object);
}

void Object::setPosition(const glm::vec2& position) {
    m_pivot = position;
    m_simulationProperties->setPosition(position);
}

const std::unique_ptr<GeometryVector>& Object::getVelocityHelper() const {
    return m_velocityVector;
}

const std::unique_ptr<GeometryVector>& Object::getForceHelper() const {
    return m_forceVector;
}