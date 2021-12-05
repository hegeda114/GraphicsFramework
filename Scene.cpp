//
// Created by hegeda on 2021-09-29.
//

#include <memory>
#include <imgui.h>
#include "Scene.h"
#include <cmath>
#include "Eigen"

using namespace std::chrono;

void Scene::init() {
    // Init simulation state
    m_globalSimulationSettings = std::make_unique<GlobalSimulationSettings>(SimulationMode::ExplicitEuler, 1.0/60.0);
    m_globalSimulationSettings->setBorders(1.0, 1.0, -1.0, -1.0);

    m_shader = std::make_unique<Shader>();
    m_shader->createShader();

    m_camera = std::make_unique<OrthogonalCamera>();

    m_frameBuffer = std::make_unique<FrameBuffer>();
    m_frameBuffer->createBuffer(800, 800);

    initStartScene();
}

void Scene::initStartScene() {
    m_points.clear();
    m_springs.clear();
    m_objects.clear();
    m_activeObjectId = -1;

    grid.clear();

    int start_scene = 3;
    bool fist_row_static = false;

    if(start_scene == 0) {
        auto point1 = this->addPoint(glm::vec2(0.0, 0.0));
        point1->setStatic(true);
        auto point2 = this->addPoint({0.0, -0.2});
        this->addSpring(point1, point2, 10, 0);
        auto point3 = this->addPoint({0.0, -0.4});
        this->addSpring(point2, point3, 10, 0);
//        point2->move(glm::vec2(0.0, 0.8));
    }

    if(start_scene == 1) {
        auto point1 = this->addPoint(glm::vec2(-0.2, 0));
        point1->setStatic(true);
        auto point2 = this->addPoint({0.0, 0.0});
        this->addSpring(point1, point2, 100, 0);
//      point2->getSimProp()->setVelocity(0.01, 0.0);
        point2->move({0.1999, 0.0});
    }

    if(start_scene == 2) {
        int maxNum = 4;
        float length = 0.2;

        std::vector<std::shared_ptr<Point>> springs;
        std::shared_ptr<Point> prevCol;
        for (int i = 0; i < maxNum; i++) {
            for (int j = 0; j < maxNum; j++) {
                auto point = this->addPoint(glm::vec2(length * i, length * j));
                springs.push_back(point);
                if (i == 0) {
                    point->setStatic(true);
                }
                if (j == 0) {
                    prevCol = point;
                }
                if (j > 0) {
                    this->addSpring(prevCol, point, 1000, 3);
                    prevCol = point;
                }
                if (i > 0) {
                    int own_idx = i * maxNum + j;
                    this->addSpring(springs[own_idx - maxNum], point, 1000, 3);
                }
                if (i * 3 + j >= maxNum - 1 && j < maxNum - 1 && i < maxNum) {
                    int own_idx = i * maxNum + j;
                    this->addSpring(springs[own_idx - maxNum + 1], point, 1000, 3);
                }
                //if(i*3+j > maxNum-1 && j < maxNum-1 && i < maxNum) {
                //    int own_idx = i*maxNum+j;
                //    this->addSpring(springs[own_idx-maxNum+1], point, 10, 0, std::sqrt(length*length));
                //}
            }
            //prevRow.clear();
        }
    }

    if(start_scene == 3) {
        float stiffness = 100;
        float damping = 10;

        count_i = 10;
        count_j = 10;
//        float length = 0.06f;
        float length = 0.08f;
        float offset = (count_i / 2.0f - 1) * length;
        glm::vec2 global_offset = glm::vec2(0.0, 0.0);

        for(int i = 0; i < count_i; i++) {
            std::vector<std::shared_ptr<Point>> column;
            for(int j = 0; j < count_j; j++) {
                auto point = this->addPoint(glm::vec2(i * length - offset, j * length - offset));
                column.push_back(point);
            }
            grid.push_back(column);
            column.clear();
        }
        if(fist_row_static) {
            for(const auto& point : grid[0]) {
                point->setStatic(true);
            }
        }
        for(int i = 1; i < count_i; i++) {
            for(int j = 0; j < count_j; j++) {
                addSpring(grid[i][j], grid[i-1][j], stiffness, damping);

                if(j < count_j - 1) {
                    addSpring(grid[i][j], grid[i-1][j+1], stiffness, damping);
                }
                if(j > 0) {
                    addSpring(grid[i][j], grid[i-1][j-1], stiffness, damping);
                }
            }
        }
        for(int j = 1; j < count_j; j++) {
            for (int i = 0; i < count_i; i++) {
                addSpring(grid[i][j], grid[i][j - 1], stiffness, damping);
            }
        }

        bool fix_left_side = false;
        bool fix_right_side = false;
        bool fix_corners = true;
        bool fix_right_top_corner = false;

        if(fix_left_side) {
            for(const auto& point : grid[0]) {
                point->setStatic(true);
            }
        }

        if(fix_right_side) {
            for (const auto &point: grid[count_i - 1]) {
                point->setStatic(true);
            }
        }
        if(fix_right_top_corner) {
            grid[count_i-1][count_j-1]->setStatic(true);
        }
        if(fix_corners) {
            grid[0][0]->setStatic(true);
            grid[0][count_j-1]->setStatic(true);
            grid[count_i-1][0]->setStatic(true);
            grid[count_i-1][count_j-1]->setStatic(true);
        }

        for(const auto& g : grid) {
            for(const auto& p : g) {
                auto pos = p->getSimProp()->getPosition();
                p->move(pos + global_offset);
            }
        }

        initShapeMatching();


//        for(const auto& point : grid[count_i-1]) {
//            auto pos = point->getSimProp()->getPosition();
//            point->move(pos + glm::vec2(0, -0.3));
//        }
//        grid[count_i-1][0]->move(0.5, -0.5);
    }

    if(start_scene == 4) {
        int number = 8;
        float radius = 0.2f;
        float stiffness = 100;
        float damping = 0;
        std::vector<std::shared_ptr<Point>> circle;

        for(float i = 0; i < 2.0f * M_PI; i+= (2.0f * M_PI) / (float) number) {
            auto point = addPoint(glm::vec2(sin(i) * radius, cos(i) * radius));
            circle.push_back(point);
        }
        for(size_t i = 0; i < circle.size() - 1; i++) {
            for(size_t j = i+1; j < circle.size(); j++) {
                if(circle[i] != circle[j]) {
                    addSpring(circle[i], circle[j], stiffness, damping);
                }
            }
        }
        for(const auto& point : circle) {
            point->move(point->getSimProp()->getPosition() * 0.8f);
        }

    }

    if(start_scene == 5) {
        float stiffness = 100;
        float damping = 0.3;

        count_i = 5;
        count_j = 5;
        float length = 0.2f;
        float offset = (count_i / 2.0f - 1) * length;

        for(int i = 0; i < count_i; i++) {
            std::vector<std::shared_ptr<Point>> column;
            for(int j = 0; j < count_j; j++) {
                auto point = this->addPoint(glm::vec2(i * length - offset, j * length - offset));
                column.push_back(point);
            }
            grid.push_back(column);
            column.clear();
        }

        for(const auto& point : grid[0]) {
            point->setStatic(true);
        }
        for(const auto& point : grid[count_i-1]) {
            point->setStatic(true);
        }
        for(int i = 1; i < count_i; i++) {
            for(int j = 0; j < count_j; j++) {
                addSpring(grid[i][j], grid[i-1][j], stiffness, damping);

                if(j < count_j - 1) {
                    addSpring(grid[i][j], grid[i-1][j+1], stiffness, damping);
                }
                if(j > 0) {
                    addSpring(grid[i][j], grid[i-1][j-1], stiffness, damping);
                }
            }
        }
        for(int j = 1; j < count_j; j++) {
            for (int i = 0; i < count_i; i++) {
                addSpring(grid[i][j], grid[i][j - 1], stiffness, damping);
            }
        }
        //resetShapeMatchingInit();
        initShapeMatching();
        for(const auto& point : grid[count_i-1]) {
            auto oldPos = point->getSimProp()->getPosition();
            point->move(oldPos - glm::vec2(0.4, 0));
        }
//        grid[count_i-1][0]->move(0.6, -0.4);
    }
}

