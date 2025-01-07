#include "Solution.h"

bool Leetcode401_500::Soltuion::canIWin(int maxChoosableInteger, int desiredTotal)
{
    // 博弈论类的题目，此类题目一般的切入点都是 DFS 递归或进一步用 DP
    // 我们定义一个 DFS 函数，用来计算下面的子问题：
    // 当前玩家先手，还剩下 "某些数字" 可选，以及当前的累积和为 curTotal 的情况下，当前玩家是否有机会赢下游戏
    // 分配一组 bool 类型的变量，记录某个数字是否已经被选取，这个动态数组在 dfs 函数中被修改
    vector<bool> choosableIntegers(maxChoosableInteger, true);
    function<bool(int)> dfs = [&](int curTotal) -> bool
    {
        // 当前先手玩家可以选择所有还没被选择的数字
        // 我们遍历 maxShoosableInteger 来检查有哪些元素没有被选择
        for(int i = 0; i < maxChoosableInteger; ++i)
        {
            // i 数字可选，那么选择，并递归对手的情况检查是否可赢
            if(choosableIntegers[i])
            {
                choosableIntegers[i] = false;
                // 注意，递归前，我们判断这次选择是否使得 curTotal 从小于 desiredTotal 变成不小于 desiredTotal
                if(curTotal+i+1 >= desiredTotal)
                {
                    choosableIntegers[i] = true;
                    return true;
                }
                // 把选择的数添加到 curTotal 中，注意，我们选择的数是 i+1，而不是 i
                // 递归，判断对手在之后的情况下是否能赢，不能的话，当前玩家就能赢
                if(!dfs(curTotal+i+1))
                {
                    // 直接返回 true 代表可赢即可
                    choosableIntegers[i] = true;
                    return true;
                }
                // 别忘了回溯
                choosableIntegers[i] = true;
            }
        }
        // 所有情况都试过了，当前先手都赢不了，那么就返回 false，代表 "赢不了"
        return false;
    };
    // 调用 dfs 函数即可
    return dfs(0);
}

// 上面的计算方案很明显是会 TLE 的，我们需要考虑使用记忆化对递归算法进行加速
// 但是，实际上要记忆化的内容不仅有 curTotal 这个标签，还有 "当前可选数字列表" 这个信息，所以我们前面使用数组记录的方式显然不适用于哈希表的键存储格式
// 我们需要考虑利用整型数存储的方法
// 而且本题的限制也是 maxChoosableNumber 是属于 [1, 20] 的，这就提示了我们可以用单个整型数来代替原来的整型数组
bool canIWin(int maxChoosableInteger, int desiredTotal)
{
    // 最后测试的时候发现题目测试案例还有一个额外的奇葩样例：所有可选数字的综合小于 desiredtotal
    // 那么我们在这里额外做一下判定。。
    // 等差数列求和公式：
    if(((1+maxChoosableInteger)*(maxChoosableInteger)>>1) < desiredTotal)
    {
        return false;
    }
    // 一个整型变量，代替上面的 bool 数组使用
    int choosedIntegers = 0;
    // 记忆化哈希表，记录的是：选择的情况为 choosedIntegers 时，先手是否可赢
    unordered_map<int, bool> memo;
    function<bool(int)> dfs = [&](int curTotal) -> bool
    {
        // 已经处理过这种情况，那么直接返回结果即可
        if(memo.find(choosedIntegers) != memo.end())
        {
            return memo[choosedIntegers];
        }
        // 我们需要根据 choosedIntegers 的情况，决定当前先手可以选择哪一个值
        for(int i = 0; i < maxChoosableInteger; ++i)
        {
            // 位运算判断对应位是否为 0，即没有被选过
            if(((choosedIntegers >> i) & 1) == 0)
            {
                // 那么我们可以选这个数
                // 如果选了这个数就能赢，那我们就不用深入递归了
                if(curTotal+i+1 >= desiredTotal)
                {
                    memo[choosedIntegers] = true;
                    return memo[choosedIntegers];
                }
                // 否则，我们先选这个数，检查对手在后续情况下是否能赢
                // 选择上这个数
                int tmp = choosedIntegers;
                choosedIntegers = choosedIntegers | (1 << i);
                // 递归
                if(!dfs(curTotal+i+1))
                {
                    // 返回前，别忘了回溯
                    choosedIntegers = tmp;
                    // 对手赢不了，那么我们就一定能赢
                    memo[choosedIntegers] = true;
                    return memo[choosedIntegers];
                }
                // 否则，虽然现在赢不了，也别忘了回溯
                choosedIntegers = tmp;
            }
        }
        // for 循环整个结束，我们都没发现先手能赢，那么就返回 false 即可
        memo[choosedIntegers] = false;
        return memo[choosedIntegers];
    };
    // 调用函数即可
    return dfs(0);
}