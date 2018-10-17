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

- (void)didReceiveResponse;
@property (nonatomic) std::shared_ptr<GPUPower::GLPreviewNode> node;

@end

@implementation GPUPowerGLView

- (void)didReceiveResponse
{
    if (self.async)
    {
        [self setNeedsDisplay];
    }
    else
    {
        [self render];
    }
}

- (void)render
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
            program->setUniform("tex", 0);
        }
        GLVertexArray<>::basicVertexArray()->draw();
        NSLog(@"render");
    }
    else
    {
        NSLog(@"NoTexture");
    }
}

- (void)drawRect:(CGRect)rect
{
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    if (self.node->needUpdate)
    {
        [self render];
    }
    else
    {
        self.node->sendRequest(nullptr);
    }
    
}

- (void)setGlcontext:(std::shared_ptr<GPUPower::GLContext>)glcontext
{
    _glcontext = glcontext;
    self.context = (__bridge EAGLContext *)glcontext->context;
    program = GLProgram::create(glcontext);
    program->setShaderString(GPUPower::passThroughVertexShader, GPUPower::passThroughFragmentShader);
    self.node = shared_ptr<GLPreviewNode>(new GLPreviewNode(glcontext));
    self.node->glView = self;
}

- (void)setInput:(std::shared_ptr<GPUPower::GLRenderNode>)node
{
    self.node->removeAllInputs();
    self.node->addInput(node, 0);
    auto a = node->context.lock();
    auto b = self.node->context.lock();
    if (a == b)
    {
        _async = NO;
    }
    else
    {
        if (a->sharegroup&&a->sharegroup == b->sharegroup)
        {
            _async = YES;
        }
        else
        {
            NSAssert(NO, @"sharegroup is NULL or not equal");
        }
    }
}

@end


shared_ptr<NodeResponse> GLPreviewNode::process()
{
    [glView didReceiveResponse];
    return nullptr;
}

void GLPreviewNode::sendRequest(shared_ptr<NodeRequest> request)
{
    needUpdate = true;
    GLRenderNode::sendRequest(request);
}
