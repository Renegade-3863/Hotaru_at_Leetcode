#include "Solution.h"

vector<int> Leetcode701_800::Soltuion::asteroidCollision(vector<int>& asteroids)
{
    // 考虑用一个栈进行模拟
    // 我们用一个栈保存从左往右还没爆炸的所有正向移动的行星
    stack<int> stk;
    // 之后每当遇到一颗负向移动的行星时，我们就让栈顶的这颗行星和该负向移动的行星相撞
    // 如果栈顶的行星和该负向移动的行星相撞后，栈顶的行星爆炸了，那么我们就将该负向移动的行星继续和下一个栈顶的行星相撞
    // 但是如果某一时刻栈中没有正向移动的行星，该怎么办？
    // 很简单，什么也不做，把这个负向移动的行星添加到答案中即可，因为它不可能和后面的正向移动行星再相撞了
    // 明确了基本逻辑，代码写起来就不难了
    // 遍历每一颗行星
    vector<int> res;
    for(const auto& asteroid : asteroids)
    {
        if(asteroid > 0)
        {
            // 正向移动的行星，直接入栈即可
            stk.push(asteroid);
        }
        else
        {
            // 负向移动的行星，那么不断与栈顶行星相撞，直到这颗行星爆炸或栈为空
            bool both = false;
            while(!stk.empty() && stk.top() <= abs(asteroid))
            {
                // 注意，如果栈顶行星等于 abs(asteroid)，那么两颗行星都爆炸了
                // 所以我们也要退出循环
                if(stk.top() == abs(asteroid))
                {
                    stk.pop();
                    both = true;
                    break;
                }
                // 让栈顶这个元素爆炸
                stk.pop();
            }
            if(stk.empty() && !both)
            {
                res.push_back(asteroid);
            }
        }
    }
    // 处理完成，把栈中剩下的元素补充到答案中即可
    int n = res.size();
    while(!stk.empty())
    {
        res.insert(res.begin()+n, stk.top());
        stk.pop();
    }
    return res;
}