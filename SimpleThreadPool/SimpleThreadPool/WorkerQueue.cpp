//
//  WorkerQueue.cpp
//  SimpleThreadPool
//
//  Created by housir on 2018/12/11.
//  Copyright © 2018年 housir. All rights reserved.
//

#include "WorkerQueue.h"

WorkerQueue::WorkerQueue(__UINT32 dwWorkerQueueSize)
:m_dwWorkerQueueSize(dwWorkerQueueSize)
,m_dwHeaderIndex(0)
,m_dwTailIndex(0)
,m_dwCount(0)
{
    (void)sem_init(&m_tFull, 0, 0);
    (void)sem_init(&m_tEmpty, 0, dwWorkerQueueSize);
    // m_tMutex = PTHREAD_MUTEX_INITIALIZER; // 静态分配（延迟分配资源），不需要释放
    if (pthread_mutex_init(&m_tMutex, NULL) != 0) //动态分配，析构时需要释放资源
    {
        printf("mutex init error\n");
    }
    
    m_vecWorker.reserve(dwWorkerQueueSize+1);
}

WorkerQueue::~WorkerQueue() 
{
    pthread_mutex_destroy(&m_tMutex);
    sem_destroy(&m_tFull);
    sem_destroy(&m_tEmpty);
    m_vecWorker.clear(); // 实际Worker对象资源由任务创建者释放
}

bool WorkerQueue::push(Worker *pWorker)
{
    sem_wait(&m_tEmpty); // 消耗空闲位置资源
    pthread_mutex_lock(&m_tMutex);
    
    m_vecWorker[m_dwTailIndex++] = pWorker;
    // 不需要处理 m_dwTailIndex 转了一圈 又等于 m_dwHeaderIndex 的情况
    m_dwTailIndex = (m_dwTailIndex >= m_dwWorkerQueueSize) ? 0 : m_dwTailIndex;
    ++m_dwCount;
    
    pthread_mutex_unlock(&m_tMutex);
    sem_post(&m_tFull);
    return true;
}

bool WorkerQueue::pop(Worker *pWorker)
{
    // 消耗资源
    sem_wait(&m_tFull);
    pthread_mutex_lock(&m_tMutex);
    
    m_vecWorker[m_dwHeaderIndex++] = pWorker;
    m_dwHeaderIndex = (m_dwHeaderIndex >= m_dwWorkerQueueSize) ? 0 : m_dwHeaderIndex;
    --m_dwCount;
    
    pthread_mutex_unlock(&m_tMutex);
    sem_post(&m_tEmpty);
    return true;
}



