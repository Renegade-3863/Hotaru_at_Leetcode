#include "Solution.h"

int Leetcode201_300::Solution::closestValue(Leetcode201_300::TreeNode* root, double target)
{
    // 如果是一道二叉树问题，我们其实还是应该使用递归方法求解，但是本题限制了二叉树本身还是一棵二叉搜索树
    // 那么我们可以某种程度上利用有序的特性进行二分加速
    // 首先，我们规定：递归函数 int dfs(subRoot, target) 返回的值是以 root 为根的子树中距离 target 最近的数的值
    // 于是我们可以执行类似下面的递归搜索过程
    // 先看根结点和 target 的距离
    // double diff1 = abs(target-subRoot->val)
    // 之后还需要判断：subRoot 的左子树中距离 target 最近的数的值和 target 的差值
    // double diff2 = abs(target-dfs(subRoot->left, target))
    // 以及右子树中距离 target 最近的数的值和 target 的差值
    // double diff3 = abs(target-dfs(subRoot->right, target))
    // 那么 dfs(subRoot, target) 就是 min(min(diff1, diff2), diff3)
    // 基于上面普通二叉树的策略，我们下面考虑如何利用二叉搜索树的性质
    // 我们可以发现：
    // 如果 root->val 本身是大于 target 的，那么我们显然不可能在 root->right 这棵子树中找到更靠近 target 的结果
    // 因而我们可以向左深入检查
    // 如果 root->val 本身是小于 target 的，那么我们显然不可能在 root->left 这棵子树中找到更靠近 target 的结果
    // 因而可以向右深入检查
    // 此时写出代码就不难了
    int res = -1;
    double min_diff = DBL_MAX;
    bool exist = false;
    function<void(TreeNode*)> dfs = [&](TreeNode* subRoot)
    {
        // 递归的结束条件：子根结点为空结点
        if(!subRoot)
        {
            return;
        }
        if(min_diff > abs(subRoot->val-target))
        {
            res = subRoot->val;
            min_diff = abs(subRoot->val-target);
        }
        // 保证题目中的额外要求，如果有多个答案，那么返回最小的那一个
        else if(min_diff == abs(subRoot->val-target))
        {
            res = min(res, subRoot->val);
        }
        // 判断应该往哪边继续深入
        if(target < subRoot->val)
        {
            // 向左深入
            dfs(subRoot->left);
        }
        // 如果找到了距离为零的结点，那么也不用继续深入了，可以直接结束递归
        else if(target == subRoot->val)
        {
            return;
        }
        else
        {
            // 向右深入
            dfs(subRoot->right);
        }
    };
    // 调用 dfs 即可
    dfs(root);
    return res;
}