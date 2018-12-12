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
#include <semaphore.h>
#include <pthread.h>
#include <vector>
using namespace std;


class WorkerQueue
{
public:
    WorkerQueue(__UINT32 dwWorkerQueueSize = MAX_WORKER_QUEUE_SIZE);
    ~WorkerQueue();
    
    // 添加任务
    bool push(Worker* pWorker);
    
    // 取出任务
    bool pop(Worker* pWorker);
    
    bool isEmpty() { return 0 == m_dwCount; }
    
    // 获取当前队列中的任务数
    __UINT32 getCount() { return m_dwCount; }
    
protected:
    
private:
    __UINT32 m_dwWorkerQueueSize; // 队列大小
    sem_t    m_tFull;  // 队列已使用空间
    sem_t    m_tEmpty; // 队列剩余空间
    pthread_mutex_t m_tMutex; // 互斥，防止两个以上的对象同时操作队列
    
    vector<Worker*> m_vecWorker;
    __UINT32        m_dwHeaderIndex;
    __UINT32        m_dwTailIndex;
    __UINT32        m_dwCount;
};

#endif /* WorkerQueue_h */
