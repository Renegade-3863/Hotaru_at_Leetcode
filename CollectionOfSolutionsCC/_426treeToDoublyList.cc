#include "Solution.h"

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
*/

Node* Leetcode401_500::Soltuion::treeToDoublyList(Node* root)
{
    // 题目要求不改变 BST 的结点结构，直接把 BST 原地转换成一个双向循环链表
    // 这个要求乍一看有点类似 Morris 遍历，我们尝试用这个方案来进行一下解决
    // 首先，我们肯定是需要对整棵树进行一轮中序遍历的，因为 BST 的中序序列就是有序的结果
    // 问题在于：如何找出所有的前驱和后继关系？
    // 这个用 Morris 遍历就不难找出了
    if(!root)
    {
        return nullptr;
    }
    Node* cur = root;
    // 记录上一个访问过的结点信息
    Node* pre = nullptr;
    Node* head = nullptr, * tail = nullptr;
    while(cur)
    {
        if(!cur->left)
        {
            // 左孩子没有结点，那么说明这个结点没有左子树，可以直接进行访问，之后往右走即可
            // 不过我们需要记录前驱结点和它之间的关系，用前驱结点的右孩子进行
            // 如果前驱结点为空，那么我们知道这是第一个访问的结点，记录头结点信息
            if(!pre)
            {
                head = cur;
            }
            else
            {
                pre->right = cur;
                cur->left = pre;
            }
            // 访问完成，往右走即可
            pre = cur;
            cur = cur->right;
        }
        else
        {
            // 左孩子有结点，那么根据 Morris 遍历的性质，我们需要确认这是第几次访问 cur 结点，这可以通过检查 cur 前驱结点的 right 指针来实现
            // 方法依然是 Morris 遍历的常规方法
            Node* predecessor = cur->left;
            while(predecessor->right && predecessor->right != cur)
            {
                predecessor = predecessor->right;
            }
            // 循环结束后两种情况
            // 1. predecessor->right == nullptr
            // 这说明是第一次访问 cur，我们需要先记录后继关系，之后继续往左深入
            if(!predecessor->right)
            {
                predecessor->right = cur;
                cur = cur->left;
            }
            // 2. predecessor->right == cur
            // 这说明是第二次访问 cur，我们可以完成对 cur 的访问，删除后继关系，并往右走
            else
            {
                // 如果前驱结点为空，那么我们知道这是第一个访问的结点，记录头结点信息
                if(!pre)
                {
                    head = cur;
                }
                else
                {
                    pre->right = cur;
                    cur->left = pre;
                }
                pre = cur;
                cur = cur->right;
                // 这里就不用复原了，因为本题的要求就是保留这些前驱后继信息
                // predecessor->right = nullptr;
            }
        }
    }
    // 内部转化完成后，我们不能忘了把链表的头尾结点连起来
    tail = pre;
    head->left = tail; tail->right = head;
    // head 指向的就是最小元素的指针
    return head;
}