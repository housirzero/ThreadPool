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
#include <vector>
#include "commondefine.h"
#include "CThread.h"
using namespace std;

class CThreadPool
{
public:
    CThreadPool(__UINT32 dwThreadNum);
    ~CThreadPool();
    
    __UINT32 getIdleThreadIndex();
    __UINT32 getIdleThreadNum();
    
    bool assignWork(CWorker * pWorker);
    void releaseWork();
    
    void moveThreadFromIdleToBusy(__UINT32 dwIndex);
    void moveThreadFromBusyToIdle(__UINT32 dwIndex);
    
    void lock();
    void unlock();
    void join();
    
private:
    vector<CThread *> m_vecAllThreads;
    list<__UINT32> m_listIdleThreads; // 空闲线程队列
    list<__UINT32> m_listBusyThreads;
    pthread_mutex_t m_pmutex; // 锁
};

#endif /* CThreadPool_h */
