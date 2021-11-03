//
// Created by hegeda on 2021-02-10.
//

#ifndef CHERNO01_GEOMETRY_H
#define CHERNO01_GEOMETRY_H

#include <glew.h>
#include <vector>
#include <memory>
#include "glm.hpp"
#include "../simulation/GlobalSimulationSettings.h"
#include "../Shader.h"

class Geometry {
protected:
    /**
     * The vertex array object id of the geometry.
     */
    unsigned int vao{};

    /**
     * The vertex buffer object id of the geometry.
     */
    unsigned int vbo{};

    /**
     * The current color of the object.
     */
    glm::vec4 m_color = {1.0f, 1.0f, 1.0f, 1.0f};

    /**
     * The default color of the object. This value should be object specific.
     */
    glm::vec4 m_defaultColor = {1.0f, 1.0f, 1.0f, 1.0f};

    glm::vec2 m_position = {0, 0};

public:
    Geometry() {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
    }
    virtual void update(const Shader* shader) const;
    virtual void create() const = 0;
    virtual void draw() const = 0;

    void setPosition(const glm::vec2& position);

    void setColor(double red, double green, double blue, double alpha);
    void setDefaultColor(double red, double green, double blue, double alpha);
    void setColorToDefault();

    virtual ~Geometry() {
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }
};

#endif //CHERNO01_GEOMETRY_H
