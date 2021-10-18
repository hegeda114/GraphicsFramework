//
// Created by hegeda on 2021-10-16.
//

#ifndef GRAPHICSFRAMEWORK_GEOMETRYLINE_H
#define GRAPHICSFRAMEWORK_GEOMETRYLINE_H

#include "glm.hpp"
#include "Geometry.h"

class GeometryLine : public Geometry {
private:
    glm::vec2 startPoint;
    glm::vec2 endPoint;
    double lineWidth = 2;
public:
    GeometryLine(glm::vec2 start, glm::vec2 end);

    void create() override;
    void draw() override;

    void setStartPoint(glm::vec2 start);
    void setEndPoint(glm::vec2 end);
    void setLineWidth(double width);
};


#endif //GRAPHICSFRAMEWORK_GEOMETRYLINE_H
