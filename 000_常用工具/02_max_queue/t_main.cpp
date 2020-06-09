//
// Created by Scheaven on 2020/6/9.
//
#include "stack"
#include <iostream>
#include <cstdio>

#include "queue_util.hpp"
#include "stack_util.hpp"

using namespace std;


int main(int argc, char const *argv[])
{
    MaxQueue<int> queue;

//    int n;
//    cin >> n;
//
//    std::cout << "n" << n << std::endl;


    queue.push(5);
    queue.push(3);
    queue.push(2);
    queue.push(9);
    printf("max:%d\n",queue.max());
    queue.push(1);
    printf("max:%d\n",queue.max());
    printf("dd:%d\n",queue.front());
    queue.pop();
    printf("max:%d\n",queue.max());
    printf("dd:%d\n",queue.front());
    queue.pop();
    printf("max:%d\n",queue.max());

    printf("E:%d\n",queue.isEmpty());
    printf("dd:%d\n",queue.front());
    queue.pop();
    printf("max:%d\n",queue.max());
    printf("dd:%d\n",queue.front());
    queue.pop();
    printf("max:%d\n",queue.max());
    printf("dd:%d\n",queue.front());
    queue.pop();

    printf("E:%d\n",queue.isEmpty());





//    for (int i = 0; i < n; ++i) {
//        char op[2];
//        printf("%s","pppppp-::");
//        scanf("%s", op);
//        if (*op == 'E')
//        {
//            printf("%s","push::");
//            int num;
//            cin >> num;
//            queue.push(num);
//        } else if (*op == 'D')
//        {
//            printf("%s","pop::");
//            printf("%d\n", queue.front());
//            queue.pop();
//        } else
//        {
//            printf("%s","max::");
//            printf("%d\n", queue.max());;
//        }
//    }

    return 0;
}
