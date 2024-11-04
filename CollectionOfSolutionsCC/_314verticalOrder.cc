#include "Solution.h"

vector<vector<int>> Leetcode301_400::Solution::verticalOrder(Leetcode301_400::TreeNode* root)
{
    // 想明白了其实本质上还是 DFS
    // 我们无非需要记录一个中间过程标记：
    // 当前结点相对于树中最左侧的那个结点的 offset 是多少
    // 如果从最左侧的那个结点，(按列)右移 i 个结点可以到达当前结点，那么我们就把这个结点的值添加到最终答案的第 i 行即可
    // 同时注意到题目要求的遍历顺序，我们不难想到需要先序遍历
    // 具体的内容到代码中理解即可
    if(!root)
    {
        return {};
    }
    unordered_map<int, vector<int>> res;
    // 订正一下前面说要进行前序遍历的错误方案，按照题目给出的例子，本题应该使用的遍历方法其实是 BFS
    // 那么我们保存到队列中的就不能是简单的结点指针本身，应该附带上这个结点到最左侧结点的 offset 值
    queue<pair<TreeNode*, int>> q;
    // 首先添加根结点及其 offset
    q.push(make_pair<TreeNode*&, int>(root, 0));
    // 记录一个哈希表的最小键值变量 minimum 和一个哈希表的最大键值变量 maximum
    int minimum = 0, maximum = 0;
    // 逐层向下遍历
    while(!q.empty())
    {
        const auto& p = q.front();
        // 根据 offset 值添加到对应的行中
        res[p.second].push_back(p.first->val);
        minimum = min(minimum, p.second);
        maximum = max(maximum, p.second);
        // 检查当前结点的左右孩子，如果有孩子，根据当前父结点的 offset 计算孩子的 offset 并组合添加到队列中
        if(p.first->left)
        {
            int nxt = p.second-1;
            q.push(make_pair<TreeNode*&, int&>(p.first->left, nxt));
        }
        if(p.first->right)
        {
            int nxt = p.second+1;
            q.push(make_pair<TreeNode*&, int&>(p.first->right, nxt));
        }
        q.pop();
    }
    // 遍历完成，根据哈希表构建并返回结果即可
    vector<vector<int>> ret(maximum-minimum+1, vector<int>());
    for(const auto& info: res)
    {
        for(int i = 0; i < info.second.size(); ++i)
        {
            ret[info.first-minimum].push_back(info.second[i]);
        }
    }
    return ret;
}