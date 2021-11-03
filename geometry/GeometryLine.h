//
// Created by hegeda on 2021-10-16.
//

#ifndef GRAPHICSFRAMEWORK_GEOMETRYLINE_H
#define GRAPHICSFRAMEWORK_GEOMETRYLINE_H

#include "glm.hpp"
#include "Geometry.h"

class GeometryLine : public Geometry {
private:
    glm::vec2 m_startPoint;
    glm::vec2 m_endPoint;
    GLfloat m_lineWidth = 2;
public:
    GeometryLine(const glm::vec2& start, const glm::vec2& end);

    void create() const override;
    void draw() const override;

    void setStartPoint(const glm::vec2& start);
    void setEndPoint(const glm::vec2& end);
    void setLineWidth(float width);

    glm::vec2 getStartPoint() const;
    glm::vec2 getEndoint() const;
};


#endif //GRAPHICSFRAMEWORK_GEOMETRYLINE_H
