#include "Solution.h"

vector<vector<int>> Leetcode501_600::Soltuion::outerTrees(vector<vector<int>>& trees)
{
    // 据说是经典的凸包算法，有时间来补一下基本的算法原理，本题个人认为最精妙的是 Andrew 算法
    // 从本质上来说，凸包算法的想法是基于叉乘运算的
    // 我们回顾一下叉乘的定义
    /*
        <a, b> x <c, d>
        假设两个向量相交的夹角是 a
        那么它们叉积的结果就是：
        | i  j  k |
        | a  b  0 |
        | c  d  0 |
        这个行列式
        计算出来的结果是：
        | b  0 |     | a  0 |     | a  b |
        | d  0 | i - | c  0 | j + | c  d | k
        也就是：
        (ad-bc)k
        一个方向单纯平行于 z 轴的向量
        而从绝对的值上来讲，叉积的结果又等于：
        |v1|*|v2|*sina*n (a 为两个向量之间的偏转角度，逆时针方向，n 为一个与 x-y 平面垂直的单位向量)
        从这个角度来说，我们就不难发现
        如果 a 这个偏转角度是小于 0 度的，那么根据 sin 函数曲线，我们不难发现，这个值就会是负数
        也就是说：第二个向量在第一个向量的右侧
        反之，就是说第二个向量在第一个向量的左侧
    */
    // 回顾了叉乘的定义和几何意义，我们回到这道题
    // 题目要求我们找 "凸包"
    // 就是勾勒出一个图形最外侧的轮廓
    // 文字来描述并不方便
    // 我们可以这样思考：
    // 将所有点按照 "优先小 x，再优先小 y" 的方式进行排序
    // 之后按顺序检查每一个点
    // 我们就可以实现：从左到右，从下到上的方式来遍历所有点
    // 在遍历整个点阵的过程中，我们每遇到一个新点，就检查所有后续点和它的连线 (后续点一定在它的右上方)
    // 那么如果我们遇到了一个后续点，这个点和已经在凸包集合中的某个点相连构成的向量，在凸包中最后一条边 (就是最后一条暂时认定为凸包轮廓的边) 的右侧 (向右偏)
    // 那么我们就可以丢弃这最后一个添加到凸包中的点，用这个新点替换它
    // 否则，我们就正常添加这个新点到凸包中，更新 "最后一条轮廓"
    // 重复这样的过程，直到我们检查完所有的点为止
    // 叉积函数
    function<int(const vector<int>&, const vector<int>&, const vector<int>&)> cross = [&](const vector<int>& p, const vector<int>& q, const vector<int>& r) -> int
    {
        return (q[0]-p[0])*(r[1]-q[1])-(q[1]-p[1])*(r[0]-q[0]);
    };
    int n = trees.size();
    if(n < 4)
    {
        // 点总数少于 4 个，这要么是一个点，要么是一条线，要么是一个三角形
        return trees;
    }
    // 按照 x 优先进行升序排列，如果 x 相同，就按 y 进行排序
    sort(trees.begin(), trees.end(), [&](const vector<int>& a, const vector<int>& b) -> bool {
        return a[0] == b[0] ? a[1] < b[1] : a[0] < b[0];
    });
    // 排序完成，我们考虑使用单调栈进行处理
    // v 这个单调栈中存储的是所有在最后的凸包中的点的下标
    vector<int> hull;
    // used 用于记录某个点是否已经被使用过了，换句话说，是否已经在凸包中了，如果已经在凸包中了，那么我们在后面求 "上半凸包" 的时候就不再需要检查对应下标上的结点信息
    vector<bool> used(n, false);
    hull.emplace_back(0);
    for(int i = 1; i < n; ++i)
    {
        // hull.size() <= 1 说明当前凸包内还没有至少两个结点，那么 i 这个点一定可以加入凸包中
        // 其实主要原因是后面的 hull.size()-2 这个下标取法需要保证合法
        // 如果这个新点导致前一条刚刚决定的 "候选边" 变成内凹的了，那么我们就丢弃前面这个点
        while(hull.size() > 1 && cross(trees[hull[hull.size()-2]], trees[hull.back()], trees[i]) < 0)
        {
            // 标记为 "不在凸包中"
            used[hull.back()] = false;
            // 弹出即可
            hull.pop_back();
        }
        // 把 i 这个点添加到凸包中
        used[i] = true;
        // 压栈
        hull.emplace_back(i);
    }
    // 之后是找上半凸包
    int m = hull.size();
    for(int i = n-2; i >= 0; --i)
    {
        if(!used[i])
        {
            while(hull.size() > m && cross(trees[hull[hull.size()-2]], trees[hull.back()], trees[i]) < 0)
            {
                used[hull.back()] = false;
                hull.pop_back();
            }
            used[i] = true;
            hull.emplace_back(i);
        }
    }
    hull.pop_back();
    vector<vector<int>> res;
    for(auto& v : hull)
    {
        res.emplace_back(trees[v]);
    }
    return res;
}