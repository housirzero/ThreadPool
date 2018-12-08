//
//  Singleton.hpp
//  CStudy
//
//  Created by housir on 2018/12/8.
//  Copyright © 2018年 housir. All rights reserved.
//

#ifndef Singleton_h
#define Singleton_h

#include <stdio.h>
#include <pthread.h>

#define LAZE_MODE

// 保证一个类仅有一个实例，并提供一个访问它的全局访问点。
class Singleton  
{  
public:  
    Singleton();
    ~Singleton();
    
    bool isOk() {return true;};
    
    static Singleton* getInstance();
    
    static void test();
    
    static void release();
      
protected:  
      
private:
#ifdef LAZE_MODE
    static pthread_mutex_t pmutex; // = PTHREAD_MUTEX_INITIALIZER;
    static Singleton* singleton;
#else
    static Singleton singleton;
#endif
      
}; 

#endif /* Singleton_h */
