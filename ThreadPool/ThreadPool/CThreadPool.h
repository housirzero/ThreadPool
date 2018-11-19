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
    CThreadPool(){};
    ~CThreadPool(){};
    
private:
    __UINT32 m_dwThreadsNum;
    list<CThread> m_listIdleThreads; // 空闲线程队列
    list<CThread> m_listBusyThreads;
};

#endif /* CThreadPool_h */
