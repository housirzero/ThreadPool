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
#include "WorkerQueue.h"
#include "ThreadPool.h"

class ThreadPoolMng
{
public:
    ThreadPoolMng();
    ~ThreadPoolMng();
    
    static ThreadPoolMng* getInstance();
    
    // 初始化线程池和任务队列
    void init(__UINT32 dwThreadPoolSize = MAX_THREAD_POOL_SIZE, __UINT32 dwWorkerQueueSize = MAX_WORKER_QUEUE_SIZE);
    
    ThreadPool* getThreadPool() {return m_pThreadPool;}
    
    WorkerQueue* getWorkerQueue() {return m_pWorkerQueue;}
    
    // 系统开始运转
    void start();
    
    // 添加任务
    // 生产者
    bool addWorker(Worker* pWorker);
    
    bool getTopAndPop(Worker** ppWorker)
    {
        return m_pWorkerQueue->getTopAndPop(ppWorker);
    }
    
    void setExit() { m_pThreadPool->setExit(); }
    
    // 释放资源
    void release();
    
    // 等待所有任务运行结束
    void join();
    
protected:
    
private:
    //static ThreadPoolMng* ms_pSelf;
    static ThreadPoolMng ms_self;
    ThreadPool*  m_pThreadPool;
    WorkerQueue* m_pWorkerQueue;
    
    __UINT32 m_dwThreadPoolSize;
    __UINT32 m_dwWorkerQueueSize;
};

#endif /* ThreadPoolMng_h */
