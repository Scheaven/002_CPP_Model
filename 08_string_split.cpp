/*
    输入一连串数字，数字之间逗号隔开，把数字存到数组或者向量里。
*/

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

int main()
{
    string str_input;
    cout<<"输入一串以逗号为分隔符的数字字符串："<<endl;
    while(cin>>str_input)
    {
        vector<int> nums;
        // string->char *
        char *s_input = (char *)str_input.c_str();
        const char * split = ",";
        // 以逗号为分隔符拆分字符串
        char *p = strtok(s_input, split);

        int a;
        while(p != NULL)
        {
            // char * -> int
            sscanf(p, "%d", &a);
            nums.push_back(a);
            p=strtok(NULL, split);
        }

        cout<<"输出得到的数字："<<endl;
        for(a = 0; a < nums.size(); a++)
        {
            cout<<nums[a]<<endl;
        }
    }
    return 0;
}