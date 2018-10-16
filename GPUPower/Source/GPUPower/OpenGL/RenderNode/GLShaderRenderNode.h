//
//  GLShaderRenderNode.h
//  GPUPower
//
//  Created by lingtonke on 2018/10/9.
//  Copyright © 2018 tencent. All rights reserved.
//
#include "GLRenderNode.h"
#include "../GLProgram.h"
#include "../GLVertexArray.h"
#include <memory>
namespace GPUPower
{
    using namespace std;
    class GLShaderRenderNode:public GLRenderNode
    {
    public:
        GLShaderRenderNode(shared_ptr<GLContext> context):GLRenderNode(context){}
        shared_ptr<GLProgram> program;
        virtual shared_ptr<NodeChain::NodeResponse> process()
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
    };
};
