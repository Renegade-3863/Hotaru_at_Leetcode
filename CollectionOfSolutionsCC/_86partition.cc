#include "Solution.h"

Leetcode1_100::ListNode* Leetcode1_100::Solution::partition(Leetcode1_100::ListNode* head, int x)
{
    // 本题是链表版的快排分区函数实现
    // 很多算法用数组实现都比较直接，而如果换用链表就会出现很多细节问题
    // 本题也不例外
    // 回忆：快排的 partition 子过程本质上是一个明显使用了循环不变式+快慢指针的逻辑过程
    // 定义一个 left 指针，指向已经检查过的区间中最后一个小于 x 的结点
    // 但在这之前，还需要一个哨兵结点 dummy
    ListNode* dummy = new ListNode();
    dummy->next = head;
    // pre 指针是用于可能的交换过程的
    ListNode* left = dummy, * right = head, * pre = dummy;
    while(right)
    {
        // 分情况讨论
        // 1. right->val < x
        // 此时需要把 right 结点交换到 left->next
        // 注意：如果 left->next == right，也就是说，此时还没有找到任何一个结点值小于 x 的结点，我们此时不能进行交换，不然会出现自指向错误
        if(right->val < x)
        {
            if(left->next != right)
            {
                // 先记录 right 的后继结点
                ListNode* tmp1 = right->next;
                // 也记录一下 left 的后继结点
                ListNode* tmp2 = left->next;
                // 进行实际的结点交换
                left->next = right;
                right->next = tmp2;
                pre->next = tmp1;
                // 维护各个指针的定义
                left = left->next;
                right = pre->next;
            }
            // 如果 left->next == right，就直接后移指针即可
            else
            {
                left = left->next;
                pre = pre->next;
                right = right->next;
            }
        }
        // 2. right->val >= x
        // 此时不需要做任何处理，简单地后移指针即可
        else
        {
            right = right->next;
            pre = pre->next;
        }
    }
    // 结束后就可以返回最终结果了
    ListNode* res = dummy->next;
    delete dummy;
    return res;
}