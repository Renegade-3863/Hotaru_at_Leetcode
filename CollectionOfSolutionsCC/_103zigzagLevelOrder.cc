#include "Solution.h"

vector<vector<int>> zigzagLevelOrder(Leetcode101_200::TreeNode* root)
{
    // 所谓的锯齿形层序遍历，其实就是，偶数层(从0开始计下标)从左到右遍历
    // 奇数层从右到左遍历的变种 BFS
    // 可以使用队列来实现
    queue<TreeNode*> q;
    if(!root)
    {
        return {};
    }
    vector<vector<int>> res;
    q.push(root);
    // 和单纯的层序遍历一样用来记录层号，这里也可以用来判断当前层应该从左到右遍历还是从右到左遍历
    int idx = 0;
    while(!q.empty())
    {
        // 先获取当前层的结点个数
        const int n = q.size();
        // 一次初始化，分配足够的空间，避免后续多次重复 push_back
        res.push_back(vector<int>(n, 0));
        for(int i = 0; i < n; ++i)
        {
            TreeNode* cur = q.front(); q.pop();
            // 如果当前层是偶数层，那么要从左到右添加元素
            if(idx % 2 == 0)
            {
                res[idx][i] = cur->val;
            }
            // 如果当前层是奇数层，那么要从右到左添加元素
            else
            {
                res[idx][n-i-1] = cur->val;   
            }
            if(cur->left)
            {
                q.push(cur->left);
            }
            if(cur->right)
            {
                q.push(cur->right);
            }
        }
        // 每添加完一层结点，别忘了更新层号
        ++idx;
    }
    // 结束后返回全局结果即可
    return res;
}