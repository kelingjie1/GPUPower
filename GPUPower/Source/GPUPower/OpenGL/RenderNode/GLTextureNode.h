//
//  GLTextureNode.h
//  GPUPower
//
//  Created by lingtonke on 2018/10/16.
//  Copyright © 2018 tencent. All rights reserved.
//

#pragma once

#include "GLRenderNode.h"
#include "../GLProgram.h"
#include "../GLTexture.h"
#include "../GLVertexArray.h"
#include <memory>

namespace GPUPower
{
    using namespace std;
    class GLTextureNode:public GLRenderNode
    {
        shared_ptr<GLRenderResponse> response;
    public:
        shared_ptr<GLTexture> texture;
        GLTextureNode(shared_ptr<GLContext> context):GLRenderNode(context)
        {
            response = shared_ptr<GLRenderResponse>(new GLRenderResponse);
            response->texture = texture;
        }
        virtual shared_ptr<NodeResponse> process()
        {
            return response;
        }
    };
}
