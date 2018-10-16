//
//  GLRenderNode.h
//  GPUPower
//
//  Created by lingtonke on 2018/10/9.
//  Copyright © 2018 tencent. All rights reserved.
//

#pragma once
#include "../../NodeChain/Node.h"
#include "../GLContext.h"
namespace GPUPower
{
    using namespace std;
    using namespace NodeChain;
    class GLRenderNode:public Node
    {
    protected:
        weak_ptr<GLContext> context;
        GLRenderNode();
    public:
        GLRenderNode(shared_ptr<GLContext> context)
        {
            this->context = context;
        }
    };
};
