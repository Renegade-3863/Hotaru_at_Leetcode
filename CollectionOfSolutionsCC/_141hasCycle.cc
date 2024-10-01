#include "Solution.h"

bool Leetcode101_200::Solution::hasCycle(Leetcode101_200::ListNode* head)
{
    // 本题是很经典的一道双指针类题目，不过如果你想按哈希表的方案做，其实也可以，不过那样显然不是最优解
    // 我们中学时应该都参加过运动会，知道"套圈"这个概念
    // 本题其实是一样的
    // 我们只需要规定两个指针，一快一慢，让这两个指针在这个可能有环的链表上运动
    // 如果某个时刻，快指针"追上"了慢指针，那么显然我们就可以断定，这个链表中存在一个环了
    ListNode* fast = head, * slow = head;
    // 进行快慢遍历即可
    while(fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;
        if(fast == slow)
        {
            return true;
        }
    }
    // 如果 fast 因为到达了结尾(nullptr)而结束循环，那么说明这个链表就没有环
    return false;
}