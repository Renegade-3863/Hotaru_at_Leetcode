#include "Solution.h"

int Leetcode601_700::Soltuion::maxDistance(vector<vector<int>>& arrays)
{
    // 提出一个暴论：
    // 任何可能成为最终结果的绝对值，都一定是由两个数组的边界值引出的
    // 同时，一定是由一个极小值和一个极大值构成的 (这一点应该是毋庸置疑的)
    // 那么，我们可以简单对整个二维数组的每一行进行遍历
    // 记录所有已知元素中的最大值和最小值 (注意，这两个值不能来自同一个数组！！)
    // 最后，这两个值的距离就是我们的结果   
    // 考虑如何实现这个 "两个值不来自同一个数组" 的要求
    // 我们可以先确定一个最大值/最小值，而最小值/最大值按每个数组进行处理
    // 具体实现看代码即可
    // 如果 arrays.size() == 0，那么直接返回 0 即可
    int n = arrays.size();
    if(n == 0)
    {
        return 0;
    }
    // 初始化维护的右边界 (极大) 值，注意同步记录是哪一个数组提供了这个最大值
    int idx = 0, maximum = arrays[0][arrays[0].size()-1];
    for(int i = 1; i < n; ++i)
    {
        if(maximum < arrays[i][arrays[i].size()-1])
        {
            idx = i;
            maximum = arrays[i][arrays[i].size()-1];
        }
    }
    // 记录完成 maximum 和 idx，接下来遍历每一个数组的左边界，如果和 maximum 不是来自同一个数组，就记录距离
    int res = 0;
    for(int i = 0; i < n; ++i)
    {
        if(i != idx)
        {
            res = max(res, abs(maximum-arrays[i][0]));
            // 这一步只是为了防止全局极小值和极大值来自同一个数组
            res = max(res, abs(arrays[idx][0]-arrays[i][arrays[i].size()-1]));
        }
    }
    // 补充：实际上，可能全局极小值和极大值是来自同一个数组的，那么有可能这个极小值会和其它数组中的元素构造出更大的距离
    return res;
}