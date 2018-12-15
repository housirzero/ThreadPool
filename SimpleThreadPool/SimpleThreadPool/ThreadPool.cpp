//
//  ThreadPool.cpp
//  SimpleThreadPool
//
//  Created by housir on 2018/12/11.
//  Copyright © 2018年 housir. All rights reserved.
//

#include "ThreadPool.h"
#include "ThreadPoolMng.h"

ThreadPool::ThreadPool(__UINT32 dwThreadPoolSize)
:m_dwThreadPoolSize(dwThreadPoolSize)
,m_pMng(NULL)
,m_bExit(false)
{
    m_pThreadTArray = new pthread_t[m_dwThreadPoolSize];
    memset_s(m_pThreadTArray, sizeof(pthread_t)*m_dwThreadPoolSize, 0, sizeof(pthread_t)*m_dwThreadPoolSize);
}

ThreadPool::~ThreadPool()
{
    memset_s(m_pThreadTArray, sizeof(pthread_t)*m_dwThreadPoolSize, 0, sizeof(pthread_t)*m_dwThreadPoolSize);
}

void ThreadPool::registerMng(ThreadPoolMng *pMng)
{
    m_pMng = pMng;
}

void ThreadPool::start()
{
    for(__UINT32 i = 0; i < m_dwThreadPoolSize; ++i)
    {
        if (0 != pthread_create(&m_pThreadTArray[i], NULL, ThreadProc, this))
        {
            // create thread failed
            printf("create the %uth thread failed.\n", i+1);
        }
        printf("create the %uth thread success.\n", i+1);
    }
}

void* ThreadPool::ThreadProc(void *argv)
{
    // 调用保证argv不会为NULL
    ThreadPool* pSelf = (ThreadPool*)argv;
    while(!pSelf->m_bExit)
    {
        if(!pSelf->m_pMng)
        {
            printf("m_pMng is NULL.\n");
            return NULL;
        }
        Worker *pWorker = NULL;
        pSelf->m_pMng->getTopAndPop(&pWorker);
        
        // run worker
        if(pSelf->m_pMng->getTopAndPop(&pWorker) && NULL != pWorker)
        {
            pWorker->run();
        }

        // look if need exit
    }
    return NULL;
}
