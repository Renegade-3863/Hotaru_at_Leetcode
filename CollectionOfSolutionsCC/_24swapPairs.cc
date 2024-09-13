#include "Solution.h"

Leetcode1_100::ListNode *Leetcode1_100::Solution::swapPairs(ListNode *head)
{
    // 本题要求我们两两交换一个给定链表中的相邻结点，很简单的模拟题，需要细心一些
    // 一般来讲，遇到链表或者回溯这种只用脑思考不是很容易建模的问题，可以画一画过程图，更容易理解流程
    // 具体流程不再记录，画个图很好理解
    // 依然是哨兵结点，方便提取返回值
    ListNode *dummy = new ListNode(-1);
    dummy->next = head;
    ListNode *pre = dummy, *cur = dummy->next, *last = dummy;
    // 交换循环的退出条件为 cur 指针已经走到了链表结尾，此时不再存在需要交换的结点对
    // 实际上这里似乎可以使用死循环     ->      不能用死循环，如果 cur 一开始就是 nullptr，cur->next 就会报空指针访问的错了
    while (cur)
    {
        // 移动两个结点各一步
        cur = cur->next;
        pre = pre->next;
        // 如果移动后 cur = nullptr，无需交换，直接退出即可
        if (!cur)
        {
            break;
        }
        // 交换
        pre->next = cur->next;
        cur->next = pre;
        last->next = cur;
        // 维护三个指针
        last = pre;
        cur = pre->next;
    }
    ListNode *res = dummy->next;
    delete dummy;
    return res;
}