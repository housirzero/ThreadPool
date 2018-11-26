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
    for(__UINT32 i = 0; i < dwThreadNum; ++i)
    {
        CThread* pThread = new CThread(this, i);
        m_vecAllThreads.push_back(pThread);
        m_listIdleThreads.push_back(i);
    }
}

CThreadPool::~CThreadPool()
{
    while(!m_listBusyThreads.empty()) // 还有线程正在运行
    {
        // 需要发送停止信号，并等待所有线程停止(需要研究一下pthread_kill)
        usleep(10000); // 10 ms
    }
    
    list<__UINT32>::iterator it = m_listIdleThreads.begin();
    for(; it != m_listIdleThreads.end(); ++it)
    {
        CThread* pThread = m_vecAllThreads[*it];
        delete pThread;
    }
    m_listIdleThreads.clear();
}

__UINT32 CThreadPool::getIdleThreadIndex()
{
    if(m_listIdleThreads.empty())
    {
        return -1;
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

void CThreadPool::join()
{
    printf("start join ...\n");
    __UINT32 dwThreadNum = m_vecAllThreads.size();
    for(__UINT32 i = 0; i < dwThreadNum; ++i)
    {
        m_vecAllThreads[i]->join();
    }
}

void CThreadPool::moveThreadFromIdleToBusy(__UINT32 dwIndex)
{
    m_listIdleThreads.remove(dwIndex);
    m_listBusyThreads.push_front(dwIndex);
}

void CThreadPool::moveThreadFromBusyToIdle(__UINT32 dwIndex)
{
    m_listBusyThreads.remove(dwIndex);
    m_listIdleThreads.push_front(dwIndex);
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
        list<__UINT32>::iterator it = m_listIdleThreads.begin();
        CThread* pThread = m_vecAllThreads[*it]; // *it is index
        
        // set worker
        if(pThread->setWorker(pWorker))
        {
            moveThreadFromIdleToBusy(*it);
            
            if(pThread->isCreate())
            {
            	// start run
            	pThread->resume();
            }
            else
            {
                pThread->create();
            }
            ret = true;
        }

    }
    unlock();
    return ret;
}






