#include "Solution.h"

string Leetcode501_600::Soltuion::findContestMatch(int n)
{
    // 简单模拟题，我们按照题目要求做就行
    // 考虑这样的事实，我们需要的是：每一轮比赛，比赛的双方都应该是 "一个强队对阵一个弱队"
    // 那么我们可以从贪心的角度考虑这个问题
    // 具体来说，假设有 8 支队伍
    // 那么按步骤来考虑的话，应该是第一支队伍和最后一支队伍比较，之后第二支队伍和倒数第二支队伍比较
    // 之后是第三支和倒数第三支，etc.
    // 用这样的方式，第一轮可以得出 "能力前四的四支队伍胜出"
    // 之后按同样的逻辑，我们可以逐渐递进地退出最后的结果
    // 根据上面的逻辑，我们一共应该需要 log2(n) 对括号来进行配对
    deque<string> dq;
    for(int i = 1; i <= n; ++i)
    {
        dq.push_back(to_string(i));
    }
    while(dq.size() > 1)
    {
        deque<string> nxt_dq;
        while(dq.size() > 0)
        {
            string x = dq.front(); dq.pop_front();
            string y = dq.back();  dq.pop_back();
            nxt_dq.push_back('('+x+','+y+')');
        }
        dq = nxt_dq;
    }
    return dq.front();
}