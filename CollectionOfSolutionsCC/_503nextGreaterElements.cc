#include "Solution.h"

vector<int> Leetcode501_600::Soltuion::nextGreaterElements(vector<int>& nums)
{
    // 一般处理循环数组的逻辑都不难
    // 既然前面的元素对于后面的元素是 "可见" 的，那么我们就修改一下原数组，在后面接一组 nums[0..nums.size()-2] 中的元素即可
    // 之后，我们就可以直接用单调栈处理这些元素了
    // 我们这样利用栈来处理这个重构后的数组 arr
    // 利用 arr[nums.size(), arr.size()-1] 中的元素，倒序构建单调栈中的初始序列 (单调栈中从栈顶到栈底值逐渐增加)
    // 重构 nums 数组
    int n = nums.size();
    vector<int> res(n, -1);
    nums.resize(2*n-1);
    // 对后面的 n-1 个位置进行数据填入
    for(int i = 0; i < n-1; ++i)
    {
        nums[i+n] = nums[i];
    }
    // 之后构建单调栈
    stack<int> stk;
    for(int i = 2*n-2; i >= n; --i)
    {
        // 处理 nums[i]
        while(!stk.empty() && stk.top() <= nums[i])
        {
            stk.pop();
        }
        stk.push(nums[i]);
    }
    // 之后，从 nums[n-1] 开始，同样的逻辑倒序遍历，这次往 res 中记录结果即可
    for(int i = n-1; i >= 0; --i)
    {
        while(!stk.empty() && stk.top() <= nums[i])
        {
            stk.pop();
        }
        if(!stk.empty())
        {
            res[i] = stk.top();
        }
        // 别忘了压栈
        stk.push(nums[i]);
    }
    return res;
}   