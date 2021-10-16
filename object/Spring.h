//
// Created by hegeda on 2021-10-13.
//

#ifndef GRAPHICSFRAMEWORK_SPRING_H
#define GRAPHICSFRAMEWORK_SPRING_H


#include "Object.h"
#include "Point.h"

class Spring : public Object {
private:
    double m_ks; // stretching
    double m_kd; // damping coefficients
    double m_l0; // default length
    double m_l;
public:
//    Spring(std::unique_ptr<Geometry> geometry, std::unique_ptr<PhysicalProperties> physicalProperties, Point i,
//           Point j, double stretching, double dampingCoeff, double defaultLength);
};


#endif //GRAPHICSFRAMEWORK_SPRING_H
