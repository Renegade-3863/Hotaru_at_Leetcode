#include "Solution.h"

vector<string> Leetcode401_500::Solution::fizzBuzz(int n)
{
    // 简单的遍历，优先判断一个数是不是同时是 3 和 5 的倍数，不是的话再
    // 进一步进行判断   
    vector<string> res;
    for(int i = 1; i <= n; ++i)
    {
        // 优先检查是否是 FizzBuzz
        int rem3 = i % 3;
        int rem5 = i % 5;
        if(rem3 == 0 && rem5 == 0)
        {
            res.push_back("FizzBuzz");
            continue;
        }
        if(rem3 == 0)
        {
            res.push_back("Fizz");
            continue;
        }
        if(rem5 == 0)
        {
            res.push_back("Buzz");
            continue;
        }
        res.push_back(to_string(i));
    }
    return res;
}