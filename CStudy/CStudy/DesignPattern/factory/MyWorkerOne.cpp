//
//  MyWorkerOne.cpp
//  CStudy
//
//  Created by housir on 2018/12/9.
//  Copyright © 2018年 housir. All rights reserved.
//

#include "MyWorkerOne.h"

MyWorkerOne::MyWorkerOne()
{
    printf("Construct MyWorkerOne...\n");
}


MyWorkerOne::~MyWorkerOne() 
{
    printf("Release MyWorkerOne...\n");
}


void MyWorkerOne::run()
{
    printf("MyWorkerOne::run \n");
}

