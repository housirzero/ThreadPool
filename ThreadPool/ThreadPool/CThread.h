//
//  CThread.h
//  ThreadPool
//
//  Created by housir on 2018/11/19.
//  Copyright © 2018年 housir. All rights reserved.
//

#ifndef CThread_h
#define CThread_h

#include <pthread.h>
#include "CWorker.h"

enum enumThreadStatus
{
    THREAD_STATUS_IDLE = 0,
    THREAD_STATUS_BUSY
};

class CThread
{
public:
    CThread();
    ~CThread();
    
    /**
     create and start thread
     */
    void start();
    void kill();
    
    /**
     pause thread
     */
    void pause();
    void resume();
    
    bool setWorker(CWorker* pWorker);

private:
    pthread_t        m_tid;  // thread id
    CWorker*         m_pWorker;
    pthread_mutex_t  m_mutex;
    enumThreadStatus m_enumStatus;
    pthread_cond_t   m_cond; // init = PTHREAD_COND_INITIALIZER;
};

#endif /* CThread_h */
