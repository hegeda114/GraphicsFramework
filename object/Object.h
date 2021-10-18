//
// Created by hegeda on 2021-10-12.
//

#ifndef GRAPHICSFRAMEWORK_OBJECT_H
#define GRAPHICSFRAMEWORK_OBJECT_H

#include <iostream>
#include <memory>
#include "glm.hpp"
#include "../geometry/Geometry.h"
#include "../physicalProperties/PhysicalProperties.h"
#include "../geometry/GeometryVector.h"

class Object {
private:
    /**
     * Stores the currently last object id.
     */
    static size_t lastId;

    /**
     * Returns the next free object id based on lastId.
     * @return The next free object id.
     */
    static size_t nextId();
protected:
    /**
     * The pivot point of the object.
     */
    glm::vec2 m_pivot = {0, 0};

    /**
     * The geometry of the object.
     */
    std::unique_ptr<Geometry> m_geometry;

    /**
     * The physical properties of the object.
     */
    std::unique_ptr<PhysicalProperties> m_physicalProperties;

    std::vector<std::shared_ptr<Object>> m_connections;

    /**
     * If true, the object could temporarily behave like a static object.
     */
    bool m_fix = false;

    /**
     * If true, the simulate function of the object does nothing.
     * Otherwise the object could move during the simulation.
     */
    bool m_static = false;

    /**
     * The name of the object.
     */
    std::string m_name;

    /**
     * The id of the object.
     */
    size_t m_id;

    GeometryVector m_velocityVector;
    GeometryVector m_forceVector;

    bool m_showVelocity = false;
    bool m_showForces = false;

public:
    Object(std::unique_ptr<Geometry> geometry, std::unique_ptr<PhysicalProperties> physicalProperties);

    /**
     * Returns a reference to the geometry of the object.
     * @return Reference to the geometry of the object.
     */
    const std::unique_ptr<Geometry>& getGeometry() const;

    /**
     * Returns a reference to the physical properties of the object.
     * @return Reference to the physical properties of the object.
     */
    const std::unique_ptr<PhysicalProperties>& getPhysicalProperties() const;

    /**
     * Returns true if the given position is inside of the object, otherwise false.
     * @param x The x coordinate of the tested position.
     * @param y The y coordinate of the tested position.
     * @return True if the position is inside of the object, otherwise false.
     */
    virtual bool isInside(double x, double y) const = 0;

    /**
     * Returns true if the given position is inside of the object, otherwise false.
     * @param position The tested position.
     * @return True if the position is inside of the object, otherwise false.
     */
    bool isInside(const glm::vec2& position) const;

    /**
     * Returns true if the object is static or false if the object is dynamic.
     * @return True if the object is static or true if the object is dynamic.
     */
    bool isStatic() const;

    /**
     * Makes the object static or dynamic.
     * @param isStatic True if static of false if dynamic.
     */
    void setStatic(bool isStatic);

    /**
     * Returns true if the object is fixed or false if the object is not fixed.
     * @return True if the object is fixed or true if the object is not fixed.
     */
    bool isFix() const;

    /**
     * Makes the object fixed or not fixed.
     * @param isFix True if fixed or false if not fixed.
     */
    void setFix(bool isFix);

    /**
     * Returns the name of the object.
     * @return The name of the object.
     */
    std::string getName() const;

    /**
     * Sets the name of the object.
     * @param newName The new name of the object.
     */
    void setName(const std::string& newName);

    /**
     * Returns the id of the object.
     * @return The id of the object.
     */
    size_t getId() const;

    /**
     * Modify the object position to the target position.
     * @param toX The x coordinate of the target position.
     * @param toY The y coordinate of the target position.
     */
    void move(double toX, double toY);

    /**
     * Modify the object position to the target position.
     * @param targetPosition The coordinate of the target position.
     */
    void move(const glm::vec2& targetPosition);

    /**
     * Simulates the object with the given simulation state.
     * @param simState The simulation state for the simulation.
     */
    void simulate(SimulationState simState);

    /**
     * Sets up and renders the helper geometries.
     */
    void showHelpers();

    glm::vec2 getPosition() const;

    void setShowVelocity(bool showVelocity);
    void setShowForces(bool showForces);

    void createAndDraw();

    virtual void connectionChangedEvent() {};

    void addConnection(std::shared_ptr<Object> object);

    virtual glm::vec2 getExertedForce(const Geometry* targetObject) const {};

};


#endif //GRAPHICSFRAMEWORK_OBJECT_H
