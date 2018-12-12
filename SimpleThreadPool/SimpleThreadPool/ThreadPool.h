//
//  ThreadPool.h
//  SimpleThreadPool
//
//  Created by housir on 2018/12/11.
//  Copyright © 2018年 housir. All rights reserved.
//

#ifndef ThreadPool_h
#define ThreadPool_h

#include <stdio.h>
#include "commondefine.h"
#include "Worker.h"

class ThreadPool
{
public:
    ThreadPool(__UINT32 dwThreadPoolSize = MAX_THREAD_POOL_SIZE);
    ~ThreadPool();
    
    // 开始运行线程
    void start();
    
    // 从任务队列里获取任务
    // 消费者
    Worker* getWorker();
    
    // 分配任务
    bool assignWorker(Worker* pWorker);
    
    // 等待所有任务运行结束
    void join();
    
    // 杀死所有线程，释放资源
    void killall();
    
private:
    static void* threadProc(void* argv);
};

#endif /* ThreadPool_h */
