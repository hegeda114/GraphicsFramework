//
// Created by hegeda on 2021-09-29.
//

#include <memory>
#include <imgui.h>
#include "Scene.h"

void Scene::init() {
    // Init simulation state
    m_globalSimulationSettings = std::make_unique<GlobalSimulationSettings>(SimulationMode::ExplicitEuler, 1.0/60.0);
    m_globalSimulationSettings->setBorders(1.0, 1.0, -1.0, -1.0);

    m_shader = std::make_unique<Shader>();
    m_shader->createShader();

    m_camera = std::make_unique<OrthogonalCamera>();

    m_frameBuffer = std::make_unique<FrameBuffer>();
    m_frameBuffer->createBuffer(800, 800);

    auto point1 = this->addPoint(glm::vec2(0, 0));
    point1->setStatic(true);
    auto point2 = this->addPoint({0.2, 0.0});
    this->addSpring(point1, point2, 10, 0, 0.2);
    point2->getSimulationProperties()->setVelocity(0.01, 0.0);
    auto point3 = this->addPoint({0.4, 0.0});
    point3->setStatic(true);
    this->addSpring(point2, point3, 10, 0, 0.2);

//    int maxNum = 4;
//    float length = 0.2;
//
//    std::vector<std::shared_ptr<Point>> springs;
//    std::shared_ptr<Point> prevCol;
//    for(int i = 0; i < maxNum; i++) {
//        for(int j = 0; j < maxNum; j++) {
//            auto point = this->addPoint(glm::vec2(length*i, length*j));
//            springs.push_back(point);
//            if(i == 0) {
//                point->setStatic(true);
//            }
//            if(j == 0) {
//                prevCol = point;
//            }
//            if(j > 0) {
//                this->addSpring(prevCol, point, 10000, 0, glm::length(prevCol->getSimulationProperties()->getPosition() -
//                                                                      point->getSimulationProperties()->getPosition()));
//                prevCol = point;
//            }
//            if(i > 0) {
//                int own_idx = i*maxNum+j;
//                this->addSpring(springs[own_idx-maxNum], point, 10000, 0, glm::length(
//                        springs[own_idx - maxNum]->getSimulationProperties()->getPosition() -
//                                                                                      point->getSimulationProperties()->getPosition()));
//            }
//            if(i*3+j >= maxNum-1 && j < maxNum-1 && i < maxNum) {
//                int own_idx = i * maxNum + j;
//                this->addSpring(springs[own_idx - maxNum + 1], point, 10000, 0, glm::length(
//                        springs[own_idx - maxNum + 1]->getSimulationProperties()->getPosition() -
//                                                                                            point->getSimulationProperties()->getPosition()));
//            }
//            //if(i*3+j > maxNum-1 && j < maxNum-1 && i < maxNum) {
//            //    int own_idx = i*maxNum+j;
//            //    this->addSpring(springs[own_idx-maxNum+1], point, 10, 0, std::sqrt(length*length));
//            //}
//        }
//        //prevRow.clear();
//    }
}

void Scene::simulate() {
    double frame_rate = 1.0/60.0;
    int iteration = ceil(frame_rate / m_globalSimulationSettings->getTimestep());
    for(int i = 0; i < iteration; i++) {
        // calculate spring forces for each springs
        for(const auto& spring : m_springs) {
            spring->calculateSpringForces();
        }
        // calculate other forces for each points
        for(const auto& point : m_points) {
            if(m_globalSimulationSettings->isGravityEnabled() && !point->isStatic()) {
                point->getSimulationProperties()->addForce(m_globalSimulationSettings->getGravity()); // add gravity
            }
        }
        //calculate new position and velocity
        for(const auto& point : m_points) {
            point->simulate(m_globalSimulationSettings.get());
        }
    }
}

void Scene::render() {
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

    m_frameBuffer->unbind();
}

void Scene::inputEvent(double x, double y, MouseButton button, ViewportMode mode) {
    bool activeObjectExist = false;
    if(this->m_activeObjectId != -1) {
        activeObjectExist = true;
    }

    bool lastMouseLeftPressActive = m_mouseLeftPressActive;
    if(button == MouseButton::LeftPress) {
        m_mouseLeftPressActive = true;
    }
    if(button == MouseButton::LeftRelease) {
        m_mouseLeftPressActive = false;
    }


    if(mode == ViewportMode::Grab && activeObjectExist) {
        const auto& currentObject = getActiveObject();

        // move start or continue
        if(m_mouseLeftPressActive && (currentObject->isInside(x, y) || lastMouseLeftPressActive)) {
            m_mouseLastPosition = {x, y};
            currentObject->move(x, y);
            currentObject->setFix(true);
        }

        // move stop
        if(!m_mouseLeftPressActive && lastMouseLeftPressActive) {
            glm::vec2 diff = glm::vec2(x, y) - m_mouseLastPosition;
            diff *= 15;
            currentObject->getSimulationProperties()->setVelocity(diff.x, diff.y);
            currentObject->setFix(false);
        }
    }

    if(mode == ViewportMode::Selection) {
        if(m_mouseLeftPressActive && (lastMouseLeftPressActive != m_mouseLeftPressActive)) {
            for(const auto& point : m_points) {
                if(point->isInside(x, y)) {
                    setActiveObject(point->getId());
                }
            }
        }
    }
}

void Scene::move_to_home(double x, double y) {
    if(this->m_activeObjectId == -1) {
        return;
    }
    const auto& currentObject = m_objects.find(this->m_activeObjectId)->second;
    currentObject->move(x, y);
    currentObject->setFix(true);
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

void Scene::addSpring(const std::shared_ptr<Point>& i, const std::shared_ptr<Point>& j, float stretchnig, float dampingCoeffitient, float defaultLengeth) {
    auto object = std::make_shared<Spring>(i, j, stretchnig, dampingCoeffitient, defaultLengeth);
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
    if(m_activeObjectId != -1 && m_activeObjectId != activeObjectId) {
        getActiveObject()->getGeometry()->setColorToDefault();
        m_activeObjectId = -1;
    }
    if(m_activeObjectId != activeObjectId) {
        this->m_activeObjectId = activeObjectId;
        getActiveObject()->getGeometry()->setColor(1.0f, 0.4f, 0.4f, 1.0f);
    } else {
        getActiveObject()->getGeometry()->setColorToDefault();
        m_activeObjectId = -1;
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


