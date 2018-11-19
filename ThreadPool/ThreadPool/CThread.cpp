//
//  CThread.cpp
//  ThreadPool
//
//  Created by housir on 2018/11/19.
//  Copyright © 2018年 housir. All rights reserved.
//

#include "CThread.h"

CThread::CThread()
{
    
}

CThread::~CThread()
{
    
}

void CThread::start()
{
    // 创建线程
    // 运行CWorker::run
}

void CThread::kill()
{
    // kill thread
}

void CThread::pause()
{
    
}

void CThread::resume()
{
    
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
