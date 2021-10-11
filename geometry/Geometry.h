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
private:
    static size_t current_id;
    static size_t getNextId();
protected:
    unsigned int vao{}, vbo{};
    bool fix = false;
    bool is_static = false;
    size_t id;
    std::string name;
    vec2 vel = {0.0, 0.0};

    glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f};
    glm::vec4 defaultColor = {1.0f, 1.0f, 1.0f, 1.0f};

    virtual void explicitEuler(SimulationState simState) = 0;
public:
    Geometry() {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        id = getNextId();
    }
    virtual void create() = 0;
    virtual void draw() = 0;

    virtual bool isInside(double x, double y) const = 0;

    bool isStatic() const;
    void setStatic(bool isStatic);
    bool isFix() const;
    void setFix(bool isFix);
    virtual void move(double toX, double toY) = 0;

    void setVel(double x, double y);

    void simulate(SimulationState simState);
    virtual void showHelpers() {};

    void setColor(double red, double green, double blue, double alpha);
    void setColorToDefault();
    std::string getName() const;
    size_t getId() const;

    ~Geometry() {
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }
};

#endif //CHERNO01_GEOMETRY_H
