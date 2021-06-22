//
// Created by hegeda on 2021-02-10.
//

#ifndef CHERNO01_CIRCLE_H
#define CHERNO01_CIRCLE_H


#include <glew.h>
#include "glm.hpp"
#include "Geometry.h"
using namespace glm;

class Circle : public Geometry {
    vec2 c;
    int r;
    vec4 color = {0.8, 0.8, 0.8, 1};

public:
    Circle(vec2 center, int radius, vec4 color);
    void create();
    void Draw() override;
    void Grab(float toX, float toY) override;
    bool isInside(float x, float y) const override;
    void toString() const;
};

#endif //CHERNO01_CIRCLE_H
