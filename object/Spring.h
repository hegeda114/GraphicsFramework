//
// Created by hegeda on 2021-10-13.
//

#ifndef GRAPHICSFRAMEWORK_SPRING_H
#define GRAPHICSFRAMEWORK_SPRING_H


#include "Object.h"
#include "Point.h"

class Spring : public Object {
private:
    float m_ks; // stretching
    float m_kd; // damping coefficients
    float m_l0; // default length
    float m_l;
    std::shared_ptr<Point> m_i;
    std::shared_ptr<Point> m_j;
public:
    Spring(const std::shared_ptr<Point>& m_i, const std::shared_ptr<Point>& m_j, float stretching, float dampingCoeff, float defaultLength);

    bool isInside(double x, double y) const override;

    void connectionChangedEvent() override;

    glm::vec2 getExertedForce(const Geometry *targetObject) const override;
};


#endif //GRAPHICSFRAMEWORK_SPRING_H
