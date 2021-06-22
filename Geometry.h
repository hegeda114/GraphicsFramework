//
// Created by hegeda on 2021-02-10.
//

#ifndef CHERNO01_GEOMETRY_H
#define CHERNO01_GEOMETRY_H

#include <glew.h>

class Geometry {
protected:
    unsigned int vao{}, vbo{};
public:
    Geometry() {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
    }
    virtual void Draw() = 0;
    virtual void create() = 0;
    virtual bool isInside(float x, float y) const = 0;
    virtual void Grab(float toX, float toY) = 0;

    virtual bool isMovable() const { return false; }
    virtual void toString() const = 0;

    ~Geometry() {
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }
};

#endif //CHERNO01_GEOMETRY_H
