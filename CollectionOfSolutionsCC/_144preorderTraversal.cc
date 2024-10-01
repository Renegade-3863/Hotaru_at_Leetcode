#include "Solution.h"

vector<int> Leetcode101_200::Solution::preorderTraversal(Leetcode101_200::TreeNode* root)
{
    // 终于是到了简单的模版题环节，不过虽然是模版，还是要稍微理解一下原理
    // 这里不给出递归版本的代码，我们实现一遍迭代方案
    // 栈用于存储所有还未完成访问的结点
    stack<TreeNode*> stk;
    // cur 存储当前手里拿着的结点
    TreeNode* cur = root;
    // 结果数组
    vector<int> res;
    // 循环结束的条件为：
    // 手里没有要检查的结点，并且栈中也没有还未完成访问的结点
    while(cur || !stk.empty())
    {
        if(cur)
        {
            // 如果当前有在检查的结点
            // 根据前序遍历的定义，我们访问这个结点的左子树之前，就可以对其进行访问了
            res.push_back(cur->val);
            // 我们接着尝试检查左子树
            stk.push(cur);
            cur = cur->left;
        }
        else
        {
            // 如果当前没有正在检查的结点，那么我们尝试拿出一个已经访问了左子树的结点
            cur = stk.top();
            // 访问完成，可以从栈中弹出这个已经完成了访问的结点
            stk.pop();
            // 继续向右访问右子树
            cur = cur->right;
        }
    }
    // 结束循环，返回最后的遍历结果
    return res;
}