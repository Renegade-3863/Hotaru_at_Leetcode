#include "Solution.h"

int Leetcode601_700::Soltuion::widthOfBinaryTree(Leetcode601_700::TreeNode* root)
{
    // 浏览一遍题，就不难想到一个差不多可行的 BFS 解法了
    // 我们用一个数值对队列，保存每一层的所有结点以及它们对应的当前层位置信息
    // 比如 (5, 0) 就代表值为 5 的结点在当前层的第一个位置上
    // 之后，对于每一层，我们除正常按照 BFS 的方式扩散记录下一层结点以及对应位置信息外
    // 只需要多加一步，计算开头结尾两个结点的位置距离即可
    // 最后，所有距离保留最小值即可
    // q 用于保存上面描述的信息
    queue<pair<TreeNode*, unsigned long long>> q;
    q.emplace(root, 0);
    // res 为最终结果
    int res = 0;
    // 大框和传统的 BFS 没有任何区别
    while(!q.empty())
    {
        // tmp 记录当前层的已知最大宽度，初始为 0
        int n = q.size(), tmp = 0;
        bool inserted = false;
        for(int i = 0; i < n; ++i)
        {
            // 取出队头的一个信息块
            auto& info = q.front();
            if(i == 0)
            {
                tmp = info.second;
            } 
            if(i == n-1)
            {
                // 计算最大宽度
                tmp = info.second-tmp+1;
            }
            // 除此之外，正常扩散即可
            if(info.first->left)
            {
                // node->left 在该层的序号等于 node 的序号乘 2
                q.emplace(info.first->left, info.second*2);
            }
            if(info.first->right)
            {
                // node->right 在该层的序号等于 node 的序号乘 2 加 1
                q.emplace(info.first->right, info.second*2+1);
            }
            q.pop();
        }
        // 更新 res
        res = max(res, tmp);
    }
    return res;
}