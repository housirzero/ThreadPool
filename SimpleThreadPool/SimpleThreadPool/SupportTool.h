//
//  SupportTool.h
//  SimpleThreadPool
//
//  Created by housir on 2019/1/3.
//  Copyright © 2019年 housir. All rights reserved.
//

#ifndef SupportTool_h
#define SupportTool_h

#include <stdio.h>
#include "commondefine.h"

class SupportTool
{
public:
    SupportTool();
    ~SupportTool();
    // 线程停顿一段时间,毫秒
    static void idle(__UINT32 dwMilliSecond);
    
protected:
    
private:
    
};

#endif /* SupportTool_h */
