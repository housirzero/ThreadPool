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
#include "commondefine.h"

enum enumThreadStatus
{
    THREAD_STATUS_IDLE,   // 未分配任务
    THREAD_STATUS_START,  // 已分配任务，但未开始
    THREAD_STATUS_BUSY,   // 正在运行任务
    THREAD_STATUS_PAUSE   // 暂停
};

//封装一个互斥量和条件变量作为状态
typedef struct condition
{
    pthread_mutex_t pmutex;
    pthread_cond_t  pcond; // init = PTHREAD_COND_INITIALIZER
}condition_t;

class CThreadPool;
class CThread
{
public:
    CThread(CThreadPool* parent);
    ~CThread();
    
    /**
     create thread
     */
    bool create();
    void run();
    static void* stRun(void* args);
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
    enumThreadStatus m_enumStatus;
    condition_t      m_cond;
    CThreadPool*     m_parent;
};

#endif /* CThread_h */
