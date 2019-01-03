//
//  SupportTool.cpp
//  SimpleThreadPool
//
//  Created by housir on 2019/1/3.
//  Copyright © 2019年 housir. All rights reserved.
//

#include "SupportTool.h"
#include <sys/select.h>

SupportTool::SupportTool()
{
}

SupportTool::~SupportTool() 
{
}

void SupportTool::idle(__UINT32 dwMilliSecond)
{
    struct timeval timeout;
    timeout.tv_sec = dwMilliSecond / 1000;
    timeout.tv_usec = (dwMilliSecond % 1000) * 1000;
    select(0, NULL, NULL, NULL, &timeout);
}

