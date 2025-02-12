#include "Solution.h"

int Leetcode501_600::Soltuion::findMinDifference(vector<string>& timePoints)
{
    // 根据鸽笼原理，如果 timePoints 的长度不短于 1440 个，说明至少有一对重复的时间节点
    // 此时直接返回 0 即可
    // 简单的模拟类题目，按题目的要求，我们把时间转换成纯 "分钟" 的，比较好比较大小的方式，排好序后
    // 按顺序统计相邻时间之间间隔最小的即可
    // 首先，遍历 timePoints 数组，把 HH:MM 格式的时间转换成纯分钟的表示法
    int n = timePoints.size();
    if(n > 1440)
    {
        return 0;
    }
    vector<int> minTime(n, 0);
    for(int i = 0; i < n; ++i)
    {
        int min = 0, hour = 0, minute = 0, j = 0;
        // 解析出前两个字符，这两个字符代表 "小时"
        for(; j < 2; ++j)
        {
            hour = hour*10+(timePoints[i][j]-'0');
        }
        // hour 解析完成，累加到 min 中
        min += 60*hour;
        // 之后解析分钟，j 指针后移一位
        ++j;
        for(; j < 5; ++j)
        {
            minute = minute*10+(timePoints[i][j]-'0');
        }
        min += minute;
        // 解析完成，我们记录 min 即可
        minTime[i] = min;
    }
    // 转换完成，我们只需要对 minTime 排序，之后遍历检查差值即可
    sort(minTime.begin(), minTime.end());
    // 注意，检查的时候，别忘了最后一个值和第一个值之间的关系检查
    int res = 1440;
    for(int i = 1; i < n; ++i)
    {
        res = min(res, minTime[i]-minTime[i-1]);
    }
    // 检查最后一个值和第一个值
    res = min(res, 1440+(minTime[0]-minTime[n-1]));
    return res;
}