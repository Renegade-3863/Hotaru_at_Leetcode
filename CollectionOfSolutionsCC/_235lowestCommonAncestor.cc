#include "Solution.h"

Leetcode201_300::TreeNode* Leetcode201_300::Solution::lowestCommonAncestorBST(Leetcode201_300::TreeNode* root, Leetcode201_300::TreeNode* p, Leetcode201_300::TreeNode* q)
{
    // 对于本题，我们依旧可以通过递归的方式来解决问题，考虑 p，q 两个结点在树中的分布情况
    // 1. p 就是当前的根结点，q 在任何一个子树中或者等于 p
    // 此时我们直接返回 p 即可
    // 2. q 就是当前的根结点，q 在任何一个子树中或者等于 q
    // 此时我们直接返回 q 即可
    // 3. p 和 q 都不是当前的根结点
    // 3.1 p，q 都在当前根的左孩子中
    // 那么我们递归地检查以 root->left 为根的子树中 p，q 的最近公共祖先
    // 3.2 p，q 都在当前根的右孩子中
    // 那么我们递归地检查以 root->right 为根的子树中 p，q 的最近公共祖先
    // 3.3 p，q 分别在当前根的左右子树中
    // 那么我们直接返回当前根即可，这个根就是 p，q 的最近公共祖先了
    // 写代码即可
    // 特殊情况判定
    if(!root)
    {
        return nullptr;
    }
    // 情况1和2
    if(p == root || q == root)
    {
        return root;
    }
    // 情况3
    // 我们需要一种方法来确定一个结点在不在当前子树中
    function<bool(TreeNode*, TreeNode*)> contains = [&](TreeNode* node, TreeNode* cur) -> bool
    {
        // 用来确定 cur 结点在不在以 node 为根结点的子树中
        if(!node)
        {
            return false;
        }
        if(node == cur)
        {
            return true;
        }
        return contains(node->left, cur) || contains(node->right, cur);
    };
    // 情况3.1
    if(contains(root->left, p) && contains(root->left, q))
    {
        return lowestCommonAncestorBST(root->left, p, q);
    }
    // 情况3.2
    if(contains(root->right, p) && contains(root->right, q))
    {
        return lowestCommonAncestorBST(root->right, p, q);
    }
    // 情况3.3
    return root;
}

// 上面的解法没有用到本题 BST 的性质，我们可以利用起这个性质，加速判断某个结点是否会在某个子树中的过程
Leetcode201_300::TreeNode* lowestCommonAncestorBST(Leetcode201_300::TreeNode* root, Leetcode201_300::TreeNode* p, Leetcode201_300::TreeNode* q)
{
    if(!root)
    {
        return nullptr;
    }
    if(p == root || q == root)
    {
        return root;
    }
    function<bool(TreeNode*, TreeNode*)> contains = [&](TreeNode* node, TreeNode* cur) -> bool
    {
        if(!node)
        {
            return false;
        }
        if(node == cur)
        {
            return true;
        }
        // 利用 BST 的性质做优化
        if(cur->val > node->val)
        {
            // 此时 cur 只可能存在于 node 的右子树中
            return contains(node->right, cur);
        }
        
        // 此时 cur 只可能存在于 node 的左子树中
        return contains(node->left, cur);
    };
    // 其余部分的写法是一样的，无需优化
    if(contains(root->left, p) && contains(root->left, q))
    {
        return lowestCommonAncestorBST(root->left, p, q);
    }
    if(contains(root->right, p) && contains(root->right, q))
    {
        return lowestCommonAncestorBST(root->right, p, q);
    }
    return root;
}

// 上面把 contains 和 lowestCommonAncestor 分开写的方法显然有些画蛇添足，我们可以在检查 p，q 在不在某个子树中的同时就完成对其共同祖先的检查
// 按照官解给出的方案，类似下面的写法：
Leetcode201_300::TreeNode* lowestCommonAncestorBST(Leetcode201_300::TreeNode* root, Leetcode201_300::TreeNode* p, Leetcode201_300::TreeNode* q)
{
    if(!root)
    {
        return nullptr;
    }
    // 如果根结点等于 p 或 q，那么我们就认为这个结点就是两个结点的最近公共祖先
    if(root == p || root == q)
    {
        return root;
    }
    // 如果当前根结点值大于p和q，说明二者都在左子树，向左递归调用 lowestCommonAncestor
    if(root->val > p->val && root->val > q->val)
    {
        return lowestCommonAncestorBST(root->left, p, q);
    }
    else if(root->val < p->val && root->val < q->val)
    {
        return lowestCommonAncestorBST(root->right, p, q);
    }
    // 否则，p 和 q 应该是分别在 root 的两侧子树中，此时我们直接返回根结点即可
    return root;
}