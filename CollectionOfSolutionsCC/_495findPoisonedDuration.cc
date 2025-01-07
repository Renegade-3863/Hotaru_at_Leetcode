#include "Solution.h"

int Leetcode401_500::Soltuion::findPoisonedDuration(vector<int>& timeSeries, int duration)
{
    // 简单题简单做，基本思路很简单，就是模拟
    // 我们从头开始遍历 timeSeries 数组，并维护两个指针：
    // right 指针：指代当前最靠右的 "艾希中毒了" 的时间值
    // left 指针：指代当前最后一个连续的 "艾希中毒了" 的时间段的左端点
    // 初始的 "中毒时间" 为 1
    // res 为最终的结果
    int res = 0;
    int right = -1, left = -1;
    // 遍历所有的时间区间，相应地更新 left 指针和 right 指针
    for(const int& series : timeSeries)
    {
        // 对于每一个下毒时间节点 series，我们都需要检查它和 [left, right] 区间的关系
        // 具体来说，series 时间点下毒，会影响的时间段是 [series, series+duration]
        // 我们需要判定这个区间是否包括了 right，并根据对应的比较结果做出后续处理
        // 1. right < series，此时是在艾希正常状态下被提莫下的毒，我们需要同步更新 left 和 right
        if(right < series)
        {
            // 在更新区间后，我们需要记录新区间的时间长度，这段时间内，无论有没有被再次下毒，艾希都处于中毒状态
            right = series+duration-1;
            left = series;
            res += (right-left+1);
        }
        // 2. right >= series 且 right <= series+duration 
        // 此时说明艾希是在中毒状态下被再次下毒的，所以我们需要按照 right 的值更新 [left, right] 
        // 同时也要更新 res
        else if(right >= series && right-duration <= series)
        {
            int tmp = right;
            right = series+duration-1;
            res += (right-tmp);
        }
        // 3. right >= series 且 right >= series+duration
        // 虽然这种情况应该不会发生，不过写一下也没问题
        // 此时说明新的 "中毒区间" 已经被包括了
        // 这时不用做任何事，跳过这个期间即可
    }
    return res; 
}