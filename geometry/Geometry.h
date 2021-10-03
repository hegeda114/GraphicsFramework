//
// Created by hegeda on 2021-02-10.
//

#ifndef CHERNO01_GEOMETRY_H
#define CHERNO01_GEOMETRY_H

#include <glew.h>
#include <vector>
#include "glm.hpp"
#include "../SimulationMode.h"
#include "../SimulationState.h"
#include "../Shaders.h"
using namespace glm;

class Geometry {
protected:
    unsigned int vao{}, vbo{};
    bool fix = false;

    float color[4] = {1.0, 0.0, 1.0, 1.0};

    virtual void explicitEuler(SimulationState simState) = 0;
public:
    Geometry() {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
    }
    virtual void create() = 0;
    virtual void draw() = 0;

    virtual bool isInside(double x, double y) const = 0;

    bool isFix() const;
    void setFix(bool isFix);
    virtual void move(double toX, double toY) = 0;

    void simulate(SimulationState simState);

    void setColor(double red, double green, double blue, double alpha);

    ~Geometry() {
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }
};

#endif //CHERNO01_GEOMETRY_H