void Scene::simulate() {
//    if(!m_shapeMatchingInitialized) {
//        initShapeMatching();
//        m_shapeMatchingInitialized = true;
//    }

//    for(const auto& point : grid[count_i-1]) {
//        auto pos = point->getSimProp()->getPosition();
//        if(pos.x < 0.7) {
//            point->move(pos + glm::vec2(0.005, 0));
//        }
//    }

    if(m_activeObjectId != -1 && false) {
        auto active = getActiveObject();
        auto pos = active->getSimProp()->getPosition();
        if(pos.x > 0.7) {
            value = -0.005;
        }
        if(pos.x < 0.3) {
            value = 0.005;
        }
        active->move(active->getSimProp()->getPosition() + glm::vec2(value, 0));
    }

    auto start = high_resolution_clock::now();
    double frame_rate = 1.0/60.0;
    int iteration = ceil(frame_rate / m_globalSimulationSettings->getTimestep());
    for(int i = 0; i < iteration; i++) {
        if(m_globalSimulationSettings->getSimApproach() == SimulationApproach::MassSpringSystem) {
            switch (m_globalSimulationSettings->getSimMode()) {
                case ExplicitEuler: eulerIntegration();
                    break;
                case RungeKuttaSecondOrder: rungeKuttaSecondOrderIntegration();
                    break;
                case RungeKuttaFourthOrder: rungeKuttaFourthOrderIntegration();
                    break;
                case SemiImplicitEuler: eulerIntegration();
                    break;
            }
        }
        if(m_globalSimulationSettings->getSimApproach() == SimulationApproach::PositionBasedDynamics) {
            switch (m_globalSimulationSettings->getPBDConstraint()) {
                case Stretching: positionBasedDynamicsStretching();
                    break;
            }
        }
        if(m_globalSimulationSettings->getSimApproach() == SimulationApproach::ShapeMatching) {
            shapeMatching();
        }
    }
    auto stop = high_resolution_clock::now();
    m_simTime = duration_cast<microseconds>(stop - start).count();
    printf("iter num: %d\t time: %lld\n", iteration, m_simTime);
}

