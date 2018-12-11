//
//  WorkerQueue.h
//  SimpleThreadPool
//
//  Created by housir on 2018/12/11.
//  Copyright © 2018年 housir. All rights reserved.
//

#ifndef WorkerQueue_h
#define WorkerQueue_h

#include <stdio.h>
#include "commondefine.h"
#include "Worker.h"


class WorkerQueue
{
public:
    WorkerQueue(__UINT32 dwWorkerQueueSize = MAX_WORKER_QUEUE_SIZE);
    ~WorkerQueue();
    
    // 添加任务
    bool push(Worker* pWorker);
    
    // 取出任务
    bool pop(Worker* pWorker);
    
    bool isEmpty();
    
    // 获取当前队列中的任务数
    __UINT32 getCount();
    
protected:
    
private:
    
};

#endif /* WorkerQueue_h */
