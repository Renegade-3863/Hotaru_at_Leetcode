#include "Solution.h"

Leetcode301_400::ListNode* Leetcode301_400::Solution::oddEvenList(Leetcode301_400::ListNode* head)
{
    // 第一眼看就是一道很经典的循环不变式问题
    // 特判：如果是空链表，直接返回
    if(!head)
    {
        return nullptr;
    }
    // 我们可以规定两个指针，一个指向从头开始最后一个连续的奇数结点地址
    // 另一个指向下一个偶数坐标结点应有的前驱结点位置
    // 我们需要先定位这两个结点
    // 1. 第一个指针直接指向开头即可，这就是最开始的最后一个连续的奇数结点
    // 2. 定位第二个指针
    ListNode* second = head;
    while(second->next && second->next->next)
    {
        // 第二个指针在定位的过程中，一次移动两个结点
        // 直到移动到最后一个奇数序号的结点
        second = second->next->next;
    }
    // 注意一个问题，由于原链表可能是偶数个结点，那么我们需要保存一个额外的指向最后一个偶数结点的指针，不然在移动指针的时候会丢掉最后这个结点
    ListNode* last = nullptr;
    if(second->next)
    {
        last = second->next;
    }
    // 之后循环，维护循环不变式即可
    ListNode* cur = head;
    // 用一个标记记录 cur 的前驱结点，用于调整链表结构
    ListNode* pre = nullptr;
    ListNode* ending = second;
    for(int i = 1; cur != ending; ++i)
    {
        // 奇数下标的结点不动，偶数下标的结点挪到第二个结点指向的结点的后继位置
        if(i%2 == 0)
        {
            // 第一步：把这个结点拆出来
            // 把前驱结点(应该是一个奇数结点)的 next 指针指向这个偶数结点的下一个结点
            pre->next = cur->next;
            // 之后，把这个偶数结点插到第二个指针和它的后继结点之间
            cur->next = second->next;
            second->next = cur;
            // 第三步就是维护 first 和 second 指针的定义
            // 写到这里突然发现 first 指针可以用 pre 指针和 cur 指针代替
            cur = pre->next;
            second = second->next;
        }
        else
        {
            // 奇数序号的结点，我们只需要把遍历用的两个指针向后平移即可
            pre = cur;
            cur = cur->next;
        }
    }
    return head;
}