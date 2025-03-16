#include "Solution.h"

bool Leetcode601_700::Soltuion::hasAlternatingBits(int n)
{
    // 简单模拟题，我们按要求做就行
    // 我们遍历 n 的二进制表示串，按从低位到高位的顺序进行
    int idx = 1;
    // 从第一位开始处理
    // 保存起始第一位的值，为了满足定义，我们把 first 预设为与 n 最低位不同的值
    int first = (n%2) ^ 1;
    // 循环检查，直到 n 变为 0 为止
    while(n)
    {
        int nxt = n%2;
        // 如果当前最低位等于 first，说明 n 不满足条件，返回 false 即可
        if(nxt == first)
        {
            return false;
        }
        first = nxt;
        n >>= 1;
    }
    // 检查完成，满足题意，返回 true 即可
    return true;
}