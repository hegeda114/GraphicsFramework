//
// Created by hegeda on 2021-10-26.
//

#include <fstream>
#include <chrono>
#include <sstream>
#include "IO.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Dependencies/stb_image.h"

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

bool IO::loadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height) {
    // Load from file
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

    // Upload pixels into texture
//#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
//    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
//#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    return true;
}

void IO::save_record_info(const std::string &filePath, const GuiState *guiState, const Scene *scene, const std::vector<int> &simTimeList) {
    std::ofstream infoFile(filePath + "/info.txt");

    if (!infoFile.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        return;
    }

    std::string simulationApproach;
    switch (scene->getGlobalSimulationSettings()->getSimApproach()) {
        case MassSpringSystem: simulationApproach = "Mass Spring System";
            break;
        case PositionBasedDynamics: simulationApproach = "Position Based Dynamics";
            break;
    }

    infoFile << "Simulation Approach: " << simulationApproach << std::endl;

    std::string simulationMode;
    switch (scene->getGlobalSimulationSettings()->getSimMode()) {
        case ExplicitEuler: simulationMode = "Explicit Euler";
            break;
        case RungeKuttaSecondOrder: simulationMode = "Second Order Runge-Kutta";
            break;
        case RungeKuttaFourthOrder: simulationMode = "Fourth Order Runge-Kutta";
            break;
        case SemiImplicitEuler: simulationMode = "Semi-Implicit Euler";
            break;
    }

    infoFile << "Simulation Mode: " << simulationMode << std::endl;

    infoFile << "PBD Iter Number: " << guiState->currentSimState.getPBDIterNum() << std::endl;

    infoFile << "PBD System Stiffness: " << guiState->currentSimState.getPBDSystemStiffness() << std::endl;

    infoFile << "Timestep: " << scene->getGlobalSimulationSettings()->getTimestep() << std::endl;

    infoFile << "Gravity: " << scene->getGlobalSimulationSettings()->getGravity().x << " " << scene->getGlobalSimulationSettings()->getGravity().y << std::endl;

    infoFile << "Sting Stiffness: " << scene->getSprings()[0]->getStretching() << std::endl;

    infoFile << "String Damping: " << scene->getSprings()[0]->getDampingCoefficient() << std::endl;

    infoFile << "Average Simulation Time per Frame: " << std::endl;

    for(const auto& item : simTimeList) {
        infoFile << item << " ";
    }
    infoFile << std::endl;

    // Close the file
    infoFile.close();
}
