#include "Solution.h"

// 下面是一个 nt 人想了两分半想出来的错误解法，大家不要跟他学（）
int Leetcode701_800::Soltuion::openLock(vector<string>& deadends, string target)
{
    // 简单的 DP 类问题
    // 我们可以先从 DFS 入手
    // 定义一个递归子问题：
    // dfs(str) 代表当前转盘锁上的数值为 str 的情况下，我们要达到 target 所需的最小旋转次数
    // 那么整体的递推思路就不难想了
    // 从当前 str 往后，应该有 36 种可能的下一步状态（一共四个圆形拨轮+每个拨轮 9 个可能的新数字）
    // dfs(str) = min{for all k from 0 to 35}(dfs(strk))
    // 边界情况有两种：
    // 1. str == target，此时我们返回 0
    // 2. str in deadends，此时我们返回 0x3f3f3f3f，代表一个不可行的极大值
    unordered_set<string> memo;
    // 需要防止无限递归，因而我们需要记录一个访问状态哈希，这一点和传统的 DFS 算法是完全一致的
    unordered_map<string, int> visited;
    // 把 deadends 数组转储成方便查询的哈希集合
    for(const auto& deadend : deadends)
    {
        memo.insert(deadend);
    }
    function<int(string& str)> dfs = [&](string& str) -> int
    {
        if(str == target)
        {
            return 0;
        }
        if(memo.find(str) != memo.end())
        {
            return -1;
        }
        // 1 代表这个结点在被访问，但是没有访问完成
        visited[str] = 1;
        // 一般情况，考虑对 str 进行修改
        int ret = INT_MAX;
        for(auto& c : str)
        {
            // 每个 c 有两种修改方案，一种是 +1，一种是 -1
            for(int i = -1; i <= 1; i += 2)
            {
                char tmp = c;
                // 注意：如果 c 是 '0' 或者是 '9'，需要在某些情况下回卷
                if(c == '0' && i == -1)
                {
                    c = '9';
                }
                else if(c == '9' && i == 1)
                {
                    c = '0';
                }
                else
                {
                    c = (char)(c+i);
                }
                // 重复的元素不再重新计算
                if(visited[str] == 2)
                {
                    continue;
                }
                // 递归计算
                int nxt = dfs(str);
                if(nxt == -1)
                {
                    c = tmp;
                    continue;
                }
                ret = min(ret, nxt+1);
                // 回溯
                c = tmp;
            }
        }
        // 此时 str 已经访问完成，我们把它标记成 2
        visited[str] = 2;
        return ret == INT_MAX ? -1 : ret;
    };
    string start = "0000";
    return dfs(start);
}

// 马后炮：分析了一下，上面的方案失败的本质原因在于，这道题不具备 DFS 的基本结构
// 关键问题在于：我们没法防止无限递归
// 应用上面的思路，我们依然没法确保在 "9000" 的时候知道 "0000" 是否已经在这一个枝条中被访问过了
// 简单画一下递归回溯树的话，我们会发现需要去重的元素在不同枝条的不同层上，这种去重很难搞
// 所以这道题基本的思路还是 BFS
int openLock(vector<string>& deadends, string target)
{
    // 基本思路是，使用广搜往外进行结点扩散
    // 当第一次扩散到 target 时，我们扩散的层数就是结果
    // 在这种思路下，我们就自然而然避免了 DFS 那种夸张的、无法解决的防止重复访问问题
    // 回忆一下 BFS 的基本模版
    // 我们用一个 queue 保存所有的 "下一层" 结点信息
    // 在每一层中更新下一层的信息
    // 直到 "下一层" 没有更多信息，或者对于本题，我们达到了最终的结果
    queue<string> q;
    // 开始状态为 "0000"
    string start = "0000";
    // 预处理一下 deadends 数组，保存成更方便检索的哈希形式
    unordered_set<string> memo;
    for(const auto& deadend : deadends)
    {
        memo.insert(deadend);
    }
    // 开头就在 deadends 中，没法做了，直接返回 -1 
    if(memo.count("0000"))
    {
        return -1;
    }
    int steps = 0;
    unordered_set<string> visited;
    visited.insert(start);
    q.push(start);
    while(!q.empty())
    {
        // 我们按层进行处理
        // 获取层长
        int n = q.size();
        // cout << n << endl;
        for(int i = 0; i < n; ++i)
        {
            string cur = q.front();
            q.pop();
            // 这里我们实现一个假设：cur 一定不是 deadends 中的元素
            // 那么如果 cur 是 target，我们就可以直接返回 steps 层数了
            if(cur == target)
            {
                return steps;
            }
            // 否则，还不是 target，那么我们尝试对 cur 进行扩散
            // 在这里，我们就可以剪枝那些之前已经访问过的结点，因为在更深的层访问在上层已经访问过的结点
            // 即使这条路最后到达了 target，步数也一定是多于在高层就访问这个结点的路径的
            // 所以我们可以用一个 visited 数组来保存那些已经访问过的结点，不再对它们进行二次访问
            for(auto& c : cur)
            {
                // 两种情况，对 c +1 和对 c -1
                for(int i = -1; i <= 1; i += 2)
                {
                    char tmp = c;
                    if(c == '0' && i == -1)
                    {
                        c = '9';
                    }
                    else if(c == '9' && i == 1)
                    {
                        c = '0';
                    }
                    else 
                    {
                        c = (char)(c+i);
                    }
                    // 如果修改后的 str 没有出现在 memo 中过，同时它也不再 deadends 中，那么我们就把它放到 q 中，等待下一层处理
                    if(memo.count(cur) == 0 && visited.count(cur) == 0)
                    {
                        memo.insert(cur);
                        q.push(cur);
                    }
                    c = tmp;
                }
            }
        }
        // 当前层处理完成，我们可以对 steps 进行递增
        ++steps;
    }
    // 没有到达 target，返回 -1
    return -1;
}