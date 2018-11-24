//
//  CThreadPool.cpp
//  ThreadPool
//
//  Created by housir on 2018/11/20.
//  Copyright © 2018年 housir. All rights reserved.
//

#include "CThreadPool.h"
#include <unistd.h>


CThreadPool::CThreadPool(__UINT32 dwThreadNum)
{
    m_dwThreadNum = dwThreadNum;
    for(int i = 0; i < m_dwThreadNum; ++i)
    {
        CThread* pThread = new CThread(this);
        m_listIdleThreads.push_back(pThread);
    }
}

CThreadPool::~CThreadPool()
{
    while(!m_listBusyThreads.empty()) // 还有线程正在运行
    {
        // 需要发送停止信号，并等待所有线程停止(需要研究一下pthread_kill)
        usleep(10000); // 10 ms
    }
    
    list<CThread *>::iterator it = m_listIdleThreads.begin();
    for(; it != m_listIdleThreads.end(); ++it)
    {
        delete *it;
    }
    m_listIdleThreads.clear();
}

CThread* CThreadPool::getIdleThread()
{
    if(0 == m_dwIdleThreadNum)
    {
        return NULL;
    }
    return *(m_listIdleThreads.begin());
}

void CThreadPool::lock()
{
    pthread_mutex_lock(&m_pmutex);
}

void CThreadPool::unlock()
{
    pthread_mutex_unlock(&m_pmutex);
}

bool CThreadPool::assignWork(CWorker * pWorker)
{
    bool ret = false;
    // 若果任务分配实在多线程的情况下，这里要加上锁(锁m_listIdleThreads/m_listBusyThreads)
    // 暂时不考虑
    lock();
    if(m_listIdleThreads.size() > 0)
    {
        // get idle thread
        list<CThread *>::iterator it = m_listIdleThreads.begin();
        CThread* pThread = *it;
        
        // set worker
        if(pThread->setWorker(pWorker))
        {
            // turn thread from idle to busy
            // 需要看看下面两句那个删除效率高
            m_listIdleThreads.erase(it);
            //m_listIdleThreads.pop_front();
            
            m_listBusyThreads.push_front(pThread);
            
            // start run
            pThread->resume();
            ret = true;
        }

    }
    unlock();
    return ret;
}






