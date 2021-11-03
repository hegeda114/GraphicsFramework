//
// Created by hegeda on 2021-11-01.
//

#ifndef GRAPHICSFRAMEWORK_GEOMETRYSPRING_H
#define GRAPHICSFRAMEWORK_GEOMETRYSPRING_H

#include "glm.hpp"
#include "Geometry.h"

class GeometrySpring : public Geometry {
private:
    glm::vec2 m_startPoint;
    glm::vec2 m_endPoint;
    GLfloat m_lineWidth = 2;
    static const size_t m_count = 30;
public:
    GeometrySpring(const glm::vec2& start, const glm::vec2& end);

    void create() const override;
    void draw() const override;

    void setStartPoint(const glm::vec2& start);
    void setEndPoint(const glm::vec2& end);
    void setLineWidth(float width);
};


#endif //GRAPHICSFRAMEWORK_GEOMETRYSPRING_H
