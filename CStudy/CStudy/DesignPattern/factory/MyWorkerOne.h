//
//  MyWorkerOne.h
//  CStudy
//
//  Created by housir on 2018/12/9.
//  Copyright © 2018年 housir. All rights reserved.
//

#ifndef MyWorkerOne_h
#define MyWorkerOne_h

#include <stdio.h>
#include "Worker.h"

class MyWorkerOne: public Worker
{  
public:  
    MyWorkerOne();  
    ~MyWorkerOne();
    
    void run();
}; 

#endif /* MyWorkerOne_h */
