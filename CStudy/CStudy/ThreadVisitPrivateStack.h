//
//  ThreadVisitPrivateStack.hpp
//  CStudy
//
//  Created by housir on 2018/12/5.
//  Copyright © 2018年 housir. All rights reserved.
//

#ifndef __THREAD_VISIT_PRIVATE_STACK_H__
#define __THREAD_VISIT_PRIVATE_STACK_H__

#include <stdio.h>
#include <pthread.h>

void* thread1(void* args);

void* thread2(void* args);

bool test();

#endif /* __THREAD_VISIT_PRIVATE_STACK_H__ */
