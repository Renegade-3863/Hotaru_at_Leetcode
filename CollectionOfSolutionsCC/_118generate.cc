#include "Solution.h"

vector<vector<int>> Leetcode101_200::Solution::generate(int numRows)
{
    // 本题我们依然可以使用上层信息来更新下层值
    // 注意到以下事实：
    // 下标为 i 的层，层内应该有 i+1 个值
    // 当前行内下标为 j 的位置上的值等于上一行下标为 j-1 的位置上的值和 上一行下标为 j 的位置上的值的和
    // 如果 j-1 超出了上一行元素的下标域或者 j 本身超出了上一行元素的下标域，我们就简单地把当前行的这个元素赋值为1即可
    // 代码只需模拟上述过程即可
    vector<vector<int>> res = {{1}};
    for(int i = 1; i < numRows; ++i)
    {
        res.push_back(vector<int>(i+1, 0));
        // 填充当前行
        for(int j = 0; j < i+1; ++j)
        {
            int upLeft = j-1 >= 0 ? res[i-1][j-1] : 0;
            int upRight = j < i ? res[i-1][j] : 0;
            res[i][j] = upLeft+upRight;
        }
    }
    return res;
}