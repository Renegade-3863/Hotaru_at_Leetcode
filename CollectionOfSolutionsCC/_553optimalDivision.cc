#include "Solution.h"

string Leetcode501_600::Soltuion::optimalDivision(vector<int>& nums)
{
    // 脑筋急转弯，本题限制的 nums 数组中全部都是正整数
    // 那么很明显，我们只需要让除了第一个数以外，剩下后面的数先除好，剩下的分母就是最小的
    // 再用第一个数作为分子，那么这样除法得到的结果就是最大的了
    int n = nums.size();
    string res;
    for(int i = 0; i < n; ++i)
    {
        res.append(to_string(nums[i]));
        if(i < n-1)
        {
            res += "/";
        }
        if(i == 0 && n > 2)
        {
            res += "(";
        }
    }
    if(n > 2)
    {
        res += ")";
    }
    return res;
}