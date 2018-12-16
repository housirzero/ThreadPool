//
//  WorkerQueue.cpp
//  SimpleThreadPool
//
//  Created by housir on 2018/12/11.
//  Copyright © 2018年 housir. All rights reserved.
//

#include "WorkerQueue.h"

WorkerQueue::WorkerQueue(__UINT32 dwWorkerQueueSize)
:m_dwWorkerQueueSize(dwWorkerQueueSize)
,m_dwHeaderIndex(0)
,m_dwTailIndex(0)
,m_dwCount(0)
{
    // sem_init在mac中已经不被支持，创建总是失败
    //(void)sem_init(&m_tFull, 0, 0);
    //(void)sem_init(&m_tEmpty, 0, dwWorkerQueueSize);
    m_pSemFull = sem_open("m_pSemFull",O_CREAT, S_IRUSR | S_IWUSR, 0);
    if(NULL == m_pSemFull)
    {
        printf("sem_open m_pSemFull failed.\n");
    }
    m_pSemEmpty = sem_open("m_pSemEmpty",O_CREAT, S_IRUSR | S_IWUSR, dwWorkerQueueSize);
    if(NULL == m_pSemEmpty)
    {
        printf("sem_open m_pSemEmpty failed.\n");
    }

    // m_tMutex = PTHREAD_MUTEX_INITIALIZER; // 静态分配（延迟分配资源），不需要释放
    if (pthread_mutex_init(&m_tMutex, NULL) != 0) //动态分配，析构时需要释放资源
    {
        printf("mutex init error\n");
    }
    
    //m_vecWorker.reserve(dwWorkerQueueSize);
    for(int i = 0 ; i < dwWorkerQueueSize; ++i)
    {
        m_vecWorker.push_back(NULL);
    }
}

WorkerQueue::~WorkerQueue()
{
    pthread_mutex_destroy(&m_tMutex);
    // sem_destroy在mac中已经不被支持，创建总是失败
    //sem_destroy(&m_tFull);
    //sem_destroy(&m_tEmpty);
    sem_close(m_pSemFull);
    sem_unlink("m_pSemFull");
    sem_close(m_pSemEmpty);
    sem_unlink("m_pSemEmpty");
    m_vecWorker.clear(); // 实际Worker对象资源由任务创建者释放
}

bool WorkerQueue::push(Worker *pWorker)
{
    sem_wait(m_pSemEmpty); // 消耗空闲位置资源
    pthread_mutex_lock(&m_tMutex);
    
    m_vecWorker[m_dwTailIndex++] = pWorker;
    // 不需要处理 m_dwTailIndex 转了一圈 又等于 m_dwHeaderIndex 的情况
    m_dwTailIndex = (m_dwTailIndex >= m_dwWorkerQueueSize) ? 0 : m_dwTailIndex;
    ++m_dwCount;
    
    pthread_mutex_unlock(&m_tMutex);
    sem_post(m_pSemFull);
    return true;
}

/*
 * 基本思路：
 *     使用sem_trywait来判断信号量是否为0，在循环中通过休眠(usleep)进行等待
 *     直到超时或者信号量大于0
 * 存在问题：
 *     休眠会使当前线程失去被处理器调度的资格，1）等休眠过后再次被处理器调度，可能已经超超时
 *     2) 当有很多线程执行此操作时，可能有其它线程恰好得到sem的控制权，当前线程一直没等到，只能超时
 * 还可以参考Keith Shortridge的实现：
 *     https://github.com/housirzero/libxbee3/blob/master/xsys_darwin/sem_timedwait.c
 */
int WorkerQueue::sem_timedwait_macos(sem_t *sem, __UINT32 dwWaitTime)
{
    int ret = sem_trywait(sem);
    __UINT32 dwAlreadyWaitTime = dwWaitTime;
    // 等待时间小于SEM_WAIT_TIME_INTIVAL时，不再等待，直接返回
    while(0 != ret && dwAlreadyWaitTime > SEM_WAIT_TIME_INTIVAL)
    {
        usleep(SEM_WAIT_TIME_INTIVAL);
        dwAlreadyWaitTime -= SEM_WAIT_TIME_INTIVAL;
        ret = sem_trywait(sem);
    }
    return ret;
}

bool WorkerQueue::getTopAndPop(Worker** ppWorker)
{
    // 消耗资源
    //sem_wait(&m_tFull);
    // 使用超时机制，防止没有任务时一直等待，无法接收终止信号(整个进程需要终止时，push不需要考虑这种情况)
    if (0 != sem_timedwait_macos(m_pSemFull, DEFAULT_SEM_WAIT_TIME_OUT))
    {
        *ppWorker = NULL;
        return false;
    }
    
    pthread_mutex_lock(&m_tMutex);
    
    *ppWorker = m_vecWorker[m_dwHeaderIndex]; // get
    // pop
    m_vecWorker[m_dwHeaderIndex++] = NULL; // 具体资源的释放由上层处理
    m_dwHeaderIndex = (m_dwHeaderIndex >= m_dwWorkerQueueSize) ? 0 : m_dwHeaderIndex;
    --m_dwCount;
    
    pthread_mutex_unlock(&m_tMutex);
    sem_post(m_pSemEmpty);
    return true;
}



