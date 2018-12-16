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
,m_dwBusyThreadNum(0)
{
    if (pthread_mutex_init(&m_tMutex, NULL) != 0) //动态分配，析构时需要释放资源
    {
        printf("mutex init error\n");
    }

    m_pThreadTArray = new pthread_t[m_dwThreadPoolSize];
    for(int i = 0; i < m_dwThreadPoolSize; ++i)
    {
        m_pThreadTArray[i] = NULL;
    }
}

ThreadPool::~ThreadPool()
{
    pthread_mutex_destroy(&m_tMutex);
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
    m_dwBusyThreadNum = 0;
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
        
        // run worker
        if(pSelf->m_pMng->getTopAndPop(&pWorker) && NULL != pWorker)
        {
            pthread_mutex_lock(&pSelf->m_tMutex);
            ++pSelf->m_dwBusyThreadNum;
            pthread_mutex_unlock(&pSelf->m_tMutex);
            
            pWorker->run();
            
            pthread_mutex_lock(&pSelf->m_tMutex);
            --pSelf->m_dwBusyThreadNum;
            pthread_mutex_unlock(&pSelf->m_tMutex);
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




