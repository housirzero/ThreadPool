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

//封装一个互斥量和条件变量作为状态
typedef struct condition
{
    pthread_mutex_t pmutex;
    pthread_cond_t  pcond; // init = PTHREAD_COND_INITIALIZER
}condition_t;

enum enumThreadStatus
{
    THREAD_STATUS_UNCREATE,   // 未创建线程
    THREAD_STATUS_RUN,        // 正在运行（空闲或忙碌）
    THREAD_STATUS_EXIT        // 退出
};

const __UINT32 EXIT_STATUS_CHECK_TI = 10000; // 线程退出状态检查时间间隔
const __UINT32 EXIT_STATUS_MAX_CHECK_TIMES = 10; // 线程退出状态最大检查次数


class CThreadPool;
class CThread
{
public:
    CThread(CThreadPool* parent, __UINT32 dwIndex);
    ~CThread();
    
    static void* stRun(void* args);
    
    bool create();
    void run();
    void exit();
    void force_exit(); // 强制终止
    void resume();
    void join();

    bool isCreate() { return m_bCreate; }
    
    bool setWorker(CWorker* pWorker);

private:
    __UINT32         m_dwIndex;
    bool             m_bCreate;
    bool             m_bExit;
    enumThreadStatus m_eStatus;
    pthread_t        m_tid;  // thread id
    condition_t      m_cond;
    CWorker*         m_pWorker;
    CThreadPool*     m_parent;
};

#endif /* CThread_h */
