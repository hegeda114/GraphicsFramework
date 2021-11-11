//
// Created by hegeda on 2021-10-12.
//

#ifndef GRAPHICSFRAMEWORK_OBJECT_H
#define GRAPHICSFRAMEWORK_OBJECT_H

#include <iostream>
#include <memory>
#include "glm.hpp"
#include "../geometry/Geometry.h"
#include "../simulation/SimulationProperties.h"
#include "../geometry/GeometryVector.h"

enum ObjectType { PointObject, SpringObject};

class Object {
private:
    // Stores the currently last object id.
    static int lastId;

    /**
     * Returns the next free object id based on lastId.
     * @return The next free object id.
     */
    static int nextId();
protected:
    // The pivot point of the object.
    glm::vec2 m_pivot = {0, 0};

    // The geometry of the object.
    std::unique_ptr<Geometry> m_geometry;

    // The simulation properties of the object.
    std::unique_ptr<SimulationProperties> m_simulationProperties;

    // List of the connected objects, for example springs.
    std::vector<std::shared_ptr<Object>> m_connections;

    // If true, the object could temporarily behave like a static object.
    bool m_fix = false;

    // If true, the simulate function of the object does nothing.
    // Otherwise, the object could move during the simulation.
    bool m_static = false;

    // The name of the object.
    std::string m_name;

    // The id of the object.
    int m_id;

    // The velocity vector object of the current object.
    std::unique_ptr<GeometryVector> m_velocityVector;

    // The force vector object of the current object.
    std::unique_ptr<GeometryVector> m_forceVector;

public:
    /**
     * Constructor, creates an object with the given geometry and simulation properties.
     * @param geometry The geometry of the object.
     * @param simulationProperties The simulation properties of the object.
     */
    Object(std::unique_ptr<Geometry> geometry, std::unique_ptr<SimulationProperties> simulationProperties);

    /**
     * Returns a reference to the geometry of the object.
     * @return Reference to the geometry of the object.
     */
    const std::unique_ptr<Geometry>& getGeometry() const;

    /**
     * Returns a reference to the simulation properties of the object.
     * @return Reference to the simulation properties of the object.
     */
    const std::unique_ptr<SimulationProperties>& getSimProp() const;

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
    bool setName(const std::string& newName);

    /**
     * Returns the id of the object.
     * @return The id of the object.
     */
    int getId() const;

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
    void simulate(const GlobalSimulationSettings* globalSimulationSettings);

    /**
     * Sets up and renders the helper geometries.
     */
    void renderHelpers(const Shader* shader);

    /**
     * Creates and draws the geometry of the object.
     */
    void render(const Shader* shader) const;

    /**
     * Default implementation is empty.
     * This function is useful, when an object depends on some other object's position. It will be called for all connections of an object, is the object moves.
     */
    virtual void connectionChangedEvent() const {};

    /**
     * Adds the object to the list of connected objects.
     * @param object
     */
    void addConnection(const std::shared_ptr<Object>& object);

    virtual ObjectType getType() const = 0;

    void setPosition(const glm::vec2& position);

    virtual std::string getSerializedData() const = 0;

    const std::unique_ptr<GeometryVector>& getVelocityHelper() const;

    const std::unique_ptr<GeometryVector>& getForceHelper() const;

    virtual ~Object() = default;
};


#endif //GRAPHICSFRAMEWORK_OBJECT_H
