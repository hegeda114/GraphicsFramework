//
// Created by hegeda on 2021-11-01.
//

#ifndef GRAPHICSFRAMEWORK_FRAMEBUFFER_H
#define GRAPHICSFRAMEWORK_FRAMEBUFFER_H


class FrameBuffer {
private:
    unsigned int m_fbo = -1;
    unsigned int m_texture = -1;
    unsigned int m_width = 800;
    unsigned int m_height = 800;
    GLubyte* m_data = new GLubyte[3 * m_width * m_height];

public:
    FrameBuffer() = default;
    void createBuffer(unsigned int width, unsigned int height);
    void bind() const;
    void unbind() const;
    void recordToData();
    const GLubyte* getData() const;
    unsigned int getRenderedTexture() const;
    ~FrameBuffer();
};


#endif //GRAPHICSFRAMEWORK_FRAMEBUFFER_H
