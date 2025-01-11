/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};
*/

#include "Solution.h"

Node* Leetcode501_600::Soltuion::inorderSuccessor(Node* node)
{
    // 基本的数据结构题
    // 考虑一个结点的后继可能在哪
    // 1. 在它的右子树中
    // 2. 是它回溯到的第一个右上父结点 (就是说，回溯过程中，遇到了一个父亲结点的左孩子是当前结点)
    // 按照两种情况分类检查即可
    // 题目说明，我们可以直接访问 node 结点
    // 所以检查就从 node 入手
    // res 代表最终的结果结点
    Node* res = nullptr;
    // 按照 node->right 是否为空拆分情况
    if(node->right)
    {
        // 说明是情况1，中序后继结点在 node 的右子树中
        res = node->right;
        while(res->left)
        {
            // 持续往左移动，直到无法继续往左移动
            res = res->left;
        }
    }
    else
    {
        // 说明是情况2，中序后继结点在 node 的父系结点中
        // 我们沿着 parent 往上不断回溯
        // 直到：
        // 1. parent 为空
        // 2. parent->left = cur
        Node* cur = node;
        while(cur->parent && cur->parent->left != cur)
        {
            cur = cur->parent;
        }
        // 无论哪种情况结束循环，cur->parent 都指向了 node 的中序后继
        res = cur->parent;
    }
    return res;
}