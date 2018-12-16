//
//  main.cpp
//  SimpleThreadPool
//
//  Created by housir on 2018/12/11.
//  Copyright © 2018年 housir. All rights reserved.
//

#include <iostream>
#include "ThreadPoolMng.h"
#include "MyWorker.h"
#include <unistd.h>
using namespace std;

#define WORKER_NUM 48

int main(int argc, const char * argv[]) {
    // insert code here...
    ThreadPoolMng* pMng = ThreadPoolMng::getInstance();
    
    pMng->init();
    pMng->start();
    
    // 开始添加任务
    Worker* pWorker[WORKER_NUM] = {NULL};
    for(int i = 0; i < WORKER_NUM; ++i)
    {
        pWorker[i] = new MyWorker(i);
        pMng->addWorker(pWorker[i]);
    }
    
    // 等待任务被取完
    while(!pMng->getWorkerQueue()->empty())
    {
        usleep(1000000);
    }
    for(int i = 0; i < 60; ++i)
    {
        printf("BusyThreadNum = %u.\n", pMng->getBusyThreadNum());
        usleep(1000000);
    }
    //usleep(60000000); // 观察线程没有任务时的状态
    // 设置退出标志，不影响正在运行的任务
    pMng->setExit();
    // 等待所有任务运行结束
    pMng->join();
    
    for(int i = 0; i < WORKER_NUM; ++i)
    {
        delete pWorker[i];
    }

    return 0;
}
