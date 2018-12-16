//
//  ThreadPoolMng.cpp
//  SimpleThreadPool
//
//  Created by housir on 2018/12/11.
//  Copyright © 2018年 housir. All rights reserved.
//

#include "ThreadPoolMng.h"

//ThreadPoolMng* ThreadPoolMng::ms_pSelf = NULL;
ThreadPoolMng ThreadPoolMng::ms_self;

ThreadPoolMng::ThreadPoolMng()
{
}

ThreadPoolMng::~ThreadPoolMng() 
{
    if(m_pThreadPool)
    {
        delete m_pThreadPool;
    }
    if(m_pWorkerQueue)
    {
        delete m_pWorkerQueue;
    }
}

ThreadPoolMng* ThreadPoolMng::getInstance()
{
    return &ms_self;
}

void ThreadPoolMng::init(__UINT32 dwThreadPoolSize, __UINT32 dwWorkerQueueSize)
{
    if(NULL == m_pThreadPool)
    {
        m_pThreadPool = new ThreadPool(dwThreadPoolSize);
        m_pThreadPool->registerMng(this);
    }
    
    if(NULL == m_pWorkerQueue)
    {
        m_pWorkerQueue = new WorkerQueue(dwWorkerQueueSize);
    }
}

void ThreadPoolMng::start()
{
    m_pThreadPool->start();
}

bool ThreadPoolMng::addWorker(Worker *pWorker)
{
    return m_pWorkerQueue->push(pWorker);
}

void ThreadPoolMng::join()
{
    m_pThreadPool->join();
}
