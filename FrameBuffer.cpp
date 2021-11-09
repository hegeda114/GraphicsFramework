//
// Created by hegeda on 2021-11-01.
//

#include <glew.h>
#include <cstring>
#include "FrameBuffer.h"

void FrameBuffer::createBuffer(unsigned int width, unsigned int height) {
    m_width = width;
    m_height = height;

    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glCreateTextures(GL_TEXTURE_2D, 1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture, 0);

    unbind();
}

void FrameBuffer::recordToData() {
    GLint currentBuff;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &currentBuff);
    if(currentBuff == (GLint) m_fbo) {
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glReadPixels(0, 0, m_width, m_height, GL_RGB, GL_UNSIGNED_BYTE, m_data);
    }
}

void FrameBuffer::unbind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer() {
    delete[](m_data);
    glDeleteFramebuffers(GL_FRAMEBUFFER, &m_fbo);
}

void FrameBuffer::bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glViewport(0, 0, m_width, m_height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    memset(m_data, 0, 3 * m_width * m_height);
}

unsigned int FrameBuffer::getRenderedTexture() const {
    return m_texture;
}

const GLubyte *FrameBuffer::getData() const {
    return m_data;
}
