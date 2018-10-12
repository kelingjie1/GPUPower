//
//  GLCustomShaderRenderNode.h
//  GPUPower
//
//  Created by lingtonke on 2018/10/9.
//  Copyright © 2018 tencent. All rights reserved.
//
#include "GLRenderNode.h"
#include "../GLProgram.h"
#include <memory>
namespace GPUPower
{
    using namespace std;
    class GLCustomShaderRenderNode:public GLRenderNode
    {
    protected:
        shared_ptr<GLProgram> program;
    public:
        GLCustomShaderRenderNode(shared_ptr<GLProgram> program);
        virtual shared_ptr<NodeChain::NodeResponse> process();
    };
};
