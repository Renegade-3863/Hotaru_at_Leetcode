#include "Solution.h"

// 第一版：单纯 DFS，不加记忆化，TLE
bool Leetcode201_300::Solution::canWin(string currentState)
{
    // 博弈论的问题思路基本都是一样的，让自己赢，让对面没有赢的机会
    // 本题无非是递归问题的参数变成了 currentState 这个字符串，没有其它区别
    // 把这个母问题定义为：当前玩家，在字符串状态为 currentState 的时候，是否有一定能赢的方法
    // 我们需要做的是，先找出 currentState 的情况下，执行所有可能的操作后序下一个状态字符串
    vector<string> nextState;
    // 这部分和上一题的过程是一样的
    int n = currentState.size();
    for(int i = 0; i < n-1; ++i)
    {
        string tmp = currentState;
        if(tmp[i] == '+' && tmp[i+1] == '+')
        {
            tmp[i] = '-'; tmp[i+1] = '-';
            nextState.push_back(tmp);
        }
    }
    // 根据还有没有可能的下一步来进行递归
    n = nextState.size();
    for(int i = 0; i < n; ++i)
    {
        // 如果对手在这种情况下一定不能赢，那么，我们可以采取这个策略取胜
        if(!canWin(nextState[i]))
        {
            return true;
        }
    }
    // 如果检查完所有可能，我们都赢不了，那么我们就返回 false，代表此时我们一定赢不了
    return false;
}

// 第二版：DFS + 记忆化，依然 TLE，看了一下答案，感觉是因为太多的中间变量以及数组操作导致的
bool canWin(string currentState)
{
    // 记忆化哈希表
    unordered_map<string, bool> memo;
    function<bool(string)> dfs = [&](string curState)
    {
        // 记忆化加速
        if(memo.find(curState) != memo.end())
        {
            return memo[curState];
        }
        // 否则，就正常进行上面的过程
        vector<string> nxtState;
        int n = curState.size();
        for(int i = 0; i < n-1; ++i)
        {
            string tmp = curState;
            if(tmp[i] == '+' && tmp[i+1] == '+')
            {
                tmp[i] = '-'; tmp[i+1] = '-';
                nxtState.push_back(tmp);
            }
        }
        n = nxtState.size();
        for(int i = 0; i < n; ++i)
        {
            if(!canWin(nxtState[i]))
            {
                memo[curState] = true;
                return true;
            }
        }
        memo[curState] = false;
        return false; 
    };
    // 调用即可
    return dfs(currentState);
}

// 第三版：根据一些答案的思路，优化出一个回溯的版本看看
bool canWin(string currentState)
{
    // 记忆化哈希表
    unordered_map<string, bool> memo;
    function<bool(string&)> dfs = [&](string& curState)
    {
        // 记忆化加速
        if(memo.find(curState) != memo.end())
        {
            return memo[curState];
        }
        // 否则，就正常进行上面的过程
        // 不使用数组保存下一步结果，而是换用回溯
        // vector<string> nxtState;
        // int n = curState.size();
        // for(int i = 0; i < n-1; ++i)
        // {
        //     string tmp = curState;
        //     if(tmp[i] == '+' && tmp[i+1] == '+')
        //     {
        //         tmp[i] = '-'; tmp[i+1] = '-';
        //         nxtState.push_back(tmp);
        //     }
        // }
        int n = curState.size();
        for(int i = 0; i < n-1; ++i)
        {
            if(curState[i] == '+' && curState[i+1] == '+')
            {
                // 递归
                curState[i] = '-'; curState[i+1] = '-';
                if(!canWin(curState))
                {
                    memo[curState] = true;
                    return true;
                }
                // 回溯
                curState[i] = '+'; curState[i+1] = '+';
            }
        }
        // 否则，赢不了，记录并返回即可
        memo[curState] = false;
        return false;
        // return false;
        // n = nxtState.size();
        // for(int i = 0; i < n; ++i)
        // {
        //     if(!canWin(nxtState[i]))
        //     {
        //         memo[curState] = true;
        //         return true;
        //     }
        // }
        // memo[curState] = false;
        // return false; 
    };
    // 调用即可
    return dfs(currentState);
}