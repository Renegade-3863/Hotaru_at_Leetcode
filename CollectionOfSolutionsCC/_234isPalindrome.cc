#include "Solution.h"

bool Leetcode201_300::Solution::isPalindrome(Leetcode201_300::ListNode* head)
{
    // 本题要求我们判断一个链表是否是回文的，我们可以通过利用 "双指针找中间结点" 和 "反转链表" 的方案来实现这一过程
    // 第一步：找到链表后半段的起始结点指针
    // 特殊条件特判：空链表显然是回文的
    if(!head)
    {
        return true;
    }
    ListNode* fast = head, * slow = head;
    while(fast->next && fast->next->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    // 循环结束后，slow 指针就指向了前半部分的最后一个结点
    // slow->next 就是后半段的开始结点
    // 我们需要一个对后半段进行反转的函数
    function<ListNode*(ListNode*, ListNode*)> reverse = [&](ListNode* begin, ListNode* end) -> ListNode*
    {
        if(!begin)
        {
            return nullptr;
        }
        ListNode* pre = begin, * cur = begin->next;
        while(cur != end)
        {
            ListNode* tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
        }
        begin->next = end;
        // 循环结束后，pre 指向的就是反转后链表的头结点
        return pre;
    };
    ListNode* begin = slow->next;
    slow->next = nullptr;
    slow = reverse(begin, nullptr);
    fast = head;
    while(slow)
    {
        if(fast->val != slow->val)
        {
            return false;
        }
        fast = fast->next;
        slow = slow->next;
    }
    return true;
}