//
//  GPUPowerGLView.m
//  GPUPower
//
//  Created by lingtonke on 2018/10/15.
//  Copyright © 2018 tencent. All rights reserved.
//

#import "GPUPowerGLView.h"
#include "../../OpenGL/GLProgram.h"
#include "../../OpenGL/GLVertexArray.h"
#include "../../OpenGL/GLTexture.h"
#include "../../OpenGL/RenderNode/GLRenderData.h"
using namespace GPUPower;
@interface GPUPowerGLView()
{
    shared_ptr<GLProgram> program;
}


@end

@implementation GPUPowerGLView

- (void)drawRect:(CGRect)rect
{
    if (self.async)
    {
        
    }
    else
    {
        auto rsp = _node->getInputResponses();
        if (rsp.size()>0)
        {
            program->use();
            auto it = rsp.begin();
            auto renderRsp = dynamic_pointer_cast<GLRenderResponse>(it->second);
            if (renderRsp&&renderRsp->texture)
            {
                renderRsp->texture->activeAndBind(0);
            }
            GLVertexArray<>::basicVertexArray()->draw();
        }
        else
        {
            
        }
        
    }
}

- (void)setGlcontext:(std::shared_ptr<GPUPower::GLContext>)glcontext
{
    _glcontext = glcontext;
    self.context = (__bridge EAGLContext *)glcontext->context;
    program = GLProgram::create(glcontext);
    program->setShaderString(GPUPower::passThroughVertexShader, GPUPower::passThroughFragmentShader);
}

- (void)setInput:(std::shared_ptr<GPUPower::GLRenderNode>)node
{
    self.node->removeAllInputs();
}

@end
