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
#include <pthread.h>
#include "Worker.h"
#include <list>

class ThreadPoolMng;
class ThreadPool
{
public:
    ThreadPool(__UINT32 dwThreadPoolSize = MAX_THREAD_POOL_SIZE);
    ~ThreadPool();
    
    void registerMng(ThreadPoolMng* pMng);
    
    // 开始运行线程
    void start();
    
    // 从任务队列里获取任务
    // 消费者
    Worker* getWorker();
    
    // 分配任务
    bool assignWorker(Worker* pWorker);
    
    __UINT32 getBusyThreadNum() { return m_dwBusyThreadNum; }
    
    // 设置退出标志，准备退出
    void setExit() { m_bExit = true; };
    
    // 设置退出标志后，正在执行的任务不会被打断
    // 所以这里需要等待所有任务运行结束
    void join();
    
    // 杀死所有线程，释放资源
    void killall();
    
private:
    static void* ThreadProc(void* argv);
    bool         m_bExit; // 上层设置退出标志
    
    ThreadPoolMng* m_pMng;
    __UINT32 m_dwThreadPoolSize;
    __UINT32 m_dwBusyThreadNum; // 当前正在执行任务的线程（其他线程没有获取到任务，或者已经退出）
    pthread_mutex_t m_tMutex; // 互斥，防止两个以上的线程同时修改m_dwBusyThreadNum
    
    std::list<pthread_t*> m_lstIdleThreadId;
    std::list<pthread_t*> m_lstBusyThreadId;
    
    pthread_t* m_pThreadTArray;
    
};

#endif /* ThreadPool_h */
