//
//  main.cpp
//  CStudy
//
//  Created by housir on 2018/12/5.
//  Copyright © 2018年 housir. All rights reserved.
//

#include <iostream>
#include "ThreadVisitPrivateStack.h"
//#include "DesignPattern/Singleton.h"
#include "Singleton.h"
#include "WorkerFactory.h"
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    // test();
    // Singleton::test();
    WorkerFactory::test();

    printf("hello world!\n");
    return 0;
}
