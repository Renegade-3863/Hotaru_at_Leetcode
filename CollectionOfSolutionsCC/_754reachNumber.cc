#include "Solution.h"

int Leetcode701_800::Soltuion::reachNumber(int target)
{
    // 个人思考：如果用传统的计算机思维来考虑这道题
    // 应该 BFS 是最合适的切入点了
    // 我们可以把每一个格子和到达这个格子时走的步数的信息对当成一个 BFS 结点
    // 这二者可以唯一标识一个状态
    // 我们最终需要的是，能取到的最早的那个格子下标为 target 的状态
    // q 队列用于保存等待处理的状态信息对
    // 元信息为：[idx, step]
    queue<pair<int, int>> q;
    // 初始状态为：idx 为 0，step 为 1，即从位置 0 开始，可以往左/往右走 1 步
    q.emplace(0, 1);
    // res 代表目前为止已经走了的总步数，也是最后要返回的结果
    int res = 0;
    while(!q.empty())
    {
        // 按层进行扩散
        int n = q.size();
        // 多走一步
        ++res;
        for(int i = 0; i < n; ++i)
        {
            pair<int, int>& cur = q.front();
            // 分别尝试往左和往右走
            // 这里如果走到一个之前到过的格子，但是可走的步数不一样，我们还要不要保留
            // 个人认为有必要，因为可以走的步数不一样（）
            // 先尝试往左走
            int nxtIdx = cur.first-cur.second;
            if(nxtIdx == target)
            {
                // 如果这一步走到了目标位置，我们直接返回 res 就行，这一定是移动次数最少的方案
                return res;
            }
            // 否则，把这一步记录到 q 中，以备下一层使用
            q.emplace(nxtIdx, cur.second+1);
            // 再尝试往右走
            nxtIdx = cur.first+cur.second;
            if(nxtIdx == target)
            {
                return res;
            }
            q.emplace(nxtIdx, cur.second+1);
            // 弹出刚刚检查完的这个状态
            q.pop();
        }
    }
    // 理论上不会执行到这一行，但是规定 "如果找不到可行解"，就返回（）
    return -1;
}

// 上面的 BFS 方案在 31/73 处 MLE 了
// 这也很正常，因为一旦 target 的绝对值变得很大，那么整体的状态数量就会非常大，所以这种 CS-oriented 的 BFS 算法就很明显不合适了
// 看了下题解区，又是一道脑筋急转弯的题（）
// 这里引用一下题解区 yuki 大佬的解法：https://leetcode.cn/problems/reach-a-number/solutions/23608/deng-jie-yu-shu-zu-tian-jia-zheng-fu-hao-wen-ti-by/
// 简单来说就是：这道题目是在处理一个等差数列：
// 1, 2, 3, 4, ...
// 我们是在给这些数字前面添加符号，想要让这些数字加上符号后，总和为 target
// yuki 大佬给出了这几个的特征值：
// n 为所有符号为负的元素绝对值之和
// s 为所有元素之和
// p 为所有符号为正的元素绝对值之和
// 那么有 p+n = s
// 同时有 p-n = target
// 两式相减，有：
// 2*n = s-target (s 为 (i+1)*i/2 这样的等差数列和公式)
// 换句话说，我们要找的就是可以使得 (i+1)*i/2-target 为偶数，且不小于 0 的最小的那个 i
// 转换成一元二次方程：
// i^2/2+i/2-target >= 0 且为偶数
// 我们一个个数来试就行了
int reachNumber(int target)
{
    // 如果 target 为负数，那么很明显结果就是和正数相反的，只是左右对调了而已，我们可以合并处理
    if(target < 0)
    {
        target = ~target+1;
    }
    int res = 1;
    while(true)
    {
        int s = (res+1)*res/2;
        if(s >= target && (s-target)%2 == 0)
        {
            return res;
        }
        ++res;
    }
    return -1;
}