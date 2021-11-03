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
    float m_lengthMultiplier = 0.05;
    bool m_visibility = false;
public:
    GeometryVector(const glm::vec2& start, const glm::vec2& end);

    void create() const override;
    void draw() const override;

    void renderHelper(const Shader* shader) const;

    void calculateVector(const glm::vec2& pivot, const glm::vec2& referenceVector);

    void setLengthMultiplier(float multiplier);
    float getLengthMultiplier() const;

    void setVisibility(bool isVisible);
    bool getVisibility() const;

    void setLineWidth(float width);
};


#endif //GRAPHICSFRAMEWORK_GEOMETRYVECTOR_H
