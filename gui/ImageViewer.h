//
// Created by hegeda on 2021-11-06.
//

#ifndef GRAPHICSFRAMEWORK_IMAGEVIEWER_H
#define GRAPHICSFRAMEWORK_IMAGEVIEWER_H


#include "GuiWindow.h"

class ImageViewer : public GuiWindow {
private:
    int m_imageWidth = -1;
    int m_imageHeight = -1;
    GLuint m_imageTexture = -1;
    bool m_hasImage = false;
public:
    ImageViewer(std::shared_ptr<Scene> scene, std::shared_ptr<GuiState> guiState);
    void create() override;
};


#endif //GRAPHICSFRAMEWORK_IMAGEVIEWER_H
