#include "Solution.h"

void Leetcode201_300::Solution::deleteNode(Leetcode201_300::ListNode* node)
{
    // 比较脑筋急转弯的一道题，不给你链表头结点，要求你删除某个单链表中的某个结点
    // 习惯了正向删除的朋友们肯定会感觉比较困难，实际上，我们可以反向考虑一下这个问题：
    // 即然直接删除这个结点不太可能，我们就考虑删除它后面的结点。
    // 其实删除 node 后面的任何一个结点都是可以的，这里我们考虑直接删除紧邻 node 的后继结点
    // 先把结点值交换过来
    // 注意：如果 node->next 为空，说明 node 已经是最后一个结点了，此时我们直接删除 node 即可
    if(!node->next)
    {
        delete node;
        node = nullptr;
    }
    // 其它情况下，考虑把后面紧邻结点的值交换过来
    node->val = node->next->val;
    // 再把紧邻的后一个结点删除
    ListNode* tmp = node->next;
    node->next = node->next->next;
    delete tmp;
    tmp = nullptr;
}
