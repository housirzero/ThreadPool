//
//  Worker.hpp
//  CStudy
//
//  Created by housir on 2018/12/9.
//  Copyright © 2018年 housir. All rights reserved.
//

#ifndef Worker_h
#define Worker_h

class Worker  
{  
public:  
    Worker(){};
    virtual ~Worker(){}; // 必须加上virtual，这样delete基类时才能销毁派生类
    
    virtual void run() = 0;
}; 

#endif /* Worker_h */
