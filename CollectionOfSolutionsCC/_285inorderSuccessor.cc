#include "Solution.h"

Leetcode201_300::TreeNode* Leetcode201_300::Solution::inorderSuccessor(Leetcode201_300::TreeNode* root, Leetcode201_300::TreeNode* p)
{
    // 不明白这种数据结构的基础类问题为什么在这里成了会员题。。。
    // 找出任何一个二叉树中结点根据中序遍历规则的后继结点
    // 如何找出这样的结点？
    // 我们可以进行分类讨论
    // 对于一棵二叉树中的任何一个结点，它的后继和它本身有三种可能的关系
    // 1. 当前这个结点有右孩子
    // 那么此时它的中序后继就是以它右孩子为根的子树中最靠左的那一个结点
    // 2. 当前这个结点没有右孩子
    // 那么如果我们从当前结点往上回溯，能找到一个是父结点左孩子的结点，那么当前结点的后继就是这个结点
    // 否则，我们就知道当前结点一定是中序遍历的最后一个结点，此时返回 nullptr 即可
    // 由于题目提供的二叉树结点本身不具备指向父结点的指针，我们可能没法直接从当前结点开始往上回溯
    // 不过鉴于本树是一棵二叉搜索树，我们可以利用在一棵二叉搜索树中定位某个结点的方法来进行反向的回溯
    // 按情况1和情况2进行分类讨论即可
    // 特殊情况特判
    if(!root || !p)
    {
        return nullptr;
    }
    TreeNode* res = nullptr;
    if(p->right)
    {
        // 情况1
        res = p->right;
        while(res->left)
        {
            res = res->left;
        }
        return res;
    }
    // 情况2
    // 此时我们需要从根结点开始检查到达 p 这个结点的路径上是否有一个朝左的分支
    TreeNode* cur = root;
    // 本质是一个定位 p 的过程
    // 这里用指针或者值都是可以的，可以使用值的原因是本题是一棵二叉搜索树，不会有重复的元素
    while(cur && cur != p)
    {
        if(cur->val > p->val)
        {
            // 路径上出现了一个向左的分支
            // 用 res 记录
            res = cur;
            cur = cur->left;
        }
        else 
        {
            cur = cur->right;
        }
    }    
    // 额外做一次判断，确保树中存在 p 这个结点
    if(cur == p)
    {
        return res;
    }
    return nullptr;
}