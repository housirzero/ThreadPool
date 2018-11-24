//
//  CThreadPool.h
//  CThreadPool
//
//  Created by housir on 2018/11/19.
//  Copyright © 2018年 housir. All rights reserved.
//

#ifndef CThreadPool_h
#define CThreadPool_h
#include <list>
#include "commondefine.h"
#include "CThread.h"
using namespace std;

class CThreadPool
{
public:
    CThreadPool(__UINT32 dwThreadNum);
    ~CThreadPool();
    
    CThread* getIdleThread();
    __UINT32 getIdleThreadNum();
    
    bool assignWork(CWorker * pWorker);
    void releaseWork();
    
    void lock();
    void unlock();
    
private:
    __UINT32 m_dwThreadNum;
    __UINT32 m_dwIdleThreadNum;
    list<CThread *> m_listIdleThreads; // 空闲线程队列
    list<CThread *> m_listBusyThreads;
    pthread_mutex_t m_pmutex; // 锁
};

#endif /* CThreadPool_h */
