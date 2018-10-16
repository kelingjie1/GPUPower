//
//  GLObject.h
//  GPUPower
//
//  Created by lingtonke on 2018/10/11.
//  Copyright © 2018 tencent. All rights reserved.
//
#pragma once
#include "GLContext.h"
#include <memory>
namespace GPUPower
{
    using namespace std;
    class GLObject
    {
    public:
        weak_ptr<GLContext> context;
    protected:
        GLObject(shared_ptr<GLContext> context):context(weak_ptr<GLContext>(context))
        {

        }
        virtual ~GLObject()
        {
            
        }

    public:
        virtual void init()
        {
            auto c = context.lock();
            c->check();
        }
        virtual void cleanup()
        {
            
        }

    };
}
