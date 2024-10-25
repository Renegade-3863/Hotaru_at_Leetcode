#include "Solution.h"

// 第一版：单纯的 DFS，不加记忆化
bool Leetcode201_300::Solution::canWinNim(int n)
{
    // 博弈论类的题目都是类似的方法
    // 我们把母问题定义为：当前玩家在总是作出最优选择的情况下，是否能够获胜
    // 那么对于本题，写起来就不难了
    // 基本情况：如果当前玩家的回合，剩下的石头不足3个，那么直接返回 true 即可，因为总是执行最优拿法的策略，当前玩家一定能赢
    if(n <= 3)
    {
        return true;
    }
    // 否则，我们需要的是分别考察当前玩家拿掉一个、两个或者三个石头的情况下，是否可以让对手赢不了(注意，是赢不了，即是对手也用最优策略的条件下)
    bool canWin = false;
    if(!canWinNim(n-1) || !canWinNim(n-2) || !canWinNim(n-3))
    {
        return true;
    }
    // 如果无论怎样都不能让对方输，那么我们就赢不了了
    return false;
}

// 第二版：DFS + 记忆化加速，虽然没超时，但是炸内存了。。。题目直接给了个 1348820612 个石头，这是把全地球的石头都拿来做游戏了吗。。。
bool canWinNim(int n)
{
    vector<int> memo(n+1, -1);
    function<bool(int)> dfs = [&](int n)
    {
        if(n <= 3)
        {
            return true;
        }
        if(memo[n] != -1)
        {
            return (bool)memo[n];
        }
        bool canWin = false;
        if(!dfs(n-1) || !dfs(n-2) || !dfs(n-3))
        {
            memo[n] = true;
            return true;
        }
        memo[n] = false;
        return false;
    };
    return dfs(n);
}

// 案例来说明白上面的思路其实是可以解决大多数博弈论类问题的
// 可是本题不当人，给出超大的 n 值炸我们的内存。。。
// 然后官解给出了下面的方案：
// 只要 n 是 4 的倍数，那么当前的人就永远不可能赢
// 因为此时无论我们拿 1 个，2 个，还是 3 个，我们的对手都永远可以对应地拿 3 个，2 个 和 1 个，从而保证石头还剩下 4 的倍数个
// 直到剩下最后4个，我们拿一部分，剩下一部分对手拿走，我们就输了
// 而如果剩下的石头个数不是 4 的倍数个，我们总是可以拿走一部分，使剩下的石头是4的倍数个，留给对手 4 的倍数个
// 那么根据上面的推理，此时对手永远也不可能赢了
bool canWinNim(int n)
{
    return n % 4 != 0;
}