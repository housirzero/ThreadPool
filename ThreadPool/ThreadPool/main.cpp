//
//  main.cpp
//  ThreadPool
//
//  Created by housir on 2018/11/15.
//  Copyright © 2018年 housir. All rights reserved.
//

#include <iostream>
#include "CThreadPool.h"
#include <unistd.h>
using namespace std;

// 测试类
//
class MyWorker: public CWorker
{
public:
    MyWorker(int s, int e):start(s), end(e), sum(0){};
    ~MyWorker(){};
    
    void run()
    {
        for(int i = start; i <= end; ++i)
        {
            sum += i;
            usleep(10000);
        }
        printf("sum[%d, %d] = %d\n", start, end, sum);
    }
    
private:
    int start;
    int end;
    int sum;
};

#define WAIT_THREAD_TIME 10000

int main(int argc, const char * argv[]) {
    CThreadPool* threadPool = new CThreadPool(3);
    list<MyWorker*> listMyWorker; // 记录对象，用于最后释放空间
    
    for(int i = 0; i < 10; ++i)
    {
        MyWorker * pWorker = new MyWorker(i*20, (i + 1) * 20 - 1);
        listMyWorker.push_back(pWorker);
        while(!threadPool->assignWork(pWorker))
        {
            printf("assign work %d failed, wait %d ms...\n", i, WAIT_THREAD_TIME / 1000);
            usleep(WAIT_THREAD_TIME); // ms
        }
        printf("assign work %d success.\n", i);
    }
    
    list<MyWorker *>::iterator it = listMyWorker.begin();
    for(; it != listMyWorker.end(); ++it)
    {
        delete *it;
    }
    listMyWorker.clear();
    
    //threadPool->join();
    delete threadPool;
    return 0;
}
