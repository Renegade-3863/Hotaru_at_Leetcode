#include "Solution.h"

Leetcode101_200::Node* connect(Leetcode101_200::Node* root)
{
    // 题目要求我们针对一棵完美二叉树 (即满二叉树) 进行操作
    // 我们有必要利用起来满二叉树的特性：任何一个非叶结点都一定有两个非空子结点
    // 经过一番观察，不难发现其实一棵满二叉树的同一层只有两种可能的相邻结点对
    // 1. 这两个相邻结点对有共同的父结点
    // 2. 这两个相邻结点对指向两个不同的父结点(注意到这两个父结点应该在上层是相邻的)
    // 由此我们可以大致决定如下的修改 next 指针策略
    // 对于第1种情况，我们可以简单地通过每个上层的父结点来完成这两个子结点的 next 指针连接
    // 对于第2种情况，此时无法简单地通过一个上层父结点来完成，基于我们上面发现的这一特性：当前层紧邻，但没有公共父结点的两个结点，它们的父结点一定是紧邻，且有 next 指针相连的
    // 因而我们只需要利用这两个父结点之间的 next 指针即可实现两个子结点之间的连接
    // 基于这种算法，我们只需要记录每一层的最左侧结点即可实现，不再需要 BFS 中那样记录每一层的所有结点了
    if(!root)
    {
        return nullptr;
    }
    Node* leftMost = root;
    // 遍历所有层，基于当前层处理下一层
    // 所以结束条件是 leftMost->left 非空，即下一层还有结点
    while(leftMost->left)
    {
        // 遍历当前行内结点
        Node* curLevel = leftMost;
        while(curLevel)
        {
            // 情况1. 先处理 curLevel 本身的两个孩子结点
            curLevel->left->next = curLevel->right;
            // 情况2. 再处理 curLevel 的右孩子和它的后继者的左孩子结点
            if(curLevel->next)
            {
                curLevel->right->next = curLevel->next->left;
            }
            // 后移
            curLevel = curLevel->next;
        }
        // 下移首结点指针
        leftMost = leftMost->left;
    }
    return root;
}