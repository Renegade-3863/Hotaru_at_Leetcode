#include "Solution.h"

int Leetcode601_700::Soltuion::pathSum4(vector<int>& nums)
{
    // 先读懂题意，遇到变种题型，明确它的要求是最重要的
    // 首先，nums 是一个压缩信息数组，我们可能会需要一个解析函数 analyze，来对 nums 中的每一个元素进行拆分
    // 其次，明确一点，我们依然需要明确树的结构，因为题目要求的是 "路径总和"
    // 个人认为 DFS 比较适合这道题的要求
    // 有一个小问题：
    // 我们怎么知道，我们遍历到的一个结点是不是叶结点？
    // 想到这里，或许我们还是需要重记录一下这棵树的基本结构，用更容易检查的结构：哈希表
    // 可以用一个二维哈希表来记录："某一层 i，有没有序号为某个值 j 的结点"
    // 有了这份信息，我们就可以在第二轮 DFS 的时候，知道某个数据代表的结点是不是叶子结点了
    // 明确了具体的思路，我们再考虑一些实现细节，这道题就不难了
    unordered_map<int, unordered_map<int, int>> info;
    // 第二步：对 nums 进行遍历
    for(const auto& num : nums)
    {
        // 对每一个 num，先进行解析
        int d = num/100;
        int p = num/10-d*10;
        int v = num%10;
        // 之后考虑利用 d, p, v 三个变量来更新 info 哈希表
        // cout << "(" << d << ", " << p << "): " << v << endl;
        info[d][p] = v;
    }
    // 之后，我们设计一个 dfs(或者叫 backtrack 也可以) 函数，对这棵树进行深度搜索，直到最后计算完所有的路径总和
    int res = 0;
    // path 作为回溯的动态值，用于记录当前检查到的路径的权值和
    int path = info[1][1];
    function<void(int, int)> backtrack = [&](int depth, int pos) -> void
    {
        // cout << depth << ", " << pos << endl;
        // 设定基本情况，如果 (depth, pos) 代表的结点是一个叶结点，我们就记录 path 到 res 中，并直接返回即可
        // 要么 depth+1 没有结点，要么有结点，但是这个 2*pos 和 2*pos+1 这两个位置上没有结点
        if(info.count(depth+1) == 0 || (info[depth+1].count(2*pos) == 0 && info[depth+1].count(2*pos-1) == 0))
        {
            // cout << path << endl;
            res += path;
            return;
        }
        // 其它情况，(depth, pos) 不是叶子结点，那么我们就可以继续向 path 中累加左右孩子结点的权值，并进行深入
        // 这就是回溯的传统操作了
        // 先尝试往左走
        if(info[depth+1].count(2*pos-1))
        {
            // 左侧有结点，深入
            path += info[depth+1][2*pos-1];
            backtrack(depth+1, 2*pos-1);
            // 回溯
            path -= info[depth+1][2*pos-1];
        }
        // 再尝试往右走
        if(info[depth+1].count(2*pos))
        {
            // 右侧有结点，深入
            path += info[depth+1][2*pos];
            backtrack(depth+1, 2*pos);
            // 回溯
            path -= info[depth+1][2*pos];
        }
        // 尝试完成，结束函数
    };
    backtrack(1, 1);
    return res;
}