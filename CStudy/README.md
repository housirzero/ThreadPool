## 测试C/C++相关问题的小程序
> * ThreadVisitPrivateStack
    测试线程是否可以访问同进程下线程的栈空间
> * next

## 关于extern

extern 表明变量或函数在其他地方定义。
当一个头文件会被很多cpp引用，并且其中定义了变量或者函数，编译就会出现重复定义的问题，比如下面这样，main.cpp和1.cpp都引用了1.h，链接阶段时就会出错。
```
// 1.h
int a;
int fun() { return 0; }

// 1.cpp
#include "1.h"

// main.cpp
#include "1.h"
```

实际上我们一般对函数只会在头文件中声名，在CPP中定义，所以没有什么问题，如下：
```
// 1.h
int fun(); // 声明

// 1.cpp
#include "1.h"
int fun() // 定义
{ 
return 0; 
}

// main.cpp
#include "1.h"
```

但是变量直接写int a就代表已经定义了，分配了空间。要想声明，前面就需要加上extern关键字，并在cpp中定义，这样就不或出现问题了(main.cpp就知道a是在其他地方定义的了)。如下：
```
// 1.h
extern int a; // 声明

// 1.cpp
#include "1.h"
int a = 1; // 定义

// main.cpp
#include "1.h"
```
