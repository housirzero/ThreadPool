//
//  MyWorker.cpp
//  SimpleThreadPool
//
//  Created by housir on 2018/12/16.
//  Copyright © 2018年 housir. All rights reserved.
//

#include "MyWorker.h"

MyWorker::MyWorker(__UINT32 dwFibNum)
:m_dwFibNum(dwFibNum)
{
}

MyWorker::~MyWorker() 
{
}

void MyWorker::run()
{
    //printf("static calc fibonacci(%u).\n", m_dwFibNum);
    __UINT32 ret = calcFibonacci(m_dwFibNum);
    printf("fibonacci(%u) = %u.\n", m_dwFibNum, ret);
}

__UINT32 MyWorker::calcFibonacci(__UINT32 n)
{
    if(n == 0 || n == 1)
    {
        return 1;
    }
    else
    {
        return calcFibonacci(n - 1) + calcFibonacci(n - 2);
    }
}
