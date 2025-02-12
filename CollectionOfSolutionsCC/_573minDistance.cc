#include "Solution.h"

int Leetcode501_600::Soltuion::minDistance(int height, int width, vector<int>& tree, vector<int>& squirrel, vector<vector<int>>& nuts)
{
    // 解决问题前，先分析题目想让我们干什么
    // 要完成题目的要求，我们需要做的是：
    // 第一步：从松鼠的起点走到一个松果的位置，并把它带到树下 (这一步是独立的，我们可以有 n 种选择，n 为松果的个数)
    // 之后，就是不断往返于树和其余各个松果之间，进行运输
    // 我们会发现，第二步这些路径的长度和，实际上在我们确定了第一次拿哪一个松果后，就已经是一个固定值了
    // 所以我们实际上只需要遍历 "第一次拿取的松果" 即可找出最终的结果
    // 如果要加速第二步的计算，我们实际上可以预处理一下每个松果到树的 "曼哈顿距离"
    // 曼哈顿距离应该都知道是什么东西...
    // 遍历一下处理出每个松果到树的曼哈顿距离 (后续编写代码时，发现这个映射也是不需要记录的，记录总距离即可)
    // 为了后续省掉第二层循环，这里用一个 totalDist 记录总的距离和
    int totalDist = 0;
    for(const auto& nut : nuts)
    {
        // 每一个 nut 是一个数值对，代表一个松果的坐标
        totalDist += abs(nut[0]-tree[0])+abs(nut[1]-tree[1]);
    }
    // 预处理完成，后续就是选择第一个拿的松果了
    int n = nuts.size();
    // res 记录最终结果
    int res = INT_MAX;
    for(int i = 0; i < n; ++i)
    {
        // 先拿取 nuts[i] 这个松果
        // 记录从 squirrel 到 nuts[i]，再到树的总距离
        int dist1 = abs(squirrel[0]-nuts[i][0])+abs(squirrel[1]-nuts[i][1]);
        int diff = abs(nuts[i][0]-tree[0])+abs(nuts[i][1]-tree[1]);
        res = min(res, 2*totalDist-diff+dist1);
    }
    return res;
}