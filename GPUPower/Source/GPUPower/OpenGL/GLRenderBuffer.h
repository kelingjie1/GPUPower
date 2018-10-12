//
//  GLRenderBuffer.hpp
//  GPUPower
//
//  Created by lingtonke on 2018/10/8.
//  Copyright © 2018 tencent. All rights reserved.
//

#pragma once

#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
#include "GLObject.h"
#include "GLContext.h"
#include <memory>
namespace GPUPower
{
    using namespace std;
    class GLRenderBuffer:public GLObject
    {
    public:
        GLuint renderBufferID;
        GLRenderBuffer(shared_ptr<GLContext> context):GLObject(context){}
        virtual void init()
        {
            GLObject::init();
        }

    };
}
