//
//  MyWorker.h
//  CStudy
//
//  Created by housir on 2018/12/9.
//  Copyright © 2018年 housir. All rights reserved.
//

#ifndef MyWorker_h
#define MyWorker_h

#include <stdio.h>
#include "Worker.h"

class MyWorker: public Worker
{  
public:  
    MyWorker();  
    ~MyWorker();
    
    void run();      
}; 

#endif /* MyWorker_h */
