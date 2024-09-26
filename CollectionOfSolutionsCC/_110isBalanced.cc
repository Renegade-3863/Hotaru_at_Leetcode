#include "Solution.h"

// 不带记忆化，单纯 DFS
bool Leetcode101_200::Solution::isBalanced(Leetcode101_200::TreeNode* root)
{
    // 要求判断传入的二叉树是否是平衡的
    // 同样可以使用按定义递归的方法来执行判断
    // 平衡二叉树的定义是：该二叉树左右子树的高度差不超过1
    // 那么我们可以设计一个专门用于检查子树最大高度的函数 height
    // 这个函数也应该是递归定义的
    // height(subRoot)
    // 返回值为以 subRoot 作为根结点的子树的最大高度
    function<int(TreeNode*)> height = [&](TreeNode* subRoot)
    {
        // 如果子树为空树，直接返回0，递归结束条件
        if(!subRoot)
        {
            return 0;
        }
        // 如果子树非空，则高度至少为1
        // 记录一个全局的最大高度
        int h = 1;
        // 分别递归计算左右两侧的子树高度
        int leftHeight = height(subRoot->left), rightHeight = height(subRoot->right);
        // 当前子树的高度等于两侧子树高度更大的那一个加1
        h += max(leftHeight, rightHeight);
        // 返回结果
        return h;
    };
    // 有了上面的求解高度的 helper function，我们就可以编写外层的递归函数了
    // 封装一层，balanceCheck 函数的返回值是这课树是否平衡
    function<bool(TreeNode*)> balanceCheck = [&](TreeNode* root)
    {
        // 空树显然是平衡的
        if(!root)
        {
            return true;
        }
        // 否则，需要递归计算两侧子树的高度
        int leftHeight = height(root->left), rightHeight = height(root->right);
        if(abs(leftHeight-rightHeight) > 1)
        {
            return false;
        }
        // 否则，根据平衡二叉树的定义，该二叉树只是在这一根结点上平衡了，还需要递归判断它的所有子结点形成的子树是否平衡
        return balanceCheck(root->left) && balanceCheck(root->right);
    };
    // 进行调用即可
    return balanceCheck(root);
}

// 本题很明显能看出，我们的 height 函数被重复调用了很多次，也就是说，重复计算了很多小子树的高度值，因而类似动态规划中相关的优化策略
// 我们考虑记忆化优化
// 第二版：DFS + 记忆化
bool isBalanced(Leetcode101_200::TreeNode* root)
{
    // 要求判断传入的二叉树是否是平衡的
    // 同样可以使用按定义递归的方法来执行判断
    // 平衡二叉树的定义是：该二叉树左右子树的高度差不超过1
    // 那么我们可以设计一个专门用于检查子树最大高度的函数 height
    // 这个函数也应该是递归定义的
    // height(subRoot)
    // 返回值为以 subRoot 作为根结点的子树的最大高度
    // 添加一个记忆化哈希表，用于避免重复计算
    unordered_map<TreeNode*, int> memo;
    function<int(TreeNode*)> height = [&](TreeNode* subRoot)
    {
        if(memo.find(subRoot) != memo.end())
        {
            return memo[subRoot];
        }
        // 如果子树为空树，直接返回0，递归结束条件
        if(!subRoot)
        {
            return 0;
        }
        // 如果子树非空，则高度至少为1
        // 记录一个全局的最大高度
        int h = 1;
        // 分别递归计算左右两侧的子树高度
        int leftHeight = height(subRoot->left), rightHeight = height(subRoot->right);
        // 当前子树的高度等于两侧子树高度更大的那一个加1
        h += max(leftHeight, rightHeight);
        memo[subRoot] = h;
        // 返回结果
        return h;
    };
    // 有了上面的求解高度的 helper function，我们就可以编写外层的递归函数了
    // 封装一层，balanceCheck 函数的返回值是这课树是否平衡
    function<bool(TreeNode*)> balanceCheck = [&](TreeNode* root)
    {
        // 空树显然是平衡的
        if(!root)
        {
            return true;
        }
        // 否则，需要递归计算两侧子树的高度
        int leftHeight = height(root->left), rightHeight = height(root->right);
        if(abs(leftHeight-rightHeight) > 1)
        {
            return false;
        }
        // 否则，根据平衡二叉树的定义，该二叉树只是在这一根结点上平衡了，还需要递归判断它的所有子结点形成的子树是否平衡
        return balanceCheck(root->left) && balanceCheck(root->right);
    };
    // 进行调用即可
    return balanceCheck(root);
}

// 按理来说，作为传统 DFS 类题目，应该还有一种自底向上的 DP 解法，但由于本题的这种二叉树只支持自父结点到子结点的单向移动，似乎不那么容易搞出简单的 DP 写法