void Scene::eulerIntegration() {
    // calculate spring forces for each springs
    for(const auto& spring : m_springs) {
        auto point_i = spring->getI();
        auto point_j = spring->getJ();
        auto force_i = spring->calculateSpringForce(
                point_i->getSimProp()->getPosition(), point_j->getSimProp()->getPosition(),
                point_i->getSimProp()->getVelocity(), point_j->getSimProp()->getVelocity());
        auto force_j = spring->calculateSpringForce(
                point_j->getSimProp()->getPosition(), point_i->getSimProp()->getPosition(),
                point_j->getSimProp()->getVelocity(), point_i->getSimProp()->getVelocity());
        point_i->getSimProp()->addForce(force_i);
        point_j->getSimProp()->addForce(force_j);
    }
    // calculate other forces for each points
    for(const auto& point : m_points) {
        if(m_globalSimulationSettings->isGravityEnabled() && !point->isStatic()) {
            point->getSimProp()->addForce(m_globalSimulationSettings->getGravity()); // add gravity
        }
    }
    //calculate new position and velocity
    for(const auto& point : m_points) {
        point->simulate(m_globalSimulationSettings.get());
    }
}

void Scene::rungeKuttaSecondOrderIntegration() {
    float timestep = m_globalSimulationSettings->getTimestep();

    // calc A
    for(const auto& point : m_points) {
        glm::vec2 v = point->getSimProp()->getVelocity();
        glm::vec2 fg = glm::vec2(0, 0);
        if(m_globalSimulationSettings->isGravityEnabled() && !point->isStatic()) {
            fg = m_globalSimulationSettings->getGravity(); // add gravity
        }
        point->getSimProp()->addToA(v, fg);
    }
    for(const auto& spring : m_springs) {
        auto point_i = spring->getI();
        auto point_j = spring->getJ();
        auto force_i = spring->calculateSpringForce(
                point_i->getSimProp()->getPosition(), point_j->getSimProp()->getPosition(),
                point_i->getSimProp()->getVelocity(), point_j->getSimProp()->getVelocity());
        auto force_j = spring->calculateSpringForce(
                point_j->getSimProp()->getPosition(), point_i->getSimProp()->getPosition(),
                point_j->getSimProp()->getVelocity(), point_i->getSimProp()->getVelocity());
        point_i->getSimProp()->addToA(glm::vec2(0, 0), force_i);
        point_j->getSimProp()->addToA(glm::vec2(0, 0), force_j);
    }
    for(const auto& point : m_points) {
        point->getSimProp()->multiplyA(1, point->getSimProp()->getInvMass());
    }

    // calc B
    for(const auto& point : m_points) {
        glm::vec2 v = point->getSimProp()->getVelocity() + (timestep / 2.0f) * point->getSimProp()->getA().second;
        glm::vec2 fg = glm::vec2(0, 0);
        if(m_globalSimulationSettings->isGravityEnabled() && !point->isStatic()) {
            fg = m_globalSimulationSettings->getGravity(); // add gravity
        }
        point->getSimProp()->addToB(v, fg);
    }
    for(const auto& spring : m_springs) {
        auto point_i = spring->getI();
        auto point_j = spring->getJ();
        glm::vec2 pos_i = point_i->getSimProp()->getPosition() + (timestep / 2.0f) * point_i->getSimProp()->getA().first;
        glm::vec2 pos_j = point_j->getSimProp()->getPosition() + (timestep / 2.0f) * point_j->getSimProp()->getA().first;
        glm::vec2 vel_i = point_i->getSimProp()->getVelocity() + (timestep / 2.0f) * point_i->getSimProp()->getA().second;
        glm::vec2 vel_j = point_j->getSimProp()->getVelocity() + (timestep / 2.0f) * point_j->getSimProp()->getA().second;
        auto force_i = spring->calculateSpringForce(pos_i, pos_j, vel_i, vel_j);
        auto force_j = spring->calculateSpringForce(pos_j, pos_i, vel_j, vel_i);
        point_i->getSimProp()->addToB(glm::vec2(0, 0), force_i);
        point_j->getSimProp()->addToB(glm::vec2(0, 0), force_j);
    }
    for(const auto& point : m_points) {
        point->getSimProp()->multiplyB(1, point->getSimProp()->getInvMass());
    }

    for(const auto& point : m_points) {
        point->simulate(m_globalSimulationSettings.get());
        point->getSimProp()->clearABCD();
    }
}

