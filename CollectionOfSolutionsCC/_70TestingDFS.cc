#include "Solution.h"

// 记录一个扩展问题：如何输出所有对应的方案？
// 这个问题显然就是想让我们把原始的 dfs 版本写出来，因为 dp 要找实际方案的话，就需要记录上一步信息，这和 dfs 的本质其实是一样的
vector<vector<int>> climbStairs(int n)
{
    // 其实说是 dfs，本质上就是用回溯暴搜+记忆化
    // 不过这题用记忆化？
    // 难道要用哈希表的键存一个个的子数组？
    function<void(vector<vector<int>>&, vector<int>&, int)> backtrack = [&](vector<vector<int>>& res, vector<int>& cur, int idx)
    {
        // 如果已经爬到了楼顶，那么就可以记录路径结果并返回了
        if(idx == n)
        {
            res.push_back(cur);
            return;
        }
        // 否则，考虑当前下标 idx 之后可以跳的位置 (idx+1, idx+2)
        // 有可行的，就跳过去
        cur.push_back(idx+1);
        backtrack(res, cur, idx+1);
        cur.pop_back();
        if(idx+2 <= n)
        {
            cur.push_back(idx+2);
            backtrack(res, cur, idx+2);
            cur.pop_back();
        }
    };
    vector<vector<int>> res;
    vector<int> cur;
    backtrack(res, cur, 0);
    return res;
}

int main()
{
    int n = 5;
    vector<vector<int>> res = climbStairs(n);
    for(int i = 0; i < res.size(); ++i)
    {
        for(int j = 0; j < res[i].size(); ++j)
        {
            cout << res[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}