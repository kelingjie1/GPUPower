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
#include "../Platform/GPUPowerPlatform.h"

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
    class GLShareGroup
    {
    public:
        
    };
    
    class GLContext;
    static thread_local shared_ptr<GLContext> currentContext;
    
    class GLContext:public enable_shared_from_this<GLContext>
    {
        NodeChain::TaskQueue taskQueue;
        GLContext(GLShareGroup *sharegroup):sharegroup(sharegroup)
        {
            context = GPUPowerIOSBridge::createContext(sharegroup, this);
        }
        void init()
        {
            auto s = shared_from_this();
            taskQueue.start([=]
                            {
                                currentContext = s;
                            });
        }
    public:
        shared_ptr<GLShareGroup> sharegroup;
        void *context;
        static shared_ptr<GLContext> current()
        {
            return currentContext;
        }
        
        static shared_ptr<GLContext> create(GLShareGroup *sharegroup = nullptr)
        {
            auto context = shared_ptr<GLContext>(new GLContext(sharegroup));
            context->init();
            return context;
        }
        
        
        
        ~GLContext()
        {
            GPUPowerIOSBridge::releaseContext(this);
        }

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
    };
}
