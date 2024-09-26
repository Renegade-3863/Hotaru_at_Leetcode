#include "Solution.h"

bool Leetcode101_200::Solution::isSymmetric(Leetcode101_200::TreeNode* root)
{
    // 简单的 DFS 类题目
    // check 函数定义：
    // 返回值为两棵子树是否互相对称
    // 判断两棵子树是否互相对称，我们需要做的事有三件
    // 1. 两棵子树的根结点值是否相等
    // 2. 左子树的左子树和右子树的右子树是否对称
    // 3. 左子树的右子树和右子树的左子树是否对称
    function<bool(TreeNode* left, TreeNode* right)> check = [&](TreeNode* l, TreeNode* r)
    {
        if(!l || !r)
        {
            return l == r;
        }
        return l->val == r->val && check(l->left, r->right) && check(l->right, r->left);
    };
    if(!root)
    {
        return true;
    }
    return check(root->left, root->right);
}

// 考虑如何用迭代方案实现上面的递归解法
bool isSymmetric(Leetcode101_200::TreeNode* root)
{
    // 使用一个队列来实现同行内部的结点比较
    // 我们要实现的是一对一对的结点比较
    // 假设现在我们有两个结点 left 和 right，它们位于一对互为镜像的位置上，那么此时我们要做的事情很简单
    // 1. 检查这两个结点的值是否相等
    // 2. 把它们各自的子结点按相对的顺序添加到队列中，保证下次连续弹出的两个结点还是位于一对镜像位置上的
    queue<TreeNode*> q;
    if(!root)
    {
        return true;
    }
    if(!root->left || !root->right)
    {
        return root->left == root->right;
    }
    q.push(root->left); q.push(root->right);
    // 在循环中维护这样的循环不变式：
    // 队列开头的两个元素一定是树中一对对称位置上的两个结点的指针
    // 这个循环不变式可以通过以下事实进行维护
    // 一对原本处于对称位置上的结点，左边的结点的左孩子和右边的结点的右孩子一定仍是处于对称位置上的
    // 左边结点的右孩子和右边结点的左孩子同理
    while(!q.empty())
    {
        TreeNode* l = q.front(); q.pop();
        TreeNode* r = q.front(); q.pop();
        
        // 检查是否值相等
        // 或者是不是出现了一个为空，一个非空的情况
        if(!l || !r)
        {
            if(l != r)
            {
                return false;
            }
            else
            {
                continue;
            }
        }
        if(l->val != r->val)
        {
            return false;
        }
        // 把各自的孩子进行添加
        q.push(l->left);
        q.push(r->right);
        q.push(l->right);
        q.push(r->left);
    }
    return true;
}