//
//  CWorker.h
//  ThreadPool
//
//  Created by housir on 2018/11/19.
//  Copyright © 2018年 housir. All rights reserved.
//

#ifndef CWorker_h
#define CWorker_h

class CWorker
{
public:
    CWorker() {};
    virtual ~CWorker(){};

    virtual void run() = 0;
};

#endif /* CWorker_h */
