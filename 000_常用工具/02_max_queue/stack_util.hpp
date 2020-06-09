//
// Created by Scheaven on 2020/6/8.
//

#ifndef _STACK_UTIL_H
#define _STACK_UTIL_H

#include <algorithm>
#include <memory.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <vector>
#include <stack>
#include <cstdio>

using namespace std;

/**实现最大值栈
以O(1)的时间查询栈中的最大值.
算法思路
维护一个最大值栈，在原栈中数据发生改变时最大值栈也跟着改变。
每次输入一个数据，若最大值栈为空，则比较最大值栈栈顶和当前元素，如果当前元素较大或相等，就把当前元素推入栈中，反之出栈时，如果出栈元素和当前元素相等，则把最大值栈中元素也推出栈。
 */

template <typename T> //注意 泛型模板必须把实现方法直接写在头文件里 否则找不到文件定义
class MaxStack
{
private:
    stack<T> max_stack;
    stack<T> _data;

public:
    void push(T ele)
    {
        _data.push(ele);
        if(max_stack.empty() || ele>=max_stack.top())
        {
            max_stack.push(ele);
        }
    };

    void pop()
    {
        T tem = _data.top();
        _data.pop();
        if(tem==max_stack.top())
        {
            max_stack.pop();
        }
    };

    T top()
    {
        return _data.top();

    };

    bool isEmpty()
    {
        return _data.empty();
    };

    T maxItem()
    {
        return max_stack.top();
    };
};

#endif //INC_05_MAX_STACK_QUEUE_STACK_UTIL_H
