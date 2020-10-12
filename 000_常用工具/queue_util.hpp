//
// Created by Scheaven on 2020/6/8.
//

#ifndef _QUEUE_UTIL_H
#define _QUEUE_UTIL_H

#include "stack_util.hpp"

using namespace std;

template <typename T>
class MaxQueue
{
private:
    MaxStack<T> stackA;
    MaxStack<T> stackB;

public:
    MaxQueue(){};
    ~MaxQueue(){};

    void push(T ele) //入队
    {
        stackA.push(ele);
    };

    void pop() // 出队
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


    T front() // 取第一个元素
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

    T max() //最值
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

    int size() //大小
    {
        return stackA.size()+stackB.size();
    }

    bool isEmpty()
    {
        return stackA.isEmpty()&&stackB.isEmpty();
    };

};

template <typename T>
class MinQueue
{
private:
    MinStack<T> stackA;
    MinStack<T> stackB;

public:
    MinQueue(){};
    ~MinQueue(){};

    void push(T ele) //入队
    {
        stackA.push(ele);
    };

    void pop() // 出队
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


    T front() // 取第一个元素
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

    T min() //最值
    {
        if(!stackA.isEmpty()&&!stackB.isEmpty())
        {
            return stackA.minItem()<stackB.minItem()?stackA.minItem():stackB.minItem();
        } else if(!stackA.isEmpty()&&stackB.isEmpty())
        {
            return stackA.minItem();
        } else
        {
            return stackB.minItem();
        }
    };

    int size() //大小
    {
        return stackA.size()+stackB.size();
    }

    bool isEmpty()
    {
        return stackA.isEmpty()&&stackB.isEmpty();
    };

};

#endif //INC_05_MAX_STACK_QUEUE_QUEUE_UTIL_H
