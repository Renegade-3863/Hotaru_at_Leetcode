#include "Solution.h"

vector<string> Leetcode201_300::Solution::generatePossibleNextMoves(string currentState)
{
    // 简单的字符串模拟题
    // 要做什么，我们就做什么就可以了
    int n = currentState.size();
    vector<string> res;
    for(int i = 0; i < n-1; ++i)
    {
        string tmp = currentState;
        // 我们每次检查连续的两个字符，如果是两个 '+'，我们就可以进行转换
        if(tmp[i] == '+' && tmp[i+1] == '+')
        {
            tmp[i] = '-';
            tmp[i+1] = '-';
            // 修改后的字符串添加到 res 中
            res.push_back(tmp);
        }
        // 其它情况，都不进行添加，因为不同的两个字符不能进行变换
    }
    return res;
}