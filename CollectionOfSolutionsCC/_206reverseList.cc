#include "Solution.h"

// 迭代版本
Leetcode201_300::ListNode* Leetcode101_200::Solution::reverseList(Leetcode101_200::ListNode* head)
{
    // 本题要求的是把一个单链表进行反转，简单模拟即可
    if(!head)
    {
        return nullptr;
    }
    ListNode* pre = head, * cur = head->next;
    while(cur)
    {
        // 每次把当前结点指向它的前驱结点
        ListNode* tmp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = tmp;
    }
    // 别忘了把首元结点的 next 指针修改完成
    head->next = nullptr;
    return pre;
}

// 递归版本
Leetcode201_300::ListNode* Leetcode201_300::Solution::reverseList(Leetcode201_300::ListNode* head)
{
    // 题目要求我们迭代递归都写一版，这里尝试写一下递归版本
    if(!head || !head->next)
    {
        return head;
    }
    // 否则需要先对 head->next 部分的链表进行反转，由于反转后的 head->next 就是该部分的尾结点，我们可以直接把 head 接到 head->next->next 上
    ListNode* newHead = reverseList(head->next);
    head->next->next = head;
    head->next = nullptr;
    return newHead;
}