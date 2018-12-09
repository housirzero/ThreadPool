//
//  WorkerFactory.h
//  CStudy
//
//  Created by housir on 2018/12/9.
//  Copyright © 2018年 housir. All rights reserved.
//

#ifndef WorkerFactory_h
#define WorkerFactory_h

#include <stdio.h>
#include "Worker.h"

enum EWorkerType
{
    E_TYPE_MIN = 0,
    E_TYPE_MYWORKER = E_TYPE_MIN,
    E_TYPE_MYWORKER_ONE,
    E_TYPE_MAX = E_TYPE_MYWORKER_ONE
};

class WorkerFactory  
{  
public:  
    WorkerFactory();
    ~WorkerFactory();
    
    static Worker* getWorker(EWorkerType type);
    
    static void test();
      
protected:  
      
private:  
      
}; 

#endif /* WorkerFactory_h */
