#include "Solution.h"

Leetcode101_200::Solution::ListNode* getIntersectionNode(Leetcode101_200::ListNode* headA, Leetcode101_200::ListNode* headB)
{
    // 简单题简单做，本题虽然仍然可以分别从两个起始结点向后遍历，记录相交结点位置于一个哈希表中，之后检查重复
    // 但是这样仍然有 O(n) 的空间复杂度
    // 我们依然可以考虑双指针方案(注意不是快慢指针)
    // 考虑这样的事实：如果两个链表有交点，那么它们只可能在交点前面的部分才有可能长度不同
    // 而如果它们交点前面的部分长度都是相同的，那么显然同步从两个链表的首元结点开始遍历，我们可以直接拿到这两个链表的交点
    // 那么实际上我们只需要找到一种方案，把这两个链表交点前面的部分弄成一样长就可以了
    // 实现方案实际非常简单
    // 我们只需要：
    // 让两个指针分别从两个链表的首元开始向后运动
    // 可以想见，非相交部分较短的那一侧指针会先到达结尾
    // 那么此时我们只需要让这个先到达结尾的指针挪回非相交部分较长的那一个链表的首元并开始向后运动
    // 之后非相交部分较长的那一侧指针也挪到另一个链表头部同步运动
    // 这样二者就会正好走相同的距离，直到相遇在链表重合的第一个结点！
    // 文字说起来可能比较抽象，可以画个图帮助理解。。。
    // 代码写起来很简洁，可能会有一些细节问题
    ListNode* first = headA, * second = headB;
    while(first != second)
    {
        // 退出条件有两种：
        // 1. 链表有交点：此时二者退出时是 first == second
        // 2. 链表没有交点：此时其实是一样的退出条件，只不过 first == second == nullptr 而已
        if(!first)
        {
            first = headB;
        }
        else
        {
            first = first->next;
        }
        if(!second)
        {
            second = headA;
        }
        else
        {
            second = second->next;
        }
    }
    return first;
}