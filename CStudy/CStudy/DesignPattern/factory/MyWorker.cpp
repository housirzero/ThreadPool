//
//  MyWorker.cpp
//  CStudy
//
//  Created by housir on 2018/12/9.
//  Copyright © 2018年 housir. All rights reserved.
//

#include "MyWorker.h"

MyWorker::MyWorker()
{
    printf("Construct MyWorker...\n");
}


MyWorker::~MyWorker()
{
    printf("Release MyWorker...\n");
}


void MyWorker::run()
{
    printf("MyWorker::run \n");
}