void Scene::rungeKuttaFourthOrderIntegration() {
    float timestep = m_globalSimulationSettings->getTimestep();
    // calc a
    for(const auto& point : m_points) {
        glm::vec2 v = point->getSimProp()->getVelocity();
        glm::vec2 fg = glm::vec2(0, 0);
        if(m_globalSimulationSettings->isGravityEnabled() && !point->isStatic()) {
            fg = m_globalSimulationSettings->getGravity(); // add gravity
        }
        point->getSimProp()->addToA(v, fg);
    }
    for(const auto& spring : m_springs) {
        auto point_i = spring->getI();
        auto point_j = spring->getJ();
        auto force_i = spring->calculateSpringForce(
                point_i->getSimProp()->getPosition(), point_j->getSimProp()->getPosition(),
                point_i->getSimProp()->getVelocity(), point_j->getSimProp()->getVelocity());
        auto force_j = spring->calculateSpringForce(
                point_j->getSimProp()->getPosition(), point_i->getSimProp()->getPosition(),
                point_j->getSimProp()->getVelocity(), point_i->getSimProp()->getVelocity());
        point_i->getSimProp()->addToA(glm::vec2(0, 0), force_i);
        point_j->getSimProp()->addToA(glm::vec2(0, 0), force_j);
    }
    // calc b
    for(const auto& point : m_points) {
        glm::vec2 v = point->getSimProp()->getVelocity() + (timestep / 2) * point->getSimProp()->getA().second;
        glm::vec2 fg = glm::vec2(0, 0);
        if(m_globalSimulationSettings->isGravityEnabled() && !point->isStatic()) {
            fg = m_globalSimulationSettings->getGravity(); // add gravity
        }
        point->getSimProp()->addToB(v, fg);
    }
    for(const auto& spring : m_springs) {
        auto point_i = spring->getI();
        auto point_j = spring->getJ();
        glm::vec2 pos_i = point_i->getSimProp()->getPosition() + (timestep / 2) * point_i->getSimProp()->getA().first;
        glm::vec2 pos_j = point_j->getSimProp()->getPosition() + (timestep / 2) * point_j->getSimProp()->getA().first;
        glm::vec2 vel_i = point_i->getSimProp()->getVelocity() + (timestep / 2) * point_i->getSimProp()->getA().second;
        glm::vec2 vel_j = point_j->getSimProp()->getVelocity() + (timestep / 2) * point_j->getSimProp()->getA().second;
        auto force_i = spring->calculateSpringForce(pos_i, pos_j, vel_i, vel_j);
        auto force_j = spring->calculateSpringForce(pos_j, pos_i, vel_j, vel_i);
        point_i->getSimProp()->addToB(glm::vec2(0, 0), force_i);
        point_j->getSimProp()->addToB(glm::vec2(0, 0), force_j);
    }
    // calc c
    for(const auto& point : m_points) {
        glm::vec2 v = point->getSimProp()->getVelocity() + (timestep / 2) * point->getSimProp()->getB().second;
        glm::vec2 fg = glm::vec2(0, 0);
        if(m_globalSimulationSettings->isGravityEnabled() && !point->isStatic()) {
            fg = m_globalSimulationSettings->getGravity(); // add gravity
        }
        point->getSimProp()->addToC(v, fg);
    }
    for(const auto& spring : m_springs) {
        auto point_i = spring->getI();
        auto point_j = spring->getJ();
        glm::vec2 pos_i = point_i->getSimProp()->getPosition() + (timestep / 2) * point_i->getSimProp()->getB().first;
        glm::vec2 pos_j = point_j->getSimProp()->getPosition() + (timestep / 2) * point_j->getSimProp()->getB().first;
        glm::vec2 vel_i = point_i->getSimProp()->getVelocity() + (timestep / 2) * point_i->getSimProp()->getB().second;
        glm::vec2 vel_j = point_j->getSimProp()->getVelocity() + (timestep / 2) * point_j->getSimProp()->getB().second;
        auto force_i = spring->calculateSpringForce(pos_i, pos_j, vel_i, vel_j);
        auto force_j = spring->calculateSpringForce(pos_j, pos_i, vel_j, vel_i);
        point_i->getSimProp()->addToC(glm::vec2(0, 0), force_i);
        point_j->getSimProp()->addToC(glm::vec2(0, 0), force_j);
    }

    // calc d
    for(const auto& point : m_points) {
        glm::vec2 v = point->getSimProp()->getVelocity() + timestep * point->getSimProp()->getB().second;
        glm::vec2 fg = glm::vec2(0, 0);
        if(m_globalSimulationSettings->isGravityEnabled() && !point->isStatic()) {
            fg = m_globalSimulationSettings->getGravity(); // add gravity
        }
        point->getSimProp()->addToD(v, fg);
    }
    for(const auto& spring : m_springs) {
        auto point_i = spring->getI();
        auto point_j = spring->getJ();
        glm::vec2 pos_i = point_i->getSimProp()->getPosition() + timestep * point_i->getSimProp()->getC().first;
        glm::vec2 pos_j = point_j->getSimProp()->getPosition() + timestep * point_j->getSimProp()->getC().first;
        glm::vec2 vel_i = point_i->getSimProp()->getVelocity() + timestep * point_i->getSimProp()->getC().second;
        glm::vec2 vel_j = point_j->getSimProp()->getVelocity() + timestep * point_j->getSimProp()->getC().second;
        auto force_i = spring->calculateSpringForce(pos_i, pos_j, vel_i, vel_j);
        auto force_j = spring->calculateSpringForce(pos_j, pos_i, vel_j, vel_i);
        point_i->getSimProp()->addToD(glm::vec2(0, 0), force_i);
        point_j->getSimProp()->addToD(glm::vec2(0, 0), force_j);
    }

    for(const auto& point : m_points) {
        point->simulate(m_globalSimulationSettings.get());
        point->getSimProp()->clearABCD();
    }
}

