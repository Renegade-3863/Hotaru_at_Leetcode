#include "Solution.h"

Leetcode301_400::ListNode* Leetcode301_400::Solution::plusOne(Leetcode301_400::ListNode* head)
{
    // 简单模拟题
    // 我们的加法无非两种可能
    // 1. 最低位不是9，无需进位
    // 此时我们简单地给最后一位加一即可
    // 2. 最低位是9，我们需要进位
    // 此时我们需要把从最低位开始往前的所有连续的9结点都变为0，给从右到左第一个非9结点的值单纯加一
    // 而要确定这个从最低位开始的连续为9的结点，我们可以通过判定每个连续的为 9 的结点来实现
    // 具体的实现到代码中看即可
    // 第一步，我们判断出上面说的连续的9结点序列的头
    ListNode* cur = head;
    ListNode* lastNine = nullptr;
    ListNode* last = nullptr;
    while(cur)
    {
        if(!lastNine && cur->val == 9)
        {
            lastNine = cur;
        }
        else if(lastNine && cur->val != 9)
        {
            lastNine = nullptr;
        }
        if(!cur->next)
        {
            last = cur;
        }
        cur = cur->next;
    }
    // 循环结束时，如果最后一个连续的9序列包含了最后一个结点，我们的 lastNine 指针就指向了这个序列的头结点
    // 三种情况：
    // 1. lastNine == head
    // 此时我们重新遍历一遍链表，把所有结点的值都变成零，并给原来的链表前面添加一个1
    if(lastNine == head)
    {
        ListNode* newHead = new ListNode(1);
        newHead->next = head;
        while(lastNine)
        {
            lastNine->val = 0;
            lastNine = lastNine->next;
        }
        return newHead;
    }
    // 2. lastNine != nullptr
    // 此时说明我们有一个直接延伸到结尾的9序列
    // 那么我们把这些结点的值都变成0，再把它前面的结点值加一即可
    if(lastNine)
    {
        cur = head;
        while(cur->next != lastNine)
        {
            cur = cur->next;
        }
        ++cur->val;
        while(lastNine)
        {
            lastNine->val = 0;
            lastNine = lastNine->next;
        }
        return head;
    }
    // 3. lastNine == nullptr
    // 此时我们只需要给最后一个结点加一即可
    ++last->val;
    return head;
}