#include "Solution.h"

vector<vector<int>> Leetcode301_400::Solution::findLeaves(Leetcode301_400::TreeNode* root)
{
    if(!root)
    {
        return {};
    }
    // 第一印象：这不就是拓扑排序吗？
    // 直接思考把这个二叉树转成图来处理
    // 我们记录每个结点的入度，之后按照传统的拓扑排序来处理即可
    unordered_map<TreeNode*, int> indegrees;
    // 邻接表记录每个结点指向的其它结点
    unordered_map<TreeNode*, vector<TreeNode*>> adjList;
    // 对这棵二叉树进行遍历，确认每个结点的入度
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty())
    {
        TreeNode* cur = q.front();
        indegrees[cur] = 0;
        if(cur->left)
        {
            q.push(cur->left);
            ++indegrees[cur];
            adjList[cur->left].push_back(cur);
        }
        if(cur->right)
        {
            q.push(cur->right);
            ++indegrees[cur];
            adjList[cur->right].push_back(cur);
        }
        q.pop();
    }
    // 此时我们就拿到了所有结点的入度信息
    // 考虑开始拓扑排序
    // 复用上面的队列
    for(const auto& indegree : indegrees)
    {
        if(indegree.second == 0)
        {
            q.push(indegree.first);
        }
    }
    // 最终的结果数组
    vector<vector<int>> res;
    while(!q.empty())
    {
        int n = q.size();
        // 添加一层子数组
        res.push_back(vector<int>());
        for(int i = 0; i < n; ++i)
        {
            TreeNode* cur = q.front();
            res[res.size()-1].push_back(cur->val);
            // 修改对应的指向结点的入度
            for(const auto& nxt : adjList[cur])
            {
                if(--indegrees[nxt] == 0)
                {
                    q.push(nxt);
                }
            }
            q.pop();
        }
    }
    // 返回结果即可
    return res;
}