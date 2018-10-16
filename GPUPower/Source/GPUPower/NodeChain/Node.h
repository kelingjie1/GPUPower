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
#include "../Error.h"

namespace NodeChain
{
    using namespace std;
    using namespace GPUPower;
    class Node:public enable_shared_from_this<Node>
    {
    protected:
        
        int restResponseCount;
        map<int,shared_ptr<Node>> inputNodes;
        map<int,shared_ptr<NodeResponse>> inputResponses;
        vector<shared_ptr<Node>> outputNodes;
        map<int,shared_ptr<Node>>::iterator findInputNode(shared_ptr<Node> node)
        {
            auto it = find_if(inputNodes.begin(), inputNodes.end(), [&](const std::map<int,shared_ptr<Node>>::value_type item)
                              {
                                  return item.second == node;
                              });
            return it;
        }
    public:
        bool holdInputResponsesAfterProcess;
        
        virtual void addInput(shared_ptr<Node> node,int atIndex)
        {
            inputNodes[atIndex] = node;
            auto t = shared_from_this();
            node->outputNodes.push_back(t);
        }
        
        virtual void removeInput(shared_ptr<Node> node)
        {
            auto it = findInputNode(node);
            if (it != inputNodes.end())
            {
                inputNodes.erase(it);
                node->outputNodes.erase(find(node->outputNodes.begin(), node->outputNodes.end(), node));
            }
            else
            {
                throw Error(GPUPowerError_InputNodeNotFound);
            }
        }
        
        virtual void removeAllInputs()
        {
            for (auto &pair: inputNodes)
            {
                auto node = pair.second;
                node->outputNodes.erase(find(node->outputNodes.begin(), node->outputNodes.end(), node));
            }
            inputNodes.clear();
        }
        
        virtual void addOutput(shared_ptr<Node> node,int toIndex)
        {
            node->addInput(shared_from_this(),toIndex);
        }
        
        virtual void removeOutput(shared_ptr<Node> node)
        {
            node->removeInput(shared_from_this());
        }
        
        virtual void removeAllOutputs()
        {
            for (auto &node: outputNodes)
            {
                node->inputNodes.erase(node->findInputNode(shared_from_this()));
            }
            outputNodes.clear();
        }
        
        virtual void sendRequest(shared_ptr<NodeRequest> request)
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
        
        virtual void sendResponse(shared_ptr<NodeResponse> response)
        {
            restResponseCount--;
            if (response.get())
            {
                auto it = findInputNode(response->node.lock());
                inputResponses[it->first] = response;
                
            }
            checkAndProcess();
        }
        
        virtual void checkAndProcess()
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
        
        virtual shared_ptr<NodeResponse> process()
        {
            return shared_ptr<NodeResponse>(new NodeResponse);
        }
        
        map<int,shared_ptr<NodeResponse>> getInputResponses()
        {
            return inputResponses;
        }
    };
};
