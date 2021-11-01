//
// Created by hegeda on 2021-11-01.
//

#ifndef GRAPHICSFRAMEWORK_FRAMEBUFFER_H
#define GRAPHICSFRAMEWORK_FRAMEBUFFER_H


class FrameBuffer {
private:
    unsigned int m_fbo = -1;
    unsigned int m_texture = -1;
    unsigned int m_width;
    unsigned int m_height;

public:
    FrameBuffer() = default;
    void createBuffer(unsigned int width, unsigned int height);
    void bind();
    void unbind();
    unsigned int getRenderedTexture() const;
    ~FrameBuffer();
};


#endif //GRAPHICSFRAMEWORK_FRAMEBUFFER_H
