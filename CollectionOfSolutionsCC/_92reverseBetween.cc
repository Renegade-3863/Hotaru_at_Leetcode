#include "Solution.h"

Leetcode1_100::ListNode* Leetcode1_100::Solution::reverseBetween(Leetcode1_100::ListNode* head, int left, int right)
{
    // 要求反转从位置 left 到位置 right 到链表结点，并返回反转后到链表
    // 本题不涉及可疑的链表交换(即自己和自己交换的情况)，所以细节问题没有那么严重
    // 不过会涉及到一些交换前后指针调整的细节问题
    // 首先定义一个用来反转 left 和 right 指针之间的结点的函数
    // 返回值为反转后的链表首元结点
    // 定义 end 为要反转的部分之后的第一个结点
    function<ListNode*(ListNode*, ListNode*)> reverseLF = [&](ListNode* start, ListNode* end) -> ListNode*
    {
        // 只有一个结点，不需要反转，直接返回即可
        if(start->next == end)
        {
            return start;
        }
        ListNode* cur = start->next, * pre = start;
        while(cur != end)
        {
            ListNode* tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
        }
        // 最后把 start 接到 end 上
        start->next = end;
        // 此时 pre 就是反转后的结果
        return pre;
    };
    // 之后想办法调用上面的函数即可
    // 写一个哨兵结点
    ListNode* dummy = new ListNode();
    dummy->next = head;
    ListNode* preStart = dummy, * start = head, * end = head;
    // 先把 end 指针后移 right-left+1 次
    for(int i = 0; i < right-left+1; ++i)
    {
        end = end->next;
    }
    // 之后 start 和 end 指针同步后移 left-1 次
    // 注意 preStart 也要跟着移动，记录 start 的前驱结点
    for(int i = 0; i < left-1; ++i)
    {
        preStart = preStart->next;
        start = start->next;
        end = end->next;
    }
    // 调用函数即可
    preStart->next = reverseBetween(start, end);
    ListNode* res = dummy->next;
    delete dummy;
    return res;
}