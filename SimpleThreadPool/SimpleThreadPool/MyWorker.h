//
//  MyWorker.h
//  SimpleThreadPool
//
//  Created by housir on 2018/12/16.
//  Copyright © 2018年 housir. All rights reserved.
//

#ifndef MyWorker_h
#define MyWorker_h

#include <stdio.h>
#include "commondefine.h"
#include "Worker.h"

class MyWorker: public Worker
{
public:
    MyWorker(__UINT32 dwFibNum);
    ~MyWorker();
    
    void run();
    
    // 构造一个耗时程序
    __UINT32 calcFibonacci(__UINT32 n);
protected:
    
private:
    __UINT32 m_dwFibNum;
    
};

#endif /* MyWorker_h */
