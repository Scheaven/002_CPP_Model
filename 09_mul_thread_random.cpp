#include <iostream>
#include <thread>
#include  <unistd.h>
#include <ctime>
#include <cstdlib>

'''
运行命令
g++ -std=c++11 sample.cpp -lpthread
'''

void subthread_function()
{
	srand(time(0));
	for (int i = 0; i < 10; ++i)
	{
		int random_seconds = rand()%5;
		/* code */
		std::cout << i << " :ID: = " << std::this_thread::get_id() << "  :  " <<  random_seconds << std::endl;
		sleep(random_seconds);
	}
}

int main(int argc, char const *argv[])
{
	std::thread threadObj1(subthread_function);
	std::thread threadObj2(subthread_function);

	threadObj1.join();
	threadObj2.join();
	return 0;
}


// static void subthread_function(int cc)
// {
// 	srand(time(0));
// 	for (int i = 0; i < 10; ++i)
// 	{
// 		int random_seconds = rand()%cc;
// 		/* code */
// 		std::cout << cc << " :ID: = " << std::this_thread::get_id() << "  :  " <<  random_seconds << std::endl;
// 		sleep(random_seconds);
// 	}
// }

// int main(int argc, char const *argv[])
// {
// 	std::vector<std::thread> vec;


// 	for (int i = 2; i < 5; ++i)
// 	{
// 		std::thread threadObj(subthread_function, i);

// 		vec.emplace_back(std::move(threadObj));
// 	}

// 	for (auto &a : vec)
// 	{
// 		a.join();
// 	}
// 	return 0;
// }
