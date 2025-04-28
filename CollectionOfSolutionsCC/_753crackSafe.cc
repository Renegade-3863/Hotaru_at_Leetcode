#include "Solution.h"

string Leetcode701_800::Soltuion::crackSafe(int n, int k)
{
    // 不要管那么多奇奇怪怪的欧拉南欧拉北的
    // 这道题我们直接回溯就行
    // 简单来说，最后的答案串长度一定是
    // n-1+k^n，其中前面的 n-1 是一串 0，后面的 k^n 个值每一个都代表了一个可能的排列
    // 我们这里假设从 n 个 0 这个排列开始找，所以前面 n-1 才是一串 0，否则可以是其它元素
    // 我们把问题简化成：
    // 每一轮 dfs，检查并记录一个不重复的，可能的排列
    // 当我们走完一种可能后，如果已经找出的排列个数等于 k^n 个，那么我们就找到了一个最短的可行解
    // 基本的回溯流程看代码就行了
    unordered_set<int> visited;
    int highest = pow(10, n-1);
    function<void(int, string&)> dfs = [&](int node, string& res) -> void
    {
        // 如果此时 res.size() 已经等于了 pow(k, n)，那么说明我们已经找到了答案
        if(res.size() == pow(k, n))
        {
            // 可以直接返回了
            return;
        }
        for(int i = 0; i < k; ++i)
        {
            // 否则，针对当前的这个结点值，我们尝试扩散出一个结果 node##k 来
            // 备注：这里的 ## 标记是仿了 C++/C #define 宏编译指令，代表两个字符串的拼接
            int neigh = node*10+i;
            // 如果当前情况下，这个排列是我们新找到的，之前没有出现过，那么就记录到 res 中作为答案的一种
            if(!visited.count(neigh))
            {
                res.push_back('0'+i);
                visited.insert(neigh);
                // 之后，尝试进一步拿 node 的后 n-1 位继续寻找新的排列
                dfs(neigh%highest, res);
                // 注意检查，如果走了这条路之后，我们拿到了结果，那么从这里就要截断，不能执行下面的回溯步骤
                if(res.size() == pow(k, n))
                {
                    return;
                }
                // 否则，说明我们尝试先遍历这个排列是不可行的，需要回溯
                visited.erase(neigh);
                res = res.substr(0, res.size()-1);
            }
        }
    };
    string res;
    dfs(0, res);
    res = string(n-1, '0')+res;
    return res;
}