void Scene::positionBasedDynamicsStretching() {
    float timestep = m_globalSimulationSettings->getTimestep();
    // calculate other forces for each points
    for(const auto& point : m_points) {
        if(m_globalSimulationSettings->isGravityEnabled() && !point->isStatic()) {
            glm::vec2 v = point->getSimProp()->getVelocity() + timestep * point->getSimProp()->getInvMass() * m_globalSimulationSettings->getGravity();
            point->getSimProp()->setVelocity(v); // add gravity
        }
    }
    for(const auto& point : m_points) {
        glm::vec2 x = point->getSimProp()->getPosition();
        glm::vec2 v = point->getSimProp()->getVelocity();
        point->getSimProp()->setPredictedPosition(x + timestep * v);
    }
    // TODO generateCollisionConstraints(x -> p)

    for(const auto& point: m_points) {
        auto predPos = point->getSimProp()->getPredictedPosition();
        if(predPos.y < -0.7) {
            auto newPredPos = glm::vec2(predPos.x, -0.7);
            point->getSimProp()->setPredictedPosition(newPredPos);
        }
    }

    // project constraints
    int iterNum = m_globalSimulationSettings->getPBDIterNum();
    float stiffness = m_globalSimulationSettings->getPBDSystemStiffness();
    for(int i = 0; i < iterNum; i++) {
        for(const auto& spring : m_springs) {
            auto point_i = spring->getI();
            auto point_j = spring->getJ();
            auto w_i = point_i->getSimProp()->getInvMass();
            auto w_j = point_j->getSimProp()->getInvMass();
            auto predPos_i = point_i->getSimProp()->getPredictedPosition();
            auto predPos_j = point_j->getSimProp()->getPredictedPosition();
            auto d = spring->getDefaultLength();
            auto posDiff = glm::length(predPos_i - predPos_j);

            if((w_i > 0 || w_j > 0) && posDiff > 0) {
                glm::vec2 plusDeltaPredPos_i = -(w_i / (w_i + w_j)) * (posDiff - d) * ((predPos_i - predPos_j) / posDiff);
                point_i->getSimProp()->setPredictedPosition(predPos_i + plusDeltaPredPos_i * stiffness );

                glm::vec2 plusDeltaPredPos_j = (w_j / (w_i + w_j)) * (posDiff - d) * ((predPos_i - predPos_j) / posDiff);
                point_j->getSimProp()->setPredictedPosition(predPos_j + plusDeltaPredPos_j * stiffness);
            }
        }
    }

    //calculate new position and velocity
    for(const auto& point : m_points) {
        point->simulate(m_globalSimulationSettings.get());
    }
}

