//
// Created by hegeda on 2021-10-13.
//

#include "Spring.h"
#include "../geometry/GeometryLine.h"

Spring::Spring(const std::shared_ptr<Point>& i, const std::shared_ptr<Point>& j, float stretching, float dampingCoefficient, float defaultLength) :
   Object(std::make_unique<GeometryLine>(i->getPosition(), j->getPosition()),
   std::make_unique<PhysicalProperties>(glm::vec2(0, 0))), m_i(i), m_j(j) {
    m_ks = stretching;
    m_kd = dampingCoefficient;
    m_l0 = defaultLength;
}

void Spring::calculateSpringForces() {
    // calculate force for i:
    glm::vec2 posDiff, velDiff;
    posDiff = (m_j->getPosition() - m_i->getPosition());
    velDiff = (m_j->getVelocity() - m_i->getVelocity());
    glm::vec2 force = calcForce(posDiff, velDiff);
    m_i->getPhysicalProperties()->addForce(force);

    // calculate force for j:
    posDiff = (m_i->getPosition() - m_j->getPosition());
    velDiff = (m_i->getVelocity() - m_j->getVelocity());
    force = calcForce(posDiff, velDiff);
    m_j->getPhysicalProperties()->addForce(force);
}

glm::vec2 Spring::calcForce(glm::vec2 posDiff, glm::vec2 velDiff) const {
    float lenposdiff = glm::length(posDiff);
    return (posDiff / lenposdiff) * m_ks * (lenposdiff - m_l0); //TODO ezt pontosítani!
}

void Spring::connectionChangedEvent() {
    dynamic_cast<GeometryLine&>(*m_geometry).setStartPoint(m_i->getPosition());
    dynamic_cast<GeometryLine&>(*m_geometry).setEndPoint(m_j->getPosition());
}
