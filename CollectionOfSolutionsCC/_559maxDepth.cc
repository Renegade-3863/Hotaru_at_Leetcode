#include "Solution.h"

int Leetcode501_600::Soltuion::maxDepth(Node* root)
{
    // 简单题简单做
    // 我们对整棵树进行 BFS 遍历即可找出这棵树的最大深度
    if(!root)
    {
        return 0;
    }
    queue<Node*> q;
    q.push(root);
    int depth = 0;
    while(!q.empty())
    {   
        // 每多遍历一层，深度就加 1
        ++depth;
        int n = q.size();
        // 遍历当前层
        for(int i = 0; i < n; ++i)
        {
            Node*& cur = q.front();
            // 检查 cur 所有的孩子结点
            for(const auto& child : cur->children)
            {
                // 把 child 添加到队列中
                q.push(child);
            }
            q.pop();
        }
    }
    return depth;
}