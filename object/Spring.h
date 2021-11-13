//
// Created by hegeda on 2021-10-13.
//

#ifndef GRAPHICSFRAMEWORK_SPRING_H
#define GRAPHICSFRAMEWORK_SPRING_H


#include "Object.h"
#include "Point.h"

/**
 * Represents a spring, it has two points and a stretching, damping coefficients and default length parameters.
 */
class Spring : public Object {
private:
    // Stores the currently last spring id.
    static int lastSpringId;

    /**
     * Returns the next free spring id based on lastId.
     * @return The next free spring id.
     */
    static int nextSpringId();
private:
    float m_ks; // stretching
    float m_kd; // damping coefficients
    float m_l0; // default length
    float m_l; // current length
    std::shared_ptr<Point> m_i;
    std::shared_ptr<Point> m_j;

    glm::vec2 calcForce(glm::vec2 posDiff, glm::vec2 velDiff) const;
    static glm::vec2 orthoProjection(glm::vec2 a, glm::vec2 b);
    bool isInside(double x, double y) const override { return false; };
public:
    /**
     * Constructor, creates the spring with the given parameters.
     * @param m_i The start Point.
     * @param m_j The end Point.
     * @param stretching The stretching as float.
     * @param dampingCoefficient The damping coefficient as float.
     * @param defaultLength The default length as float.
     */
    Spring(const std::shared_ptr<Point>& i, const std::shared_ptr<Point>& j, float stretching, float dampingCoefficient, float defaultLength);
    Spring(const std::shared_ptr<Point>& i, const std::shared_ptr<Point>& j, float stretching, float dampingCoefficient);

    Spring();

    Spring(const Spring& spring);

    glm::vec2 calculateSpringForce(const glm::vec2& firstPos, const glm::vec2& secondPos, const glm::vec2& firstVel, const glm::vec2& secondVel);

    /**
     * Refreshes the start and end position of the spring, based on the spring's points position.
     */
    void connectionChangedEvent() const override;

    ObjectType getType() const override;

    std::string getSerializedData() const override;

    std::shared_ptr<Point> getI() const;
    std::shared_ptr<Point> getJ() const;

    static std::shared_ptr<Spring> createSpringFromSavedData(const std::shared_ptr<Point>& i, const std::shared_ptr<Point>& j, const std::string& serializedData);

    float getStretching() const;
    float getDampingCoefficient() const;
    float getDefaultLength() const;
    void setStretching(float stretching);
    void setDampingCoefficient(float dampingCoefficient);
    void setDefaultLength(float defaultLength);

    float getCurrentLength() const;
};


#endif //GRAPHICSFRAMEWORK_SPRING_H
