//
// Created by hegeda on 2021-10-16.
//

#ifndef GRAPHICSFRAMEWORK_GEOMETRYVECTOR_H
#define GRAPHICSFRAMEWORK_GEOMETRYVECTOR_H

#include "glm.hpp"
#include "Geometry.h"

class GeometryVector : public Geometry {
private:
    glm::vec2 startPoint;
    glm::vec2 endPoint;
    double lineWidth = 2;
public:
    GeometryVector(glm::vec2 start, glm::vec2 end);

    void create() override;
    void draw() override;

    void setStartPoint(glm::vec2 start);
    void setEndPoint(glm::vec2 end);
    void setLineWidth(double width);
};


#endif //GRAPHICSFRAMEWORK_GEOMETRYVECTOR_H
