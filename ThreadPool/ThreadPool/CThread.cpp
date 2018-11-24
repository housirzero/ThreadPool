//
//  CThread.cpp
//  ThreadPool
//
//  Created by housir on 2018/11/19.
//  Copyright © 2018年 housir. All rights reserved.
//

#include "CThread.h"
#include <stdio.h>


CThread::CThread(CThreadPool* parent)
{
    m_tid         = NULL;  // thread id
    m_pWorker     = NULL;
    m_enumStatus  = THREAD_STATUS_IDLE;
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
    
}

bool CThread::create()
{
    // 创建线程
    // 运行CWorker::run
    if (0 != pthread_create(&m_tid, NULL, stRun, this))
    {
        return false;
    }
    
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
    while(true)
    {
        pthread_mutex_lock(&m_cond.pmutex);
        while(NULL == m_pWorker)
        {
            pthread_cond_wait(&m_cond.pcond, &m_cond.pmutex);
        }
        pthread_mutex_unlock(&m_cond.pmutex);
        
        if(m_pWorker)
        {
            m_enumStatus = THREAD_STATUS_BUSY;
            m_pWorker->run();
            printf("Thread %llu complete a work.\n", (unsigned long long)m_tid);
            
            // release worker
            m_pWorker = NULL;
            // turn thread from busy to idle
            // how to do ????
            m_enumStatus = THREAD_STATUS_IDLE;
        }
    }
}


void CThread::kill()
{
    // kill thread
}

// 暂停执行，即使分配任务了也不执行
void CThread::pause()
{
}

void CThread::resume()
{
    pthread_mutex_lock(&m_cond.pmutex);
    pthread_cond_signal(&m_cond.pcond);
    pthread_mutex_unlock(&m_cond.pmutex);
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
