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
    for(int i = 0; i < m_dwThreadPoolSize; ++i)
    {
        m_pThreadTArray[i] = NULL;
    }
}

ThreadPool::~ThreadPool()
{
    delete[] m_pThreadTArray;
    //m_pThreadTArray = NULL;
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
        bool bBusy = false;
        
        // run worker
        if(pSelf->m_pMng->getTopAndPop(&pWorker) && NULL != pWorker)
        {
            printf("thread is working...\n");
            pWorker->run();
            bBusy = true;
        }
        if(!bBusy)
        {
            printf("thread is idleing.\n");
        }
    }
    printf("thread exit.\n");
    return NULL;
}

void ThreadPool::join()
{
    for(__UINT32 i = 0; i < m_dwThreadPoolSize; ++i)
    {
        pthread_join(m_pThreadTArray[i], NULL);
    }
}




