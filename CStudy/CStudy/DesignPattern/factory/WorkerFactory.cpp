//
//  WorkerFactory.cpp
//  CStudy
//
//  Created by housir on 2018/12/9.
//  Copyright © 2018年 housir. All rights reserved.
//

#include "WorkerFactory.h"
#include "MyWorker.h"
#include "MyWorkerOne.h"

WorkerFactory::WorkerFactory()
{
    
}

WorkerFactory::~WorkerFactory() 
{
         
}

Worker* WorkerFactory::getWorker(EWorkerType type)
{
    Worker* pWorker = NULL;
    switch(type)
    {
        case E_TYPE_MYWORKER:
            pWorker = new MyWorker();
            printf("new MyWorker success.\n");
            break;
        case E_TYPE_MYWORKER_ONE:
            pWorker = new MyWorkerOne();
            printf("new MyWorkerOne success.\n");
            break;
        default:
            printf("type %d not exist.\n", type);
            break;
    }
    return pWorker;
}


void WorkerFactory::test()
{
    // 将相关函数改为静态方法，就不需要创建工厂类对象了
    // WorkerFactory factory;
    Worker* pWorker1 = WorkerFactory::getWorker(E_TYPE_MYWORKER);
    if(pWorker1) pWorker1->run();
    Worker* pWorker2 = WorkerFactory::getWorker(E_TYPE_MYWORKER_ONE);
    if(pWorker2) pWorker2->run();
    Worker* pWorker3 = WorkerFactory::getWorker((EWorkerType)10);
    if(pWorker3) pWorker3->run();
    
    delete pWorker1;
    delete pWorker2;
    delete pWorker3;
}