void Scene::initShapeMatching() {
    // original - center of mass
    m_original_cm = glm::vec2(0, 0);
    float w_sum = 0.0;

    for(const auto& point : m_points) {
        float w_i = 1.0 / (point->getSimProp()->getInvMass() + 0.0000001);
        w_sum += w_i;
        m_original_cm += w_i * point->getSimProp()->getPosition();
        point->getSimProp()->setOriginalPosition(point->getSimProp()->getPosition());
    }
    if (w_sum > 0.0) {
        m_original_cm = m_original_cm / w_sum;
    }

    // original - A matrix
    Eigen::Array22f Aqq = Eigen::Array22f::Zero();
    for(const auto& point: m_points) {
        glm::vec2 qi = point->getSimProp()->getPosition() - m_original_cm;
        float w_i = 1.0 / (point->getSimProp()->getInvMass() + 0.0000001);
        Aqq(0, 0) += w_i * qi.x * qi.x;
        Aqq(0, 1) += w_i * qi.x * qi.y;
        Aqq(1, 0) += w_i * qi.y * qi.x;
        Aqq(1, 1) += w_i * qi.y * qi.y;
    }
    A_firstrow = glm::vec2(Aqq(0, 0), Aqq(0, 1));
    A_secondrow = glm::vec2(Aqq(1, 0), Aqq(1, 1));
}

void Scene::shapeMatching() {
    //initShapeMatching();
    // calculate predicted positions
    float timestep = m_globalSimulationSettings->getTimestep();
    // calculate other forces for each points

//    for(const auto& point : m_points) {
//        if(m_globalSimulationSettings->isGravityEnabled() && !point->isStatic()) {
//            glm::vec2 v = point->getSimProp()->getVelocity() + timestep * point->getSimProp()->getInvMass() * m_globalSimulationSettings->getGravity();
//            point->getSimProp()->setVelocity(v); // add gravity
//        }
//    }
//    for(const auto& point : m_points) {
//        glm::vec2 x = point->getSimProp()->getPosition();
//        glm::vec2 v = point->getSimProp()->getVelocity();
//        point->getSimProp()->setPredictedPosition(x + timestep * v);
//    }

    // new - center of mass
    glm::vec2 new_cm = glm::vec2(0, 0);
    float w_sum = 0.0;

    for(const auto& point : m_points) {
        float w_i = 1.0 / (point->getSimProp()->getInvMass() + 0.0000001);
        w_sum += w_i;
        new_cm += w_i * point->getSimProp()->getPredictedPosition();
    }
    if (w_sum > 0.0) {
        new_cm = new_cm / w_sum;
    }

    // new - A matrix
    Eigen::Array22f Apq = Eigen::Array22f::Zero();
    for(const auto& point: m_points) {
        glm::vec2 qi = point->getSimProp()->getOriginalPosition() - m_original_cm;
        glm::vec2 pi = point->getSimProp()->getPredictedPosition() - new_cm;
        float w_i = 1.0 / (point->getSimProp()->getInvMass() + 0.0000001);
        Apq(0, 0) += w_i * pi.x * qi.x;
        Apq(0, 1) += w_i * pi.x * qi.y;
        Apq(1, 0) += w_i * pi.y * qi.x;
        Apq(1, 1) += w_i * pi.y * qi.y;
    }

    // correction
    Eigen::Array22f Aqq;
    Aqq << A_firstrow.x, A_firstrow.y, A_secondrow.x, A_secondrow.y;
    Eigen::Matrix2f A = Apq.matrix() * Aqq.matrix().inverse();
    Eigen::JacobiSVD<Eigen::Matrix2f> svd(A, Eigen::ComputeFullU | Eigen::ComputeFullV);

    const Eigen::Matrix2f &U = svd.matrixU();
    const Eigen::Matrix2f &V = svd.matrixV();

    Eigen::Matrix2f R = U * V.transpose();

    float beta = m_globalSimulationSettings->getBeta();
    for(const auto& point : m_points) {
        glm::vec2 q_i = point->getSimProp()->getOriginalPosition() - m_original_cm;
        Eigen::Vector2f qi = Eigen::Vector2f(q_i.x, q_i.y);
//        Eigen::Vector2f final_pos = (R * qi) + Eigen::Vector2f(new_cm.x, new_cm.y);
        Eigen::Vector2f final_pos = ((beta * A + (1-beta) * R) * qi) + Eigen::Vector2f(new_cm.x, new_cm.y);

        glm::vec2 newpos = glm::vec2(final_pos.x(), final_pos.y());
        point->getSimProp()->setPredictedPosition( newpos);
//        printf("%f %f \t%f %f\n",
//               point->getSimProp()->getPosition().x,
//               point->getSimProp()->getPosition().y,
//               point->getSimProp()->getPredictedPosition().x,
//               point->getSimProp()->getPredictedPosition().y);
    }

    //calculate new position and velocity
    for(const auto& point : m_points) {
        point->simulate(m_globalSimulationSettings.get());
    }
}

