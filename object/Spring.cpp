//
// Created by hegeda on 2021-10-13.
//

#include "Spring.h"
#include "../geometry/GeometryLine.h"

Spring::Spring(const std::shared_ptr<Point>& i, const std::shared_ptr<Point>& j, float stretching, float dampingCoeff, float defaultLength) :
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
    glm::vec2 posdiff, veldiff;
    if(dynamic_cast<const Point*>(targetObject) == m_i.get()) {
        posdiff = (m_j->getPosition() - m_i->getPosition());
        veldiff = (m_j->getVelocity() - m_i->getVelocity());
    } else {
        posdiff = (m_i->getPosition() - m_j->getPosition());
        veldiff = (m_i->getVelocity() - m_j->getVelocity());
    }
    float lenposdiff = glm::length(posdiff);
    return (posdiff / lenposdiff) * m_ks * (lenposdiff - m_l0);
}
