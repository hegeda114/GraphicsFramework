//
// Created by hegeda on 2021-10-13.
//

#include "Spring.h"
#include "../geometry/GeometryLine.h"

Spring::Spring(const std::shared_ptr<Point>& i, const std::shared_ptr<Point>& j, double stretching, double dampingCoeff, double defaultLength) :
   Object(std::make_unique<GeometryLine>(i->getPosition(), j->getPosition()),
   std::make_unique<PhysicalProperties>(glm::vec2(0, 0))), m_i(i), m_j(j) {
    m_ks = stretching;
    m_kd = dampingCoeff;
    m_l0 = defaultLength;
    m_l = defaultLength;
}

bool Spring::isInside(double x, double y) const {
    return false;
}

void Spring::connectionChangedEvent() {
    dynamic_cast<GeometryLine&>(*m_geometry).setStartPoint(m_i->getPosition());
    dynamic_cast<GeometryLine&>(*m_geometry).setEndPoint(m_j->getPosition());
}

glm::vec2 Spring::getExertedForce(const Geometry *targetObject) const {
    glm::vec2 force = {0, 0}; // TODO javítani!
    return force;
}