void Scene::render(bool recordOn) {
    m_shader->use();

    m_frameBuffer->bind();

    for(const auto &spring : m_springs) {
        spring->render(m_shader.get());
    }

    for(const auto &point : m_points) {
        point->render(m_shader.get());
        if(!m_hideHelperVectors) {
            point->renderHelpers(m_shader.get());
        }
    }

    if(m_mode == ViewportMode::SpringCreation) {
        springCreationLine.update(m_shader.get());
        springCreationLine.create();
        springCreationLine.draw();
    }

    if(recordOn) {
        m_frameBuffer->recordToData();
    }

    m_frameBuffer->unbind();
}

void Scene::inputEvent(double x, double y, const GuiState &guiState) {
    if(m_activeObjectId == -1 && m_mode == ViewportMode::Grab) {
        m_mode = ViewportMode::Default;
    }

    switch (m_mode) {
        case Default: selectionMode(x, y);
            break;
        case Grab: grabMode(x, y);
            break;
        case PointCreation:
        case SpringCreation: creationMode(x, y, guiState.referencePoint, guiState.referenceSpring);
            break;
        case ViewPan:
            break;
    }
}

std::shared_ptr<Point> Scene::addPoint(const glm::vec2& position) {
    auto object = std::make_shared<Point>(position);
    m_objects.insert(std::make_pair(object->getId(), object));
    m_points.push_back(object);
    return object;
}

std::shared_ptr<Point> Scene::addPoint(std::shared_ptr<Point> object) {
    m_objects.insert(std::make_pair(object->getId(), object));
    m_points.push_back(object);
    return object;
}

void Scene::addStaticPoint(glm::vec2 position) {
    auto object = addPoint(position);
    object->setStatic(true);
}

void Scene::addSpring(const std::shared_ptr<Point>& i, const std::shared_ptr<Point>& j, float stretchnig, float dampingCoeffitient) {
    auto object = std::make_shared<Spring>(i, j, stretchnig, dampingCoeffitient);
    i->addConnection(object);
    j->addConnection(object);
    m_objects.insert(std::make_pair(object->getId(), object));
    m_springs.push_back(object);
}

void Scene::addSpring(const std::shared_ptr<Spring>& object) {
    object->getI()->addConnection(object);
    object->getJ()->addConnection(object);
    m_objects.insert(std::make_pair(object->getId(), object));
    m_springs.push_back(object);
}


std::map<size_t, std::string> Scene::getObjects() const {
    std::map<size_t, std::string> geometries;
    for(const auto& object : m_objects) {
        geometries.insert({object.first, object.second->getName()});
    }
    return geometries;
}

void Scene::setActiveObject(int activeObjectId) {
    if(m_activeObjectId != -1) {
        getActiveObject()->getGeometry()->setColorToDefault();
        m_activeObjectId = -1;
    }
    if(m_activeObjectId != activeObjectId && activeObjectId > -1) {
        this->m_activeObjectId = activeObjectId;
        getActiveObject()->getGeometry()->setColor(1.0f, 0.4f, 0.4f, 1.0f);
    }
}

const std::shared_ptr<Object> &Scene::getActiveObject() const {
    if(m_activeObjectId >= 0) {
        return m_objects.find(this->m_activeObjectId)->second;
    }
    throw std::out_of_range("Get active object when active object id is -1!");
}

std::vector<std::shared_ptr<Point>> Scene::getPoints() const {
    return m_points;
}

std::vector<std::shared_ptr<Spring>> Scene::getSprings() const {
    return m_springs;
}

void Scene::clearAllObject() {
    m_objects.clear();
    m_springs.clear();
    m_points.clear();
    m_activeObjectId = -1;
}

const std::shared_ptr<Object> &Scene::getObjectByName(const std::string &objectName) const {
    for(const auto& obj : m_objects) {
        if(obj.second->getName() == objectName) {
            return obj.second;
        }
    }
    throw std::out_of_range("Name is not exist!");
}

const std::unique_ptr<GlobalSimulationSettings> &Scene::getGlobalSimulationSettings() const {
    return m_globalSimulationSettings;
}

