//
//  GLTexture.h
//  GPUPower
//
//  Created by lingtonke on 2018/10/8.
//  Copyright © 2018 tencent. All rights reserved.
//
#pragma once

#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
#include "GLContext.h"
#include "GLObject.h"

namespace GPUPower
{
    class GLTexture:public GLObject
    {
    protected:
        GLTexture(shared_ptr<GLContext> context):GLObject(context){}
    public:
        GLuint textureID;
        
        static shared_ptr<GLTexture> create(shared_ptr<GLContext> context)
        {
            return shared_ptr<GLTexture>(new GLTexture(context));
        }
        
        
        virtual void init()
        {
            GLObject::init();
            glGenTextures(1, &textureID);
        }

        virtual void cleanup()
        {
            GLObject::cleanup();
            auto c = context.lock();
            GLuint tex = textureID;
            c->checkAndAsyncTask([=]{
                glDeleteTextures(1, &tex);
            });
            
        }

        void setImageData(const GLvoid *pixels, GLsizei width,GLsizei height,GLenum internalformat=GL_RGBA,GLenum format=GL_RGBA)
        {
            glBindTexture(GL_TEXTURE_2D, textureID);
            if (pixels)
            {
                glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
            }
            else
            {
                glTexStorage2D(GL_TEXTURE_2D, 0, internalformat, width, height);
            }
        }

        void activeAndBind(GLuint index)
        {
            auto c = context.lock();
            c->check();
            glActiveTexture(GL_TEXTURE0+index);
            glBindTexture(GL_TEXTURE_2D, textureID);
        }
    };
};

