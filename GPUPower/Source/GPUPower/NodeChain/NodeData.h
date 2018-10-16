//
//  NodeData.h
//  GPUPower
//
//  Created by lingtonke on 2018/10/8.
//  Copyright © 2018 tencent. All rights reserved.
//

#pragma once
#include <memory>

namespace NodeChain
{
    using namespace std;
    class Node;
    class NodeData
    {
    public:
        weak_ptr<Node> node;
        virtual ~NodeData(){}
    };
    
    class NodeRequest:public NodeData
    {
    public:
        shared_ptr<NodeRequest> previousRequest;
        virtual ~NodeRequest(){}
    };
    
    class NodeResponse:public NodeData
    {
    public:
        virtual ~NodeResponse(){}
    };
};
