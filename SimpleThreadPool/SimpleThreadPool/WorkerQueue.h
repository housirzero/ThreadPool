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
#include <semaphore.h>
#include <pthread.h>
#include <vector>
#include <unistd.h>
#include "Worker.h"

// 每次try_wait后的等待时间间隔(0.1s)，毫秒
#define SEM_WAIT_MILLI_SECOND_TIME_INTIVAL 100
// sem_timedwait_macos 等待的默认时间(1s)，毫秒
#define DEFAULT_SEM_WAIT_MILLI_SECOND_TIME_OUT 1000

class WorkerQueue
{
public:
    WorkerQueue(__UINT32 dwWorkerQueueSize = MAX_WORKER_QUEUE_SIZE);
    
    ~WorkerQueue();
    
    // 添加任务
    bool push(Worker* pWorker);
    
    // 简易模拟sem_timedwait
    // dwWaitTime: 单位微秒
    int sem_timedwait_macos(sem_t *sem, __UINT32 dwWaitTime);
    
    // 取出任务并弹出(set NULL)
    // 记录的是地址，取出时已经返回，所以弹出不影响其他地方使用
    bool getTopAndPop(Worker** ppWorker);
    
    bool empty() { return 0 == m_dwCount; }
    
    // 获取当前队列中的任务数
    __UINT32 getCount() { return m_dwCount; }
    
protected:
    
private:
    __UINT32 m_dwWorkerQueueSize; // 队列大小
    sem_t*    m_pSemFull;  // 队列已使用空间
    sem_t*    m_pSemEmpty; // 队列剩余空间
    pthread_mutex_t m_tMutex; // 互斥，防止两个以上的对象同时操作队列
    
    std::vector<Worker*> m_vecWorker;
    __UINT32        m_dwHeaderIndex;
    __UINT32        m_dwTailIndex;
    __UINT32        m_dwCount;
};

#endif /* WorkerQueue_h */