void Scene::setGlobalSimulationSettings(std::unique_ptr<GlobalSimulationSettings> globalSimulationSettings) {
    m_globalSimulationSettings = std::move(globalSimulationSettings);
}

int Scene::getActiveObjectId() const {
    return m_activeObjectId;
}

unsigned int Scene::getRenderTextureId() const {
    return m_frameBuffer->getRenderedTexture();
}

void Scene::updateCamera(float width, float height) const {
    m_shader->use();
    m_camera->setAspectRation(width / height);
    m_camera->update(m_shader.get());
}

void Scene::setHideHelperVectors(bool hideHelperVectors) {
    m_hideHelperVectors = hideHelperVectors;
}

bool Scene::getHideHelperVectors() const {
    return m_hideHelperVectors;
}

void Scene::refreshButtonStatus(GLFWwindow *window) {
    m_mouseState.buttonPressed(window);
}

void Scene::setMode(ViewportMode mode) {
    m_mode = mode;
}

void Scene::grabMode(double x, double y) {
    const auto& currentObject = getActiveObject();
    ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);

    if(m_grabObjectLastPos == glm::vec2(0, 0)) {
        m_grabObjectLastPos = currentObject->getSimProp()->getPosition();
    }

    currentObject->move(glm::vec2(x, y));
    currentObject->setFix(true);

    // move stop
    if(m_mouseState.leftIsActive() || m_mouseState.rightIsActive()) {
        if(m_mouseState.rightIsActive()) {
            currentObject->move(m_grabObjectLastPos);
        }
        currentObject->setFix(false);
        m_mode = ViewportMode::Default;
        m_grabObjectLastPos = glm::vec2(0, 0);
    }
}

void Scene::selectionMode(double x, double y) {
    if(m_mouseState.leftIsActive() && m_mouseState.leftButtonStateChanged()) {
        for(const auto& point : m_points) {
            if(point->isInside(x, y)) {
                setActiveObject(point->getId());
            }
        }
    }
}

void Scene::creationMode(double x, double y, const Point& refPoint, const Spring& refSpring) {
    if (m_mode == ViewportMode::PointCreation) {
        if(m_mouseState.leftIsActive() && m_mouseState.leftButtonStateChanged()) {
            const auto &point = addPoint({x, y});
            point->setStatic(refPoint.isStatic());
        }
    }
    if(m_mode == ViewportMode::SpringCreation) {
        if(!m_mouseState.leftIsActive() && !m_mouseState.leftButtonStateChanged()) {
            deselectAll();
            for(const auto& point : m_points) {
                if(point->isInside(x, y)) {
                    setActiveObject(point->getId());
                    springCreationFirstPoint = point;
                }
            }
        }
        if(m_mouseState.leftIsActive()) {
            springCreationLine.setEndPoint({x, y});
            deselectAll();
            for(const auto& point : m_points) {
                if(point->isInside(x, y)) {
                    setActiveObject(point->getId());
                    springCreationLastPoint = point;
                }
            }
        }
        if(m_mouseState.leftIsActive() && m_mouseState.leftButtonStateChanged()) {
            glm::vec2 startPos = springCreationFirstPoint->getSimProp()->getPosition();
            springCreationLine.setStartPoint(startPos);
        }
        if(!m_mouseState.leftIsActive() && m_mouseState.leftButtonStateChanged()) {
            springCreationLine.setStartPoint({0, 0});
            springCreationLine.setEndPoint({0, 0});
            addSpring(springCreationFirstPoint, springCreationLastPoint, refSpring.getStretching(),
                      refSpring.getDampingCoefficient());
        }
    }
    if(m_mouseState.rightIsActive()) {
        m_mode = ViewportMode::Default;
        springCreationLine.setStartPoint({0, 0});
        springCreationLine.setEndPoint({0, 0});
    }
}

ViewportMode Scene::getMode() const {
    return m_mode;
}

void Scene::deselectAll() {
    setActiveObject(-1);
}

const FrameBuffer &Scene::getFrameBuffer() const {
    return *m_frameBuffer;
}

void Scene::modifyAllSpring(float stretching, float damping, float defaultLength) {
    for(const auto& spring : m_springs) {
        spring->setStretching(stretching);
        spring->setDampingCoefficient(damping);
        spring->setDefaultLength(defaultLength);
    }
}

long long Scene::getSimulationTime() const {
    return m_simTime;
}

glm::vec2 Scene::orthoProjection(glm::vec2 a, glm::vec2 b) {
    glm::vec2 b_norm = glm::normalize(b);
    return (glm::dot(a, b_norm) / glm::dot(b_norm, b_norm)) * b_norm;
}

void Scene::resetShapeMatchingInit() {
    m_shapeMatchingInitialized = false;
}
