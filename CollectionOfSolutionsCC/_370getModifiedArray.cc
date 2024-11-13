#include "Solution.h"

vector<int> Leetcode301_400::Solution::getModifiedArray(int length, vector<vector<int>>& updates)
{
    // 第一想法是暴力模拟。。。
    // 看了眼官方题解，学到了差分数组的(应该是最本质的)用法
    // 对于这一题我们可以使用一个差分数组和一个初始值，来递推出最终的结果值
    // 注意到这样的事实：如果我们要修改一个区间内的元素，那么有下面的隐含细节：
    // 我们实际上只需要记录边界处的 "突变值"
    // 因为对一个区间内的所有值进行修改，并不会影响内部元素之间的 offset!
    // 所以我们根据每一个 update，对差分数组的对应位置进行修改即可
    // 记录一个差分数组，代表每两个数组元素之间的差值
    // 注意，我们捏合了最后的答案数组和对应的差分数组，所以这里的长度是 length 而不是 length-1
    vector<int> diff(length, 0);
    // 遍历所有的更新
    for(const auto& update : updates)
    {
        diff[update[0]] += update[2];
        if(update[1] < length-1)
        {
            // 更新区间后面的第一个元素的差值
            diff[update[1]+1] -= update[2]; 
        }
    }
    // 明确了所有的差值，我们只需要从头开始推断即可
    for(int i = 1; i < length; ++i)
    {   
        diff[i] += diff[i-1];
    }   
    return diff;
}