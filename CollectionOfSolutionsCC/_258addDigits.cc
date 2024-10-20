#include "Solution.h"

int Leetcode201_300::Solution::addDigits(int num)
{
    // 简单的模拟题，按照题目要求模拟各位添加的过程即可
    // count 用于记录当前这个 num 的数位个数
    int count = 0;
    // 先获取一开始的 num 的数位个数
    int tmp = num;
    while(tmp)
    {
        tmp /= 10;
        ++count;
    }
    while(count > 1)
    {
        // 重制数位个数
        count = 0;
        // 把每个位上的元素求和，赋值给 num，再重求 count 值
        int sum = 0;
        while(num)
        {
            sum += num%10;
            num /= 10;
        }
        num = sum;
        // 再循环求 num 的数位个数
        while(sum)
        {
            sum /= 10;
            ++count;
        }
    }
    // 上面的循环结束后，num 保存的就是最终结果，返回结果即可
    return num;
}

// 官解给出的 O(1) 解法属实逆天，不过也无所谓了，看个乐子就好，个人认为面试的时候能写出来模拟的代码就可以了。。。