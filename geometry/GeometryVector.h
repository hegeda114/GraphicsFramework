//
// Created by hegeda on 2021-10-16.
//

#ifndef GRAPHICSFRAMEWORK_GEOMETRYVECTOR_H
#define GRAPHICSFRAMEWORK_GEOMETRYVECTOR_H

#include "glm.hpp"
#include "Geometry.h"

class GeometryVector : public Geometry {
private:
    glm::vec2 m_startPoint;
    glm::vec2 m_endPoint;
    GLfloat m_lineWidth = 2;
public:
    GeometryVector(const glm::vec2& start, const glm::vec2& end);

    void create() override;
    void draw() const override;

    void setStartPoint(const glm::vec2& start);
    void setEndPoint(const glm::vec2& end);
    void setLineWidth(float width);
};


#endif //GRAPHICSFRAMEWORK_GEOMETRYVECTOR_H
