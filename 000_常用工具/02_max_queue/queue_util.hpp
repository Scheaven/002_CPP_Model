//
// Created by Scheaven on 2020/6/8.
//

#ifndef _QUEUE_UTIL_H
#define _QUEUE_UTIL_H

#include "stack_util.hpp"

using namespace std;
/**
 * 最大值队列
要求
用o(n)时间查询队列的最大值

算法思想：
用两个最大值栈模拟队列。入队时把元素压入栈A，出队时弹出B的栈顶。（若B为空，则把A中元素全部弹出压入B再弹出）。取最大值时去A，B中的最大值的最大值。


 * */

template <typename T> //注意 泛型模板必须把实现方法直接写在头文件里 否则找不到文件定义
class MaxQueue
{
private:
    MaxStack<T> stackA;
    MaxStack<T> stackB;

public:
    MaxQueue(){};
    ~MaxQueue(){};

    void push(T ele)
    {
        stackA.push(ele);
    };

    void pop()
    {
        if(stackB.isEmpty())
        {
//        if(stackA.isEmpty())
//        {
//            return ;
//        }
            while (!stackA.isEmpty())
            {
                stackB.push(stackA.top());
                stackA.pop();
            }
        }

        stackB.pop();
    };


    T front()
    {
        if(stackB.isEmpty())
        {
//        if(stackA.isEmpty())
//        {
//            return ;
//        }
            while (!stackA.isEmpty())
            {
                stackB.push(stackA.top());
                stackA.pop();
            }
        }
        return stackB.top();
    };

    T max()
    {
        if(!stackA.isEmpty()&&!stackB.isEmpty())
        {
            return stackA.maxItem()>stackB.maxItem()?stackA.maxItem():stackB.maxItem();
        } else if(!stackA.isEmpty()&&stackB.isEmpty())
        {
            return stackA.maxItem();
        } else
        {
            return stackB.maxItem();
        }
    };

    bool isEmpty()
    {
        return stackA.isEmpty()&&stackB.isEmpty();
    };

};

#endif //INC_05_MAX_STACK_QUEUE_QUEUE_UTIL_H
