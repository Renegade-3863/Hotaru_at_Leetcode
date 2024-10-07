#include "Solution.h"

Leetcode101_200::Solution::BSTIterator::BSTIterator(Leetcode101_200::TreeNode* root)
{
    // 初始化过程，我们需要找到中序遍历的第一个结点，并在内部栈中存储路径信息
    this->cur = root;
    while(cur)
    {
        this->stk.push(cur);
        cur = cur->left;
    }
    // 一直向左不断深入到空为止，根据 BST 的性质，此时栈顶的结点就是中序第一个结点
    // 初始化完成
}

int Leetcode101_200::Solution::BSTIterator::next()
{
    // 要求返回下一个中序遍历结点信息
    // 我们直接进行和迭代版中序遍历相同的方式即可
    // 弹出栈中的结点
    this->cur = stk.top();
    int ret = this->cur->val;
    stk.pop();
    // 再向右深入一层，并再次不断向左深入，记录路径到本地栈中
    cur = cur->right;
    while(cur)
    {
        this->stk.push(cur);
        cur = cur->left;
    }
    // 处理完成，返回结果
    return ret;
}

bool Leetcode101_200::Solution::BSTIterator::hasNext()
{
    // 要求判断是否还有下一个结点，我们只需要检查栈中是否还有结点即可
    return !stk.empty();
}