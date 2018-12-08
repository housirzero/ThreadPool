//
//  Singleton.cpp
//  CStudy
//
//  Created by housir on 2018/12/8.
//  Copyright © 2018年 housir. All rights reserved.
//

#include "Singleton.h"

// 这里要带上数据的类型，但不能带static
#ifdef LAZE_MODE
pthread_mutex_t Singleton::pmutex = PTHREAD_MUTEX_INITIALIZER;
Singleton* Singleton::singleton = NULL;
// 也可以直接 Singleton* Singleton::singleton = new Singleton();
// 这样就是另一种形式的饿汉模式，使用后需要释放空间
#else
Singleton Singleton::singleton;
#endif
Singleton::Singleton()
{
    
}

Singleton::~Singleton() 
{
    
}

// 在类外实现是不能加static
Singleton* Singleton::getInstance()
{
#ifdef LAZE_MODE
    // 懒汉模式，双重检查锁，线程安全
    if(NULL == singleton)
    {
        pthread_mutex_lock(&pmutex);
        if(NULL == singleton)
        {
            singleton = new Singleton();
        }
        pthread_mutex_unlock(&pmutex);
    }
    return singleton;
#else
    // 饿汉模式
    return &singleton;
#endif
    // 除此之外还有一种通过内部静态变量的懒汉实现，和饿汉模式有相似之处，但又具有懒汉的特性
    /*
     pthread_mutex_lock(&pmutex);
     static Singleton singleton;
     pthread_mutex_unlock(&pmutex);
     return &singleton;
     */
}

void Singleton::test()
{
    if(NULL != getInstance() && getInstance()->isOk())
    {
#ifdef LAZE_MODE
        printf("getInstance success[LAZE_MODE].\n");
#else
        printf("getInstance success[HUNGRY_MODE].\n");
#endif
        release();
    }
}

void Singleton::release()
{
#ifdef LAZE_MODE
    // <懒汉模式，双重检查锁，线程安全> 才需要释放空间
    if(NULL != singleton)
    {
        pthread_mutex_lock(&pmutex);
        if(NULL != singleton)
        {
            delete singleton;
            singleton = NULL;
            printf("release singleton[LAZE_MODE].\n");
        }
        pthread_mutex_unlock(&pmutex);
    }
#endif
}



