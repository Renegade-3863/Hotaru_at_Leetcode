#include "Solution.h"

Leetcode1_100::ListNode *Leetcode1_100::Solution::mergeTwoLists(Leetcode1_100::ListNode *list1, Leetcode1_100::ListNode *list2)
{
    // 要求使用链表的格式实现归并排序的 merge 步骤
    // 简单题简单做即可
    // 我们当然可以新建一个链表再按序填入结点，但这样显然会使用一倍的额外空间
    // 如果我们可以确定我们之后只会使用合并后的链表，那么显然 in-place 的合并方案要更节约内存空间
    // 不过要对链表进行增删操作的时候最好添加一个哨兵结点，避免对首元结点的意外修改导致返回值出错
    // 澄清一下首元结点和头结点的区别，首元结点指第一个存储了有效数据的结点，头结点相当于这里我们使用的哨兵结点
    ListNode *dummy = new ListNode();
    // 我们这里把所有结点都合并到 list1 原来所在的链表中去
    dummy->next = list1;
    ListNode *cur1 = list1, *cur2 = list2;
    // 新建一个用于添加结点的尾指针 tail，这个指针总是指向最后一个已经有序的子链表的结尾位置
    ListNode *tail = dummy;
    // 只要两个链表有任何一个遍历到了结尾，我们就可以简单退出了
    while (cur1 && cur2)
    {
        if (cur1->val <= cur2->val)
        {
            // 因为 tail 指针和 cur1 指针公用同一个链表，所以其实我们这里不需要进行任何的插入操作，只需要对 tail 指针和 cur1 指针进行一些维护即可
            // 注意到一个事实：cur1 和 cur2 指针一定都会指向各自所在链表中第一个还没完成合并的结点，从这个定义的角度出发，cur1 某种程度上来说
            // 一定指向的是 tail->next，这是一个比较重要的事实
            // 根据这个不变式，我们就可以很方便的维护 tail 和 cur1 了
            tail = cur1;
            cur1 = cur1->next;
        }
        else
        {
            // 存储这个来自另一个链表的较小值的原下一跳结点
            ListNode *tmp = cur2->next;
            // 令这个来自另一个链表的较小值指向有序链表结尾指针原来指向的下一个结点
            cur2->next = tail->next;
            tail->next = cur2;
            // 正确修改 cur2 的指向结点
            cur2 = tmp;
            // 维护 tail 指针的定义
            tail = tail->next;
        }
    }
    // 退出时，如果是第一个链表还有剩余结点，那我们就不需要额外处理了，直接返回即可，因为我们是尝试把第二个链表并入第一个链表
    if (cur1)
    {
        ListNode *res = dummy->next;
        delete dummy;
        return res;
    }
    // 否则就一定是第二个链表还有剩余，我们要做的就是把第二个链表剩下的结点接到第一个链表的结尾
    else
    {
        tail->next = cur2;
    }
    // 循环结束后就可以返回结果了
    ListNode *res = dummy->next;
    delete dummy;
    return res;
}