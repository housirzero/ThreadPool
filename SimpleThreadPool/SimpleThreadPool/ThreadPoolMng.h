//
//  ThreadPoolMng.h
//  SimpleThreadPool
//
//  Created by housir on 2018/12/11.
//  Copyright © 2018年 housir. All rights reserved.
//

#ifndef ThreadPoolMng_h
#define ThreadPoolMng_h

#include <stdio.h>
#include "commondefine.h"
#include "Worker.h"
#include "ThreadPool.h"
#include "WorkerQueue.h"

class ThreadPoolMng
{
public:
    ThreadPoolMng();
    ~ThreadPoolMng();
    
    // 初始化线程池和任务队列
    void init(__UINT32 dwThreadPoolSize = MAX_THREAD_POOL_SIZE, __UINT32 dwWorkerQueueSize = MAX_WORKER_QUEUE_SIZE);
    
    // 系统开始运转
    void start();
    
    // 添加任务
    bool addWorker(Worker pWorker);
    
    // 释放资源
    void release();
    
    // 等待所有任务运行结束
    void join();
    
protected:
    
private:
    static ThreadPoolMng* ms_pSelf;
    ThreadPool*  m_pThreadPool;
    WorkerQueue* m_pWorkerQueue;
    
    __UINT32 m_dwThreadPoolSize;
    __UINT32 m_dwWorkerQueueSize;
};

#endif /* ThreadPoolMng_h */
