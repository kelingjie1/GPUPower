//
//  Node.cpp
//  GPUPower
//
//  Created by lingtonke on 2018/10/8.
//  Copyright © 2018 tencent. All rights reserved.
//

#include "Node.h"
#include <thread>

using namespace NodeChain;

map<int,shared_ptr<Node>>::iterator Node::findInputNode(shared_ptr<Node> node)
{
    auto it = find_if(inputNodes.begin(), inputNodes.end(), [&](const std::map<int,shared_ptr<Node>>::value_type item)
                      {
                          return item.second == node;
                      });
    return it;
}

void Node::addInput(shared_ptr<Node> node,int atIndex)
{
    inputNodes[atIndex] = node;
    node->outputNodes.push_back(shared_from_this());
}

void Node::removeInput(shared_ptr<Node> node)
{
    auto it = findInputNode(node);
    if (it != inputNodes.end())
    {
        inputNodes.erase(it);
        node->outputNodes.erase(find(node->outputNodes.begin(), node->outputNodes.end(), node));
    }
}

void Node::addOutput(shared_ptr<Node> node,int toIndex)
{
    node->addInput(shared_from_this(),toIndex);
}

void Node::removeOutput(shared_ptr<Node> node)
{
    node->removeInput(shared_from_this());
}

void Node::sendRequest(shared_ptr<NodeRequest> request)
{
    restResponseCount++;
    if (inputNodes.size() == 0)
    {
        sendResponse(NULL);
    }
    else
    {
        auto nextRequest = shared_ptr<NodeRequest>(new NodeRequest);
        nextRequest->previousRequest = request;
        nextRequest->node = shared_from_this();
        for(auto input : inputNodes)
        {
            input.second->sendRequest(nextRequest);
        }
    }
}

void Node::sendResponse(shared_ptr<NodeResponse> response)
{
    restResponseCount--;
    if (response.get())
    {
        auto it = findInputNode(response->node.lock());
        inputResponses[it->first] = response;
    }
    checkAndProcess();
}

void Node::checkAndProcess()
{
    if (inputResponses.size() == inputNodes.size())
    {
        auto response = process();
        for(auto output : outputNodes)
        {
            response->node = shared_from_this();
            output->sendResponse(response);
        }
    }
}

shared_ptr<NodeResponse> Node::process()
{
    return shared_ptr<NodeResponse>(new NodeResponse);
}
