#include "Solution.h"

vector<vector<int>> Leetcode1_100::Solution::combinationSum2(vector<int>& candidates, int target) 
{
    // 给定一个候选编号集合 candidates 和一个目标值 target，要求找出 candidates 中所有可以使数字和为 target 的组合
    // 39题的变体，仍然是回溯类的问题，只是这次 candidates 数组中可能会出现重复元素，并且要求 candidates 中的每个元素都只能使用一次
    // 我们依然可以采用类似回溯的策略进行求解
    // 为了去重，依然需要对 candidates 数组进行排序，保证其按非降序排列
    sort(candidates.begin(), candidates.end());
    // 之后进行常规的回溯过程，修改去重方案即可
    /*
        res 是全局的答案序列，记录所有可行的结果(不重复)
        rec 记录本地的(可能)符合要求的子序列
        cur 记录当前 rec 中元素的和
        idx 记录当前检查元素的其实下标
    */
    function<void(vector<vector<int>>&, vector<int>&, int, int) backtrack = [&](vector<vector<int>>& res, vector<int>& rec, int cur, int idx)
    {
        // 切入点依旧是从 idx 开始，按序检查每个数字是否可以填入当前位置
        for(int i = idx; i < candidates.size(); ++i)
        {
            // 先按传统的回溯方案写好代码
            // 注意，由于我们明确了数组中可能会存在重复元素
            // 因而我们原先的，按序检查，只检查不大于已经选取过的元素的策略不再完美
            // 可能会出现下面这种重复：
            // [1, 2, 2, 2, 3, 6, 7] target = 7
            // 第一次选了第一个2，之后我们可以选出一个 [2, 2, 3] 序列，其中前两个2是上面序列中的前两个2
            // 第二次选了第二个2，之后我们也可以选出一个 [2, 2, 3] 序列，其中前两个2是上面序列中的后两个2
            // 而我们也不能把遍历条件改成只遍历比已经选取过的元素大的元素，因为这样会丢掉所有 [2, 3, 3] 的结果
            // 其实解决办法还是简单的
            // 我们要做的只是想办法剪掉第二种情况即可
            // 如果画一下递归树，我们可以想明白，其实就是同一层中，我们不选取任何重复的元素 (即不会向同一个位置上重复填写相同的元素)
            // 这样就可以避免上面的这种重复了
            if(i > idx && candidates[i] == candidates[i-1])
            {
                continue;
            }
            // 添加当前元素
            rec.push_back(candidates[i]);
            // 这里和39题稍有不同，由于本题限定我们每种元素只能使用1次，因而我们这里用过了下标为 i 的元素，下一个元素就只能从 i+1 下标处选取了
            backtrack(res, rec, cur+candidates[i], i+1);
            rec.pop_back();
        }
    };
    vector<vector<int>> res;
    vector<int> rec;
    backtrack(res, rec, 0, 0);
    return res;
}