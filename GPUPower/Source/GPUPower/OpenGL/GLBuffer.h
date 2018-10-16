//
//  GLBuffer.h
//  GPUPower
//
//  Created by lingtonke on 2018/10/10.
//  Copyright © 2018 tencent. All rights reserved.
//

#pragma once

#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
#include <string>
#include "../Error.h"
#include "GLObject.h"

namespace GPUPower
{
    using namespace std;
    template<class T>
    class GLBuffer:public GLObject
    {
        GLBuffer(shared_ptr<GLContext> context):GLObject(context),bufferID(0),size(0),count(0){}
    public:
        GLuint bufferID;
        GLsizei size;
        GLsizei count;

        static shared_ptr<GLBuffer> create(shared_ptr<GLContext> context)
        {
            return shared_ptr<GLBuffer>(new GLBuffer(context));
        }
        virtual void init()
        {
            GLObject::init();
            glGenBuffers(1, &bufferID);
            if (!bufferID)
            {
                throw Error();
            }
        }
        
        void alloc(GLsizei count,T *data=nullptr,GLenum usage=GL_DYNAMIC_DRAW)
        {
            auto c = context.lock();
            c->check();
            this->count = count;
            size = count*sizeof(T);
            glBufferData(bufferID, size, data, usage);
        }
        void accessData(function<void(T *data)> func,GLuint offset=0,GLuint length=0,GLbitfield access=GL_MAP_READ_BIT|GL_MAP_WRITE_BIT)
        {
            auto c = context.lock();
            c->checkAndAsyncTask([&]{
                auto data = lock(offset,length,access);
                func(data);
                unlock();
            });
        }
        T *lock(GLuint offset=0,GLuint length=0,GLbitfield access=GL_MAP_READ_BIT|GL_MAP_WRITE_BIT)
        {
            auto c = context.lock();
            c->check();
            if (length == 0)
            {
                length = size-offset;
            }
            void *data = glMapBufferRange(bufferID, offset, length, access);
            if (!data)
            {
                GLenum error = glGetError();
                throw Error(GPUPowerError_MapBufferFailed,error);
            }
            return (T*)data;
        }
        void unlock()
        {
            auto c = context.lock();
            c->check();
            if(!glUnmapBuffer(bufferID))
            {
                GLenum error = glGetError();
                throw Error(GPUPowerError_UnMapBufferFailed,error);
            }
        }
    };
}
