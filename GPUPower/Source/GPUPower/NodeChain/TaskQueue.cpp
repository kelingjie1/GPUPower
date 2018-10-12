//
//  TaskQueue.cpp
//  GPUPower
//
//  Created by lingtonke on 2018/10/9.
//  Copyright © 2018 tencent. All rights reserved.
//

#include "TaskQueue.h"
using namespace NodeChain;

void TaskQueue::addTask(std::function<void ()> func)
{
    queue.push(func);
}

void TaskQueue::start(std::function<void ()> startfunc)
{
    isStoped = false;
    thread = std::thread([=](){
        if (startfunc)
        {
            startfunc();
        }
        std::function<void ()> func;
        while (!isStoped)
        {
            queue.wait_and_pop(func);
            func();
        }
    });
}

void TaskQueue::stop()
{
    isStoped = true;
}

