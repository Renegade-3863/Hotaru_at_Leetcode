#include "Solution.h"

bool Leetcode201_300::Solution::isHappy(int n)
{
    // 简单题简单做，我们需要做的只有下面的事：
    // 不断计算从 n 出发的所有下一个 "快乐数"
    // 并记录所有出现过的 "快乐数"
    // 如果某一次计算算出了前面出现过的 "快乐数"
    // 那么就可以断定我们拿不到1了
    // 否则，只要遇到了个1，我们就可以返回 true 了
    unordered_set<int> rec;
    rec.insert(n);
    while(n != 1)
    {
        // 计算这个数所有位的平方和
        int tmp = n, nxt = 0;
        while(tmp)
        {
            nxt += (tmp % 10) * (tmp % 10);
            tmp /= 10;
        } 
        n = nxt;
        if(rec.find(n) != rec.end())
        {
            return false;
        }
        rec.insert(nxt);
    }
    return n == 1;
}