//
//  ThreadVisitPrivateStack.cpp
//  CStudy
//
//  Created by housir on 2018/12/5.
//  Copyright © 2018年 housir. All rights reserved.
//
//  测试线程是否可以访问同进程下线程的栈空间

#include "ThreadVisitPrivateStack.h"

int *p = NULL;

pthread_cond_t  pcond  = PTHREAD_COND_INITIALIZER;
pthread_mutex_t pmutex = PTHREAD_MUTEX_INITIALIZER;

bool change = false;

void* thread1(void* args)
{
    // 阻塞，等待thread2将&a赋值给p
    pthread_mutex_lock(&pmutex);
    while(NULL == p)
    {
        printf("thread %d cond wait p become not NULL.\n", 1);
        pthread_cond_wait(&pcond, &pmutex);
    }
    pthread_mutex_unlock(&pmutex);
    
    *p = 2;
    printf("thread %d, change *p = %d.\n", 1, *p);
    
    // 通知thread2，*p已被修改
    pthread_mutex_lock(&pmutex);
    change = true;
    pthread_cond_signal(&pcond);
    pthread_mutex_unlock(&pmutex);
    return NULL;
}

void* thread2(void* args)
{
    int a = 1;
    printf("thread %d, a = %d.\n", 2, a);
    
    // 通知thread1，已将&a赋值给p
    pthread_mutex_lock(&pmutex);
    p = &a;
    printf("thread %d set p = &a.\n", 2);
    pthread_cond_signal(&pcond);
    pthread_mutex_unlock(&pmutex);
    
    // 阻塞，等待thread1将*p修改
    pthread_mutex_lock(&pmutex);
    while(!change)
    {
        printf("thread %d cond wait change become true.\n", 2);
        pthread_cond_wait(&pcond, &pmutex);
    }
    pthread_mutex_unlock(&pmutex);
    
    printf("thread %d, a = %d.\n", 2, a);
    if(a != 1)
    {
        printf("thread can access other thread's stack space.\n");
    }
    else
    {
        printf("thread can not access other thread's stack space.\n");
    }
    return NULL;
}

bool test()
{
    pthread_t        tid1;  // thread id
    if (0 != pthread_create(&tid1, NULL, thread1, NULL))
    {
        return false;
    }
    
    pthread_t        tid2;  // thread id
    if (0 != pthread_create(&tid2, NULL, thread2, NULL))
    {
        return false;
    }
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return true;
}
/***************************
 运行结果为：
 thread 2, a = 1.
 thread 1 cond wait p become not NULL.
 thread 2 set p = &a.
 thread 2 cond wait change become true.
 thread 1, change *p = 2.
 thread 2, a = 2.
 thread can access other thread's stack space.
***************************/

