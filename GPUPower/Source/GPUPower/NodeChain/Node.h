//
//  Node.h
//  GPUPower
//
//  Created by lingtonke on 2018/10/8.
//  Copyright © 2018 tencent. All rights reserved.
//
#pragma once

#include "NodeData.h"
#include <vector>
#include <map>

namespace NodeChain
{
    using namespace std;
    class Node:enable_shared_from_this<Node>
    {
    protected:
        int restResponseCount;
        map<int,shared_ptr<Node>> inputNodes;
        map<int,shared_ptr<NodeResponse>> inputResponses;
        vector<shared_ptr<Node>> outputNodes;
        map<int,shared_ptr<Node>>::iterator findInputNode(shared_ptr<Node> node);
    public:
        bool holdInputResponsesAfterProcess;
        virtual void addInput(shared_ptr<Node> node,int atIndex=-1);
        virtual void removeInput(shared_ptr<Node> node);
        virtual void addOutput(shared_ptr<Node> node,int toIndex=-1);
        virtual void removeOutput(shared_ptr<Node> node);
        
        virtual void sendRequest(shared_ptr<NodeRequest> request);
        virtual void sendResponse(shared_ptr<NodeResponse> response);
        
        virtual shared_ptr<NodeResponse> process();
        virtual void checkAndProcess();
    };
};
