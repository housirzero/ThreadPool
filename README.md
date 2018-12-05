# ThreadPool
thread pool

##问题记录
###.gitignore无效的解决方法
gitignore只能忽略那些原来没有被track的文件，如果某些文件已经被纳入了版本管理中，则修改.gitignore是无效的。解决方法是先把本地缓存删除，然后再提交。

    git rm --cache 需要忽略的文件
    # -r 可以递归移除目录及其下面的文件
    # -f 可以强制移除
