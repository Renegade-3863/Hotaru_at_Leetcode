#include "Solution.h"

vector<int> Leetcode501_600::Soltuion::boundaryOfBinaryTree(Leetcode501_600::TreeNode* root)
{
    // 二叉树类的问题基本都可以用类似递归的方式来解决
    // 我们用 res 数组存储最后的边界值
    vector<int> res;
    // 如果面试的时候要自己做，对于刷惯了常规套路类算法题的人来说
    // 这种简单的创新题一时间还真不好想到合适的解法
    // 其实基本思路很简单
    // 我们分三次遍历整棵树
    // 第一轮，寻找所有的左边界结点
    // 第二轮，寻找所有的右边界结点
    // 最后一轮，寻找所有的叶结点
    // 我们根据每一轮遍历的具体要求分开写一下遍历函数即可
    // 左边界遍历函数，我们的假设是：调用 dfsL 函数的参数结点 root 要么是左边界结点候选人，要么是叶结点，否则就是空结点
    function<void(TreeNode*)> dfsL = [&](TreeNode* root) -> void
    {
        // 如果 root 本身是空的，直接返回即可
        if(!root)
        {
            return;
        }
        // 当前结点不是叶子结点，那么它就一定是一个左边界结点
        if(root->left || root->right)
        {
            res.push_back(root->val);
        }
        // 如果 root 左孩子非空，那么根据要求，我们进一步往左检查更多边界结点即可，不用管右孩子了
        if(root->left)
        {
            // 此时我们认为 root->left 是左边界的候选人，进一步递归
            dfsL(root->left);
            return;
        }
        // 否则，root 左孩子为空，那么只有当右孩子非空时，我们才进一步检查，否则，当前结点就不在左边界中
        if(root->right)
        {
            // 此时我们认为 root->right 是右边界的候选人，进一步递归
            dfsL(root->right);
        }
        return;
    };
    // dfsR 定义和 dfsL 是对称的
    function<void(TreeNode*)> dfsR = [&](TreeNode* root) -> void
    {
        if(!root)
        {
            return;
        }
        if(root->left || root->right)
        {
            res.push_back(root->val);
        }
        if(root->right)
        {
            dfsR(root->right);
            return;
        }
        if(root->left)
        {
            dfsR(root->left);
        }
        return;
    };
    // 最后是寻找叶结点的函数，这个就很简单了
    function<void(TreeNode*)> dfs = [&](TreeNode* root) -> void
    {
        if(!root)
        {
            return;
        }
        // 找到了一个叶子结点，记录并返回即可
        if(!root->left && !root->right)
        {
            res.push_back(root->val);
            return;
        }
        // 先序遍历，之后检查左右子树中的叶子结点
        dfs(root->left);
        dfs(root->right);
    };
    // 最后是对上面函数的调用
    if(!root)
    {
        return res;
    }
    // 根结点默认在边界中
    res.push_back(root->val);
    // 细节处理：如果根结点就是叶子结点，那么我们直接返回，避免重复添加
    if(!root->left && !root->right)
    {
        return res;
    }
    dfsL(root->left);
    dfs(root);
    // 注意，题目要求右边界要逆序出现在结果数组结尾，所以我们这里记录一下右边界开始下标，最后对这部分元素进行一下反转
    int idx = res.size();
    dfsR(root->right);
    reverse(res.begin()+idx, res.end());
    return res;
}