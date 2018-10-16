//
//  GPUPowerIOSBridge.m
//  GPUPower
//
//  Created by lingtonke on 2018/10/12.
//  Copyright © 2018 tencent. All rights reserved.
//

#import "GPUPowerIOSBridge.h"
#import <GLKit/GLKit.h>
#include <map>
#include "../../Error.h"
#include "../../OpenGL/GLContext.h"

using namespace GPUPower;

static map<GLShareGroup*,EAGLSharegroup*> shareGroups;
static map<GLContext*,EAGLContext*> contexts;

void releaseShareGroup(GLShareGroup *group)
{
    shareGroups.erase(group);
    delete group;
}

shared_ptr<GLShareGroup> GPUPowerIOSBridge::createShareGroup()
{
    shared_ptr<GLShareGroup> group(new GLShareGroup(),releaseShareGroup);
    return group;
}
void *GPUPowerIOSBridge::createContext(GLShareGroup *sharegroup,GLContext *context)
{
    EAGLContext *eaglcontext;
    if (sharegroup)
    {
        EAGLSharegroup *group = shareGroups[sharegroup];
        eaglcontext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3 sharegroup:group];
    }
    else
    {
        eaglcontext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    }
    if (!eaglcontext)
    {
        throw Error(GPUPowerError_ContextCreateFailed);
    }
    contexts[context] = eaglcontext;
    return (__bridge void*)eaglcontext;
}

void GPUPowerIOSBridge::setContext(GLContext *context)
{
    [EAGLContext setCurrentContext:(__bridge EAGLContext*)context];
}

void GPUPowerIOSBridge::releaseContext(GLContext *context)
{
    contexts.erase(context);
}

bool GPUPowerIOSBridge::isMainThread()
{
    return [NSThread isMainThread];
}

void GPUPowerIOSBridge::addMainThreadTask(function<void()> func)
{
    dispatch_async(dispatch_get_main_queue(), ^{
        func();
    });
}
