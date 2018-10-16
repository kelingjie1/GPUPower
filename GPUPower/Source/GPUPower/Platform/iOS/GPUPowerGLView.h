//
//  GPUPowerGLView.h
//  GPUPower
//
//  Created by lingtonke on 2018/10/15.
//  Copyright © 2018 tencent. All rights reserved.
//

#pragma once

#import <Foundation/Foundation.h>
#import <GLKit/GLKit.h>
#include "../../OpenGL/RenderNode/GLRenderNode.h"

NS_ASSUME_NONNULL_BEGIN
@class GPUPowerGLView;
namespace GPUPower
{
    class GLPreviewNode:public GLRenderNode
    {
    public:
        __weak GPUPowerGLView *glView;
        GLPreviewNode(shared_ptr<GLContext> context):GLRenderNode(context){}
        virtual shared_ptr<NodeResponse> process();
        virtual void sendRequest(shared_ptr<NodeRequest> request);
        bool needUpdate;
    };
}

@interface GPUPowerGLView : GLKView

@property (nonatomic) std::shared_ptr<GPUPower::GLContext> glcontext;
@property (nonatomic,readonly) BOOL async;

- (void)setInput:(std::shared_ptr<GPUPower::GLRenderNode>)node;

@end

NS_ASSUME_NONNULL_END
