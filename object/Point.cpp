//
// Created by hegeda on 2021-10-12.
//

#include "Point.h"
#include "../geometry/GeometryPoint.h"
#include <fstream>
#include <chrono>
#include <sstream>

int Point::lastPointId = 1;

int Point::nextPointId() {
    return lastPointId++;
}

Point::Point(glm::vec2 pivotPoint, double radius) :
    Object(std::make_unique<GeometryPoint>(pivotPoint, radius),
            std::make_unique<SimulationProperties>(pivotPoint)) {
    m_name = std::string("Point_") + std::to_string(nextPointId());
    m_pivot = pivotPoint;
    m_radius = radius;
}

bool Point::isInside(double x, double y) const {
    if(std::abs(x - m_pivot.x) < m_radius && std::abs(y - m_pivot.y) < m_radius) {
        return true;
    }
    return false;
}

ObjectType Point::getType() const {
    return ObjectType::PointObject;
}

std::string Point::getSerializedData() const {
    char buffer [200];
    std::string is_static = "true";
    if(!m_static) is_static = "false";
    sprintf(buffer, "%f;%f;%f;%s;%s", m_pivot.x, m_pivot.y, m_radius, m_name.c_str(), is_static.c_str());
    return buffer;
}

std::shared_ptr<Point> Point::createPointFromSavedData(const std::string& serializedData) {
    std::stringstream ss(serializedData);
    std::string val, val1, val2;

    getline(ss, val1, ';');
    getline(ss, val2, ';');
    glm::vec2 pivot(std::stof(val1), std::stof(val2));

    getline(ss, val, ';');
    double radius = std::stod(val);

    getline(ss, val, ';');
    std::string name = val;

    getline(ss, val, ';');
    bool isStatic = (val == "true");

    std::shared_ptr<Point> point = std::make_shared<Point>(pivot, radius);
    point->setName(name);
    point->setStatic(isStatic);
    return point;
}