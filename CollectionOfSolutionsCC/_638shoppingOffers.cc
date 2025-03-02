#include "Solution.h"

int Leetcode601_700::Soltuion::shoppingOffers(vector<int>& price,  vector<vector<int>>& special, vector<int>& needs)
{
    // 不要被那堆题解骗了！什么背包问题，这道题本质上是个回溯！！
    // 这样来理解这个题：
    // 我们要达到最终的 needs 这一结果，一定需要某种购买顺序
    // 这个顺序中，可能会包含很多不同的购买元
    // 比如某一步我买某个单一物品
    // 另一步我又买了某一个大礼包
    // 这样，我们就明确了，这就是个回溯类暴搜问题！
    // 明确了基本的逻辑，我们就不难写出下面的代码了 (纯暴力版本，没有添加任何记忆化，会 TLE)
    int n = price.size(), m = special.size();
    function<int(vector<int>&)> dfs = [&](vector<int>& curNeeds) -> int
    {
        // 定义一个递归的基本情况
        // 如果 needs 为全 0，那么我们直接返回 0
        bool allZero = true;
        for(const int& curNeed : curNeeds)
        {
            if(curNeed != 0)
            {
                allZero = false;
                break;
            }
        }
        if(allZero)
        {
            return 0;
        }
        // 最后的返回结果
        int res = INT_MAX;
        // 1. 当前不买礼包，而是买任意一种还有需求的一件物品
        for(int i = 0; i < n; ++i)
        {
            if(needs[i] > 0)
            {
                --curNeeds[i];  
                res = min(res, dfs(curNeeds)+price[i]);
                // 回溯
                ++curNeeds[i];
            }
        }
        // 2. 当前买一个礼包，考虑要买哪一种，注意，必须是需求不小于礼包提供的量的时候才能买，这是题目要求
        for(int i = 0; i < m; ++i)
        {
            // 另开一个 for 循环，检查这个礼包能不能买
            bool canBuy = true;
            for(int j = 0; j < n; ++j)
            {
                if(curNeeds[j] < special[i][j])
                {
                    canBuy = false;
                    break;
                }
            }
            if(!canBuy)
            {
                // 不能买，跳过这个分支
                continue;
            }
            // 可以买，我们购买后，递归计算结果
            for(int j = 0; j < n; ++j)
            {
                curNeeds[j] -= special[i][j];
            }
            // 别忘了加上买这个礼包的钱！！
            res = min(res, dfs(curNeeds)+special[i][n]);
            // 回溯
            for(int j = 0; j < n; ++j)
            {
                curNeeds[j] += special[i][j];
            }
        }
        return res;
    };
    return dfs(needs);
}

// 第二版，优化一下递归，添加记忆化模块
// 注意到，在探索购买顺序的过程中，我们很可能会找出很多重复的子问题
// 所以这种时候，引入一个记忆化数组就很有必要了
// 不过说实话，vector 能作为 map 的键这件事我也是看过了题解才知道的...
// 如果不知道的话，可能就会傻乎乎地自己去重载一个用 vector 进行哈希运算的函数给 unordered_map 了
// 不过这样也问题不大hhh
// 注意：unordered_map 因为是用哈希函数来实现的，所以会需要用户自己定义 vector 的哈希函数
// 而 map 底层是红黑树，本质上不是用映射来存储数据的，所以 vector 是可以作为 map 存储元素的键的 (虽然这样理解不一定对，但可以记住这个知识点)
int shoppingOffers(vector<int>& price, vector<vector<int>>& speical, vector<int>& needs)
{
    int n = price.size(), m = special.size();
    unordered_map<vector<int>, int> memo;
    function<int(vector<int>&)> dfs = [&](vector<int>& curNeeds) -> int
    {
        // 定义一个递归的基本情况
        // 如果 needs 为全 0，那么我们直接返回 0
        bool allZero = true;
        for(const int& curNeed : curNeeds)
        {
            if(curNeed != 0)
            {
                allZero = false;
                break;
            }
        }
        if(allZero)
        {
            return 0;
        }
        // 记忆化
        if(memo.count(curNeeds))
        {
            return memo[curNeeds];
        }
        // 最后的返回结果
        int res = INT_MAX;
        // 1. 当前不买礼包，而是买任意一种还有需求的一件物品
        for(int i = 0; i < n; ++i)
        {
            if(needs[i] > 0)
            {
                --curNeeds[i];  
                res = min(res, dfs(curNeeds)+price[i]);
                // 回溯
                ++curNeeds[i];
            }
        }
        // 2. 当前买一个礼包，考虑要买哪一种，注意，必须是需求不小于礼包提供的量的时候才能买，这是题目要求
        for(int i = 0; i < m; ++i)
        {
            // 另开一个 for 循环，检查这个礼包能不能买
            bool canBuy = true;
            for(int j = 0; j < n; ++j)
            {
                if(curNeeds[j] < special[i][j])
                {
                    canBuy = false;
                    break;
                }
            }
            if(!canBuy)
            {
                // 不能买，跳过这个分支
                continue;
            }
            // 可以买，我们购买后，递归计算结果
            for(int j = 0; j < n; ++j)
            {
                curNeeds[j] -= special[i][j];
            }
            // 别忘了加上买这个礼包的钱！！
            res = min(res, dfs(curNeeds)+special[i][n]);
            // 回溯
            for(int j = 0; j < n; ++j)
            {
                curNeeds[j] += special[i][j];
            }
        }
        memo[curNeeds] = res;
        return res;
    };
    return dfs(needs);
}