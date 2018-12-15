//
//  commondefine.h
//  ThreadPool
//
//  Created by housir on 2018/11/19.
//  Copyright © 2018年 housir. All rights reserved.
//

#ifndef commondefine_h
#define commondefine_h

typedef unsigned int __UINT32;
typedef int          __INT32;

#define MAX_THREAD_POOL_SIZE  10
#define MAX_WORKER_QUEUE_SIZE 20

#ifdef _WIN32
    //define something for Windows (32-bit and 64-bit, this part is common)
    #ifdef _WIN64
    	//define something for Windows (64-bit only)
    #else
    	//define something for Windows (32-bit only)
	#endif
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_IPHONE_SIMULATOR
    	// iOS Simulator
    #elif TARGET_OS_IPHONE
    	// iOS device
    #elif TARGET_OS_MAC
    	// Other kinds of Mac OS
    #else
    	#   error "Unknown Apple platform"
    #endif
#elif __ANDROID__
	// android
#elif __linux__
	// linux
#elif __unix__ // all unices not caught above
	// Unix
#elif defined(_POSIX_VERSION)
	// POSIX
#else
	#   error "Unknown compiler"
#endif

#endif /* commondefine_h */
