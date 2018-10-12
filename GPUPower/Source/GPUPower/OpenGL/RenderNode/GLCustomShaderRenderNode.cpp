//
//  GLCustomShaderRenderNode.cpp
//  GPUPower
//
//  Created by lingtonke on 2018/10/9.
//  Copyright © 2018 tencent. All rights reserved.
//

#include "GLCustomShaderRenderNode.h"
#include "../GLTexture.h"
#include "../GLVertexArray.h"
#include "GLRenderData.h"
using namespace GPUPower;
GLCustomShaderRenderNode::GLCustomShaderRenderNode(shared_ptr<GLProgram> program):program(program)
{
    
}

shared_ptr<NodeChain::NodeResponse> GLCustomShaderRenderNode::process()
{
    auto response = make_shared<GLRenderResponse>();
    program->use();
    for(auto &pair: inputResponses)
    {
        auto rsp = (GLRenderResponse*)pair.second.get();
        rsp->texture->activeAndBind(pair.first);
    }
    GLVertexArray<>::basicVertexArray()->draw();
    return response;
}
