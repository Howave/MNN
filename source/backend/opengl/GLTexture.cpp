//
//  GLTexture.cpp
//  MNN
//
//  Created by MNN on 2019/01/31.
//  Copyright © 2018, Alibaba Group Holding Limited
//

#include "GLTexture.hpp"
namespace MNN {
namespace OpenGL {
#include "AutoTime.hpp"

GLTexture::~GLTexture() {
    AUTOTIME;
    glDeleteTextures(1, &mId);
    OPENGL_CHECK_ERROR;
}

GLTexture::GLTexture(int w, int h, int d, GLenum target, bool HWC4) {
    AUTOTIME;
    if(target == GL_TEXTURE_3D){
        GLASSERT(w > 0 && h > 0 && d > 0);
        mTarget = target;
        glGenTextures(1, &mId);
        OPENGL_CHECK_ERROR;
        glBindTexture(mTarget, mId);
        OPENGL_CHECK_ERROR;
        glTexParameteri(mTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        OPENGL_CHECK_ERROR;
        glTexParameteri(mTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        OPENGL_CHECK_ERROR;
        glTexParameteri(mTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        OPENGL_CHECK_ERROR;
        glTexParameteri(mTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        OPENGL_CHECK_ERROR;
        glTexParameteri(mTarget, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        OPENGL_CHECK_ERROR;
        
        int realW = w;
        int realH = h;
        int realD = d;
        if (HWC4) {
            realD = UP_DIV(d, 4);
            realH = h;
            realW = w;
        }
        glTexStorage3D(mTarget, 1, TEXTURE_FORMAT, realW, realH, realD);
        OPENGL_CHECK_ERROR;
    }else if(target == GL_TEXTURE_2D){
        GLASSERT(w > 0 && h > 0);
        mTarget = target;
        glGenTextures(1, &mId);
        OPENGL_CHECK_ERROR;
        glBindTexture(mTarget, mId);
        OPENGL_CHECK_ERROR;
        glTexParameteri(mTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        OPENGL_CHECK_ERROR;
        glTexParameteri(mTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        OPENGL_CHECK_ERROR;
        glTexParameteri(mTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        OPENGL_CHECK_ERROR;
        glTexParameteri(mTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        OPENGL_CHECK_ERROR;
        glTexParameteri(mTarget, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        OPENGL_CHECK_ERROR;
        
        int realW = w;
        int realH = h;
        glTexStorage2D(mTarget, 1, TEXTURE_FORMAT, realW, realH);
        OPENGL_CHECK_ERROR;
    }
    
}

void GLTexture::sample(GLuint unit, GLuint texId) {
    glActiveTexture(GL_TEXTURE0 + texId);
    glUniform1i(unit, texId);
    glBindTexture(mTarget, mId);
    OPENGL_CHECK_ERROR;
}

void GLTexture::read(GLuint unit) {
    glBindImageTexture(unit, mId, 0, GL_TRUE, 0, GL_READ_ONLY, TEXTURE_FORMAT);
    OPENGL_CHECK_ERROR;
}

void GLTexture::write(GLuint unit) {
    glBindImageTexture(unit, mId, 0, GL_TRUE, 0, GL_WRITE_ONLY, TEXTURE_FORMAT);
    OPENGL_CHECK_ERROR;
}
} // namespace OpenGL
} // namespace MNN
