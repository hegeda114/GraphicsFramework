//
// Created by hegeda on 2021-10-03.
//

#ifndef GRAPHICSFRAMEWORK_VECTOR_H
#define GRAPHICSFRAMEWORK_VECTOR_H


#include "HelperGeometry.h"

class Vector : public HelperGeometry {
private:
    vec2 startPoint;
    vec2 endPoint;
    double lineWidth = 2;
public:
    Vector(vec2 start, vec2 end);
    void setStartPoint(vec2 start);
    void setEndPoint(vec2 end);
    void setLineWidth(double width);
    void create() override;
    void draw() override;

};


#endif //GRAPHICSFRAMEWORK_VECTOR_H
