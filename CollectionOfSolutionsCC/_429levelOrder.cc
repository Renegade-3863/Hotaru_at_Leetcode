/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

#include "Solution.h"

vector<vector<int>> Leetcode401_500::Solution::levelOrder(Node* root)
{
    // 层序遍历的最简单方法永远都是 BFS
    // 我们依然是使用一个队列来保存所有的 "当前层" 结点，按层对 N 叉树进行遍历即可
    if(!root)
    {
        return {};
    }
    queue<Node*> q;
    vector<vector<int>> res;
    // 把根结点入队
    q.push(root);
    while(!q.empty())
    {
        // 因为我们需要按层进行遍历，所以这里也按层进行检查
        int n = q.size(), idx = res.size();
        res.push_back(vector<int>());
        for(int i = 0; i < n; ++i)
        {
            // 弹出当前层的下一个结点
            Node* cur = q.front();
            q.pop();
            // 先把这个结点的值加到答案数组中
            res[idx].push_back(cur->val);
            // 之后遍历保存的整个数组，找出所有下一层的对应新结点进行添加
            for(const auto& nxt : cur->children)
            {
                q.push(nxt);
            }
        }
    }
    // 遍历完成，返回结果即可
    return res;
}