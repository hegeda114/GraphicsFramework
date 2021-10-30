//
// Created by hegeda on 2021-10-13.
//

#include <sstream>
#include "Spring.h"
#include "../geometry/GeometryLine.h"

int Spring::lastSpringId = 1;

int Spring::nextSpringId() {
    return lastSpringId++;
}

Spring::Spring(const std::shared_ptr<Point>& i, const std::shared_ptr<Point>& j, float stretching, float dampingCoefficient, float defaultLength) :
   Object(std::make_unique<GeometryLine>(i->getSimulationProperties()->getPosition(), j->getSimulationProperties()->getPosition()),
   std::make_unique<SimulationProperties>(glm::vec2(0, 0))), m_i(i), m_j(j) {
    m_name = std::string("Spring_") + std::to_string(nextSpringId());
    m_ks = stretching;
    m_kd = dampingCoefficient;
    m_l0 = defaultLength;
}

void Spring::calculateSpringForces() {
    // calculate force for i:
    glm::vec2 posDiff, velDiff;
    posDiff = (m_j->getSimulationProperties()->getPosition() - m_i->getSimulationProperties()->getPosition());
    velDiff = (m_j->getSimulationProperties()->getVelocity() - m_i->getSimulationProperties()->getVelocity());
    glm::vec2 force = calcForce(posDiff, velDiff);
    m_i->getSimulationProperties()->addForce(force);

    // calculate force for j:
    posDiff = (m_i->getSimulationProperties()->getPosition() - m_j->getSimulationProperties()->getPosition());
    velDiff = (m_i->getSimulationProperties()->getVelocity() - m_j->getSimulationProperties()->getVelocity());
    force = calcForce(posDiff, velDiff);
    m_j->getSimulationProperties()->addForce(force);
}

glm::vec2 Spring::calcForce(glm::vec2 posDiff, glm::vec2 velDiff) const {
    float lenposdiff = glm::length(posDiff);
    return (posDiff / lenposdiff) * m_ks * (lenposdiff - m_l0); //TODO ezt pontosítani!
}

void Spring::connectionChangedEvent() {
    dynamic_cast<GeometryLine&>(*m_geometry).setStartPoint(m_i->getSimulationProperties()->getPosition());
    dynamic_cast<GeometryLine&>(*m_geometry).setEndPoint(m_j->getSimulationProperties()->getPosition());
}

ObjectType Spring::getType() const {
    return ObjectType::SpringObject;
}

std::string Spring::getSerializedData() const {
    //TODO: m_name-be ne lehessen speciális karakter, és max hossza is legyen!
    //(const std::shared_ptr<Point>& i, const std::shared_ptr<Point>& j, float stretching, float dampingCoefficient, float defaultLength
    char buffer [200];
    std::string is_static = "true";
    if(!m_static) is_static = "false";
    sprintf(buffer, "%s;%s;%f;%f;%f;%s", m_i->getName().c_str(), m_j->getName().c_str(), m_ks, m_kd, m_l0, m_name.c_str());
    return buffer;
}

std::shared_ptr<Spring> Spring::createSpringFromSavedData(const std::shared_ptr<Point>& i, const std::shared_ptr<Point>& j, const std::string &serializedData) {
    std::stringstream ss(serializedData);
    std::string val;

    getline(ss, val, ';'); // point i
    getline(ss, val, ';'); // point j

    getline(ss, val, ';');
    double ks = std::stod(val);

    getline(ss, val, ';');
    double kd= std::stod(val);

    getline(ss, val, ';');
    double l0 = std::stod(val);

    getline(ss, val, ';');
    std::string name = val;

    std::shared_ptr<Spring> spring = std::make_shared<Spring>(i, j, ks, kd, l0);
    spring->setName(name);
    return spring;
}

std::shared_ptr<Point> Spring::getI() const {
    return m_i;
}

std::shared_ptr<Point> Spring::getJ() const {
    return m_j;
}
