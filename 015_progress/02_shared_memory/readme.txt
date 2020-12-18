两个分离进程之间的交互
gcc shmread.c shmread -lm
gcc shmwrite.c shmwrite -lm 

./shmread
./shmwrite （可以有多个）

原文链接
https://blog.csdn.net/ljianhui/article/details/10253345?ops_request_misc=%25257B%252522request%25255Fid%252522%25253A%252522160825965316780296818960%252522%25252C%252522scm%252522%25253A%25252220140713.130102334.pc%25255Fall.%252522%25257D&request_id=160825965316780296818960&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_v2~rank_v29-1-10253345.pc_search_result_cache&utm_term=linux%E8%BF%9B%E7%A8%8B%E9%80%9A%E4%BF%A1%20%E4%BD%BF%E7%94%A8%E5%85%B1%E4%BA%AB%E5%86%85%E5%AD%98
