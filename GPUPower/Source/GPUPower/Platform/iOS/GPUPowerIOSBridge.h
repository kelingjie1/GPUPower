//
//  GPUPowerIOSBridge.h
//  GPUPower
//
//  Created by lingtonke on 2018/10/12.
//  Copyright © 2018 tencent. All rights reserved.
//

#pragma once
#include <memory>

namespace GPUPower
{
    using namespace std;
    class GLShareGroup;
    class GLContext;
    class GLTexture;
    class GPUPowerIOSBridge
    {
    public:
        static shared_ptr<GLShareGroup> createShareGroup();
        static void *createContext(GLShareGroup *sharegroup,GLContext *context);
        static void setContext(GLContext *context);
        static void releaseContext(GLContext *context);
    };
};



