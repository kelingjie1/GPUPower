//
//  GLContext.h
//  GPUPower
//
//  Created by lingtonke on 2018/10/9.
//  Copyright © 2018 tencent. All rights reserved.
//
#pragma once

#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
#include "../NodeChain/TaskQueue.h"
#include "../Error.h"

namespace GPUPower
{
    using namespace std;
    class GLTexture;
    class GLFrameBuffer;
    class GLRenderBuffer;
    class GLProgram;
    template<class vboType,class eboType>
    class GLVertexArray;
    
    template<class T>
    class GLBuffer;
    
    class GLContext:public enable_shared_from_this<GLContext>
    {
        NodeChain::TaskQueue taskQueue;
        GLContext(){};
    public:
        void *sharegroup;

        void check()
        {
            if (this_thread::get_id() != taskQueue.getid())
            {
                throw Error(GPUPowerError_ContextCheckFailed);
            }
        }

        void asyncTask(function<void()> func)
        {
            taskQueue.addTask(func);
        }
        void checkAndAsyncTask(function<void()> func)
        {
            if (this_thread::get_id() == taskQueue.getid())
            {
                func();
            }
            else
            {
                taskQueue.addTask(func);
            }
        }

        shared_ptr<GLTexture> createTexture()
        {
            return make_shared<GLTexture>(shared_from_this());
        }
        shared_ptr<GLFrameBuffer> createFrameBuffer()
        {
            return make_shared<GLFrameBuffer>(shared_from_this());
        }
        shared_ptr<GLRenderBuffer> createRenderBuffer()
        {
            return make_shared<GLRenderBuffer>(shared_from_this());
        }
        shared_ptr<GLProgram> createProgram()
        {
            return make_shared<GLProgram>(shared_from_this());
        }

        template<class vboType,class eboType>
        shared_ptr<GLVertexArray<vboType,eboType>> createVertextArray()
        {
            return make_shared<GLVertexArray<vboType,eboType>>(shared_from_this());
        }

        template<class T>
        shared_ptr<GLBuffer<T>> createBuffer()
        {
            return make_shared<GLBuffer<T>>(shared_from_this());
        }
    };
}
