//
//  GLRenderData.h
//  GPUPower
//
//  Created by lingtonke on 2018/10/9.
//  Copyright © 2018 tencent. All rights reserved.
//
#include "../../NodeChain/NodeData.h"
#include <memory>
namespace GPUPower
{
    using namespace std;
    class GLFrameBuffer;
    class GLTexture;
    class GLRenderData
    {
    public:
        shared_ptr<GLTexture> texture;
    };
    class GLRenderRequest:public NodeChain::NodeRequest,public GLRenderData
    {
    public:
        
    };
    
    class GLRenderResponse:public NodeChain::NodeResponse,public GLRenderData
    {
    public:
        
    };
};
