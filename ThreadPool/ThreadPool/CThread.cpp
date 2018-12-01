//
//  CThread.cpp
//  ThreadPool
//
//  Created by housir on 2018/11/19.
//  Copyright © 2018年 housir. All rights reserved.
//

#include "CThread.h"
#include "CThreadPool.h"
#include <stdio.h>


CThread::CThread(CThreadPool* parent, __UINT32 dwIndex)
{
    m_dwIndex     = dwIndex;
    m_bCreate     = false;
    m_bExit       = false;
    m_eStatus     = THREAD_STATUS_UNCREATE;
    m_tid         = NULL;  // thread id
    m_pWorker     = NULL;
    //m_cond.pcond  = PTHREAD_COND_INITIALIZER;
    //m_cond.pmutex = PTHREAD_MUTEX_INITIALIZER;
    if (pthread_mutex_init(&m_cond.pmutex, NULL) != 0)
    {
        printf("mutex init error\n");
    }
    if (pthread_cond_init(&m_cond.pcond, NULL) != 0)
    {
        printf("cond init error\n");
    }
    m_parent = parent;
}

CThread::~CThread()
{
    exit();
}

bool CThread::create()
{
    // 创建线程，运行CWorker::run
    if (0 != pthread_create(&m_tid, NULL, stRun, this))
    {
        return false;
    }
    m_bCreate = true;
    m_eStatus = THREAD_STATUS_RUN;
    return true;
}

void* CThread::stRun(void* args)
{
    CThread * pThread = (CThread *)args;
    pThread->run();
    return 0;
}

void CThread::run()
{
    printf("thread %u start run.\n", m_dwIndex);
    while(!m_bExit)
    {
        pthread_mutex_lock(&m_cond.pmutex);
        while(NULL == m_pWorker && !m_bExit)
        {
            printf("thread %u cond wait.\n", m_dwIndex);
            pthread_cond_wait(&m_cond.pcond, &m_cond.pmutex);
        }
        pthread_mutex_unlock(&m_cond.pmutex);
        
        if(m_bExit)
        {
            break;
        }
        
        if(m_pWorker)
        {
            m_pWorker->run();
            printf("Thread %u complete a work.\n", m_dwIndex);
            
            // release worker
            m_pWorker = NULL;
            m_parent->lock();
            m_parent->moveThreadFromBusyToIdle(m_dwIndex);
            m_parent->unlock();
        }
    }
    m_eStatus = THREAD_STATUS_EXIT;
    printf("thread %u exit.\n", m_dwIndex);
}

void CThread::exit()
{
    m_bExit = true;
    resume();
    __UINT32 wait_times = 0;
    while(wait_times++ < EXIT_STATUS_MAX_CHECK_TIMES)
    {
        if(THREAD_STATUS_EXIT == m_eStatus)
        {
            break;
        }
    }
    if(THREAD_STATUS_EXIT != m_eStatus)
    {
        printf("thread %u force exit.\n", m_dwIndex);
    	force_exit();
    }
    //销毁互斥量和条件变量
    pthread_mutex_destroy(&m_cond.pmutex);
    pthread_cond_destroy(&m_cond.pcond);
}

void CThread::force_exit()
{
    // force kill thread
}

void CThread::resume()
{
    pthread_mutex_lock(&m_cond.pmutex);
    pthread_cond_signal(&m_cond.pcond);
    pthread_mutex_unlock(&m_cond.pmutex);
}

void CThread::join()
{
    //pthread_join(m_tid, NULL);
}

bool CThread::setWorker(CWorker *pWorker)
{
    if(NULL == m_pWorker && NULL != pWorker)
    {
        m_pWorker = pWorker;
        return true;
    }
    return false;
}
