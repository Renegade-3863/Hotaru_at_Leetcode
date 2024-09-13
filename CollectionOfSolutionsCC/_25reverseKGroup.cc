#include "Solution.h"

Leetcode1_100::ListNode* Leetcode1_100::Solution::reverseKGroup(ListNode* head, int k)
{
    // 两两翻转链表结点问题的升级版，思路和之前的版本基本一致
    // 只是这次要翻转的结点数量可能会多于两个，我们可以写一个 lambda 函数执行过程
    /**
     * @param head 要翻转的子链表的首元结点
     * @param tail 要翻转的子链表的最后一个结点的下一个结点(用来作为翻转结束条件)
     * @return 返回一个 ListNode 类型的指针，用来表示翻转之后的子链表的首元结点
     */
    function<ListNode*(ListNode*, ListNode*)> reverseList = [&](ListNode* head, ListNode* tail) -> ListNode*
    {
        // 子过程的逻辑可以很简单，我们直接对链表进行翻转即可
        ListNode* pre = head, *cur = head->next;
        // 先把 pre 的 next 进行修正，使其指向 tail
        pre->next = tail;
        // 使用一个循环进行翻转
        while(cur != tail)
        {
            // 记录 cur->next
            ListNode* tmp = cur->next;
            // 翻转
            cur->next = pre;
            // 维护两个指针
            pre = cur;
            cur = tmp;
        }
        // 循环结束时，pre 指针指向的是翻转后链表的头结点
        return pre;
    };
    // 在主过程中，我们要做的是使得 head 和 tail 指针能够指向正确的结点，以便调用上面的 reverseList 过程
    // 依然是哨兵结点，备用
    ListNode* dummy = new ListNode(-1);
    dummy->next = head;
    ListNode* pre = dummy->next, *cur = dummy->next, *last = dummy;
    while(cur)
    {
        int i = 0;
        // 每次把 cur 后移 k 次，就找到了要翻转的部分子链表末尾结点的下一个结点，此时只需要调用 reverseList 子过程
        for(; i < k; ++i)
        {
            // 循环内部的退出条件：如果已经找不到一个长度为 k 的子链表，就可以退出了，这部分不用翻转
            if(!cur)
            {
                break;
            }
            cur = cur->next;
        }
        // 没找到长度为 k 的子链表时，不要翻转，直接退出
        if(i < k)
        {
            break;
        }
        // 循环结束时，保证 pre 在要翻转的链表首元结点处，cur 在这个链表的尾结点的后继结点处，last 在 pre 的前驱处即可
        last->next = reverseList(pre, cur);
        // 维护三个指针
        // 原来的 pre 现在在子链表的结尾，也就是下一个子链表首元结点的前驱位置
        last = pre;
        pre = cur;
        // cur 无需更新，在子过程中没有对其进行修改
    }
    // 整个循环结束后，就拿到了结果，返回 dummy->next 即可
    ListNode* res = dummy->next;
    delete dummy;
    return res;
}