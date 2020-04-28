'''
    互斥锁和条件变量
    通常情况下，互斥锁和条件变量是配合使用的，互斥锁用于短期锁定，主要保证线程对临界区的进入；
    条件变量用于线程长期等待，在wait的时候会释放锁。操作的API如下所示（介绍最常用的）：
    
    std::mutex : 独占的互斥量，不能递归使用
    std::condition_variable ：条件变量，配合 std::unique<std::mutex>进行wait操作。
    std::condition_variable_any 和任意带有lock，unlock的mutex配合使用，但是效率比std::condition_variable差。
    
    举个栗子：
    
    10个人排队使用打印机，任一时刻只有一个人能使用。用一个变量i的0和1两种状态分别表示打印机能不能使用。这个程序这样写，详细解释见注释：

'''

#include<iostream>
#include<condition_variable>
#include<vector>
#include<thread>

std::vector<std::thread> tv;         //保存线程的情况



void subi() {            
    std::lock_guard<std::mutex> locker(lock);  //使用之前先加锁
    while(i == 0){             //如果不可用                
        m_t.wait(lock);        //将当前线程阻塞，注意：此时会释放锁
    }

    i--;                       //使用打印机过程
}

void addi() {                 
    std::lock_guard<std::mutex> locker(lock); //同理，放弃使用的时候先加锁

    i++;                       //是资源变为可用
    m_t.notify_all();          //通知其余阻塞的使用者可以使用了
}

void func(int j) {
    subi();
    std::cout << "I am thread "<< j << " , i = " << i << std::endl;
    addi();
}


int main(int argc,char *argv[])
{
    for(int j = 0; j < 10 ; ++j) {
        std::thread t(func,j);
        tv.push_back(std::move(t));
    }

    for(auto &thread : tv) {
        thread.join();
    }
    return 0;
}
