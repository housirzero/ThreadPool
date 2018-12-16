//
//  Worker.h
//  SimpleThreadPool
//
//  Created by housir on 2018/12/11.
//  Copyright © 2018年 housir. All rights reserved.
//

#ifndef Worker_h
#define Worker_h

class Worker
{
public:
    Worker(){};
    virtual ~Worker() {};
    
    // 运行任务的接口
    virtual void run() = 0;
};

#endif /* Worker_h */
