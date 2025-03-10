#include "Solution.h"

// 再复习一次 "蓄水池算法"，感觉以后无论是已知很大长度的集合随机采样，还是未知长度的输入流随机采样，都可以沿用这种 O(n) 的随机化算法了
// 主要原因是：如果输入的样本数量非常大，无法同时存储进内存，那么直接采用伪随机数的那种 O(1) 算法就不可行了
// 蓄水池算法解决的基本问题模型就是：从一个很大的样本集中按完全随机的概率抽取 k 的样本出来
// 具体的数学证明过程请参考 doublexi 大佬的博客：https://www.cnblogs.com/doublexi/p/15665695.html
// 简单概括一下做法，就是根据已经遍历到的样本个数 i，如果 i <= k，那么我们先按 100%，也就是必选的概率把它们放到结果集合中 (前提是 k 这个数量级的数据必须是能够存到内存中的，不然这个问题没意义)
// 之后，对于序号 i > k 的那些样本，我们按照 k/i 的概率选取它们，并在选中它们的时候按照 1/k 的等概率替换前面 k 个已选元素中的任何一个
// 这里简单对上面算法的正确性做一下证明：
// 使用类似数学归纳法的方式来进行证明
// 我们假设，在检查第 i 个元素的时候 (i > k)，前 i-1 个元素中每一个元素被选中的概率是 pi-1
// 首先，不难知道：第 i 个元素被选入最后的 k 个元素的概率很明显是 k/i * 1/k = 1/i，这是满足要求的 "均等概率" 要求的，因为假设最后就要从这 i 个元素中选一个，所以 1/i 就是平均的概率
// 注意，根据类似数学归纳法的假设，我们假设下面的假设成立：在前面 i-1 个元素中任何一个的时候，对应元素被选中的概率都是 k/(i-1)
// 那么我们不难得出下面的等式：
// 对于前 i-1 个元素中的任何一个，它在第 i 个元素检查过后依然保留在前 k 个集合中的概率是：
// (它本身被保留在了前 k 个元素构成的集合中) 并且 ((第 i 个元素被选中，但是这个元素没有被替换) 或 (第 i 个元素没有被选中))
// 写成算式就是：
// k/(i-1) * (k/i*(k-1)/k+(i-k)/i) 
// 化简就是：k/(i-1) * (i-1)/i = k/i
// 所以我们就发现，无论前 i-1 个元素中的任何一个，或是当前的第 i 个元素，被最后保留在 k 个元素的集合中返回的概率都是 k/i
Leetcode401_500::Soltuion::Soltuion(vector<vector<int>>& rects)
{
    // 初始化步骤很简单，把坐标数组存到结构中即可
    recs = rects;
}

// 这道题的思路和水塘抽样有点类似，但不完全一样
// 基本的逻辑是这样：
// 我们按权重 (每个矩形中点点个数占总点数的比率) 计算选取每个矩形的概率
// 之后在每个矩形内按平均的概率选取一个点即可
// 而按权重比率选取每个矩形的过程有点像上面提到的水塘抽样
// 我们稍微进行一下推理：
// 假设给定三个矩形，内部占有的点数分别为 7，15，21
// 那么我们可以用类似上面水塘抽样的方法
// 按下面的逻辑遍历每个矩形：
// 对于第一个矩形，此时，累加的总点数为 7，其中有 7 个点属于矩形一
// 那么我们以 7/7 的概率选择这个矩形中的点
// 对于第二个矩形，此时，累加的总点数为 22，其中有 15 个点属于矩形二
// 那么我们以 15/22 的概率选择这个矩形中的点
// 在这种情况下，选取第一个矩形中的点的概率就是：
// 1*7/22 (前面保留了这个矩形的概率) * (这一轮没有选择第二个矩形将其替换的概率)
// 这样两个矩形选择的概率就分别是 15/22 和 7/22，符合权重比例
// 对于第三个矩形，此时，累加的总点数为 43，其中有 21 个点属于矩形三
// 我们以 21/43 的概率选择这个矩形中的点
// 在这种情况下，选取第一个矩形中的点的概率就是：
// 7/22*22/43 (前面保留了这个矩形的概率) * (这一轮没有选择第三个矩形将其替换的概率)
// 也就是 7/43 (也是符合权重的)
// 选取第二个矩形中的点的概率就是：
// 15/22*22/43 (前面保留了这个矩形的概率) * (这一轮没有选择第三个矩形将其替换的概率)
// 也就是 15/43 (同样符合权重)
// 不难想到这个问题可以推广到 k 个矩形的情况，也是可以完成按权重概率取样的目标的
vector<int> Leetcode401_500::Soltuion::Soltuion::pick()
{
    // idx 代表被选中的长方形的序号
    int idx = -1, cur = 0, n = recs.size(), curSum = 0;
    for(int i = 0; i < n; ++i)
    {
        // 获取当前矩形的四个顶点坐标
        int x1 = recs[i][0], y1 = recs[i][1], x2 = recs[i][2], y2 = recs[i][3];
        // 获取当前矩形中的顶点总个数
        cur = (x2-x1+1)*(y2-y1+1);
        // 累加总点数到 curSum 中
        curSum += cur;
        // 根据上面的逻辑，这里我们按照 cur/curSum 的概率保留 i 作为 idx，也就是最后选择的矩形序号
        if(rand()%curSum < cur)
        {
            idx = i;
        }
    }
    // 结束遍历，对选出的 idx 号矩形进行随机采样即可得出完全随机的一个点
    int x1 = recs[idx][0], y1 = recs[idx][1], x2 = recs[idx][2], y2 = recs[idx][3];
    return {x1+rand()%(x2-x1+1), y1+rand()%(y2-y1+1)};
}