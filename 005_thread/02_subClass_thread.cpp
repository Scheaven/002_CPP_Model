#include <iostream>
#include <string>
#include <iostream>
#include <map>
#include <string>
#include <list>
#include <algorithm>
#include <fstream>
#include <stdint.h>
#include <vector>
#include <thread>

#include "02_subClass/AA.h"

using namespace std;

 int main(int argc, char *argv[])
 {
    AA aa;

 	while (true)
	{
        std::thread thread1(&AA::s_test,&aa); // 如果是同一个类调用则将aa 变成 this。
        std::thread thread2(&AA::s_test,&aa); 
         // 跟多的参数用逗号分隔后再后边追加 如std::thread thread2(&AA::s_test,&aa， n , m);  

        thread1.join();
        thread2.join();
	}

 	return 0;
 }
