#include "Solution.h"

Leetcode501_600::Soltuion::Soltuion::Soltuion(vector<int>& w)
{
    // 据说是比较经典的负载均衡算法，根据进线程的执行成本动态分配 CPU 资源的一种算法
    // 用简单的 rand() 自带函数和一个前缀数组即可完成这种逻辑
    // 我们考虑执行下面的方法：
    // 把每个任务的权重值累加起来，模拟一种类似 "堆" 的结构
    // 比如，有下面三个任务：
    // {3, 2, 8}
    // 我们累加出下面的三个前缀和：
    // {3, 5, 13}
    // 之后，我们用 rand() 函数做 [0, 12] 之间的随机
    // 如果随机出来的数位于 [0, 2] 之间，那么我们返回下标 0，代表选择第一个任务 
    // 如果随机出来的数位于 [3, 4] 之间，那么我们返回下标 1，代表选择第二个任务
    // 最后，如果随机出来的数位于 [5, 12] 之间，那么我们返回下标 2，代表选择第三个任务
    // 这样，我们选择第一个任务的概率就是 3/13，第二个任务的概率就是 2/13，第三个任务的概率就是 8/13，正好和它们的权重相同
    // 描述完了算法，实现就是水到渠成了
    // 我们在这里遍历 w，计算前缀和数组
    int pre = 0, n = w.size();
    // 别忘了给 preSum 重划内存
    preSum.resize(n);
    for(int i = 0; i < n; ++i)
    {
        pre += w[i];
        preSum[i] = pre;
    }
    // 计算完成，结束构造即可
}

int Leetcode501_600::Soltuion::Soltuion::pickIndex()
{
    // 我们利用构造时拿到的前缀数组进行随机数生成即可
    // 注意，自己写的话，要记得 include <random> 库！
    // 同时注意，我们假设的是：preSum 至少有一个元素
    int ranNum = rand() % preSum[preSum.size()-1];
    // 由于 preSum 本身是一个有序的数组，我们使用二分查找找出 "第一个大于这个随机数的 preSum 元素的下标" 即可
    // 定义两个边界，left 和 right
    int left = 0, right = preSum.size()-1;
    // [left, right] 是可能存在答案的区间，当 left == right 时，答案就确定了
    // 我们把答案记录到 res 中即可
    int res = right;
    while(left <= right)
    {
        // 取中点
        int mid = ((right-left)>>1)+left;
        if(preSum[mid] > ranNum)
        {
            // 满足条件，向左夹逼 right 指针，修改 res
            res = mid;
            right = mid-1;
        }
        else
        {
            // 不满足条件，只移动 left 指针即可
            left = mid+1;
        }
    }
    // 循环结束时， res 就是我们要的随机答案
    return res;
}