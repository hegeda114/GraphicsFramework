//
// Created by hegeda on 2021-10-26.
//

#include <fstream>
#include <chrono>
#include <sstream>
#include "IO.h"

void IO::save_scene(const Scene *scene, const std::string &filePath) {
    std::ofstream sceneFile("../saved_scenes/" + filePath + ".txt");

    if (!sceneFile.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        return;
    }

    auto current_time = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(current_time);

    sceneFile << "Timestamp: " << std::ctime(&time);
    auto points = scene->getPoints();
    auto springs = scene->getSprings();
    const auto& globalSimSettings = scene->getGlobalSimulationSettings();
    sceneFile << points.size() << std::endl;
    sceneFile << springs.size() << std::endl;
    for(const auto& point : points) {
        sceneFile << point->getSerializedData() << std::endl;
    }
    for(const auto& spring : springs) {
        sceneFile << spring->getSerializedData() << std::endl;
    }
    sceneFile << globalSimSettings->getSerializedData() << std::endl;

    // Close the file
    sceneFile.close();
}

void IO::open_scene(const std::string &filePath, Scene *scene) {
    scene->clearAllObject();
    std::ifstream sceneFile(filePath);

    if (!sceneFile.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        return;
    }

    std::string line;
    getline(sceneFile, line); //Timestamp
    getline(sceneFile, line);
    size_t numOfPoints = std::stoi(line);
    getline(sceneFile, line);
    size_t numOfStrings = std::stoi(line);
    for(size_t i = 0; i < numOfPoints; i++) {
        getline(sceneFile, line);
        scene->addPoint(Point::createPointFromSavedData(line));
    }
    for(size_t i = 0; i < numOfStrings; i++) {
        getline(sceneFile, line);
        std::stringstream ss(line);
        std::string val;
        getline(ss, val, ';');
        std::shared_ptr<Point> p_i = std::static_pointer_cast<Point>(scene->getObjectByName(val));
        getline(ss, val, ';');
        std::shared_ptr<Point> p_j = std::static_pointer_cast<Point>(scene->getObjectByName(val));

        getline(ss, val, ';');
        double radius = std::stod(val);
        scene->addSpring(Spring::createSpringFromSavedData(p_i, p_j, line));
    }
    getline(sceneFile, line);
    scene->setGlobalSimulationSettings(GlobalSimulationSettings::createFromSavedData(line));


    sceneFile.close();
}
