#include "Solution.h"

// 这一题在82题写错的版本中已经写好答案了，其实如果只要保留一个的话，写法可以非常简单，不过我下面的这种写法可以拓展到每个元素保留至多 k 个的情况
Leetcode1_100::ListNode* Leetcode1_100::Solution::deleteDuplicatesK(Leetcode1_100::ListNode* head)
{
    // 本质上还是一个类似于快慢指针/循环不变式的题目
    // 只是，由于链表和数组的结构不同性，我们需要做一些细节处理
    // 预设一个哨兵结点
    ListNode* dummy = new ListNode();
    dummy->next = head;
    // left 指针标记了最后一个合法的链表结点的指针
    ListNode* left = dummy, * right = head;
    // 多记录一个 right 的前驱结点，用于交换操作
    ListNode* pre = dummy;
    // cnt 变量用于记录当前元素的出现次数，rec 用于记录上一次出现的元素
    int cnt = 0, rec = head ? head->val : -1;
    // 循环遍历所有的链表结点
    while(right)
    {
        // 如果当前出现的元素是一个新元素，那么我们就需要重置 cnt
        if(right->val != rec)
        {
            cnt = 0;
            rec = right->val;
        }
        // 如果当前元素已经出现的次数不多于1次，那么我们才可以把它放到对应的位置上
        // 这里的1理论上可以换成任意 k 值，拓展性很好
        if(cnt < 1)
        {
            ++cnt;
            // 先保存原先的 left->next 结点
            ListNode* tmp1 = left->next;
            left->next = right;
            // 之后保存原先的 right->next 结点
            ListNode* tmp2 = right->next;
            left = left->next;
            /*
                这里是数组交换转链表结点交换很常遇到的一种细节问题
                如果只是单纯交换链表结点，那么利用这种修改两个结点前驱后继结点指针的情况需要额外判断一下
                要交换的两个结点是不是同一个结点，如果是的话，所有前驱后继指针都不能修改！！！
            */
            right->next = tmp1 != right ? tmp1 : right->next;
            pre->next = tmp1 != right ? tmp2 : right;
            pre = pre->next;
            right = right->next;
        }
        // 否则，因为我们前面已经判断过这个结点的元素是不是一个新元素，因而这里就可以断定这个结点元素一定是之前出现过的
        // 重复元素，直接删除它就行
        else
        {
            pre->next = right->next;
            delete right;
            right = pre->next;
        }
    }
    // 循环结束后，我们就可以进行结果返回了
    // 别忘了删除 dummy 哨兵结点
    ListNode* res = dummy->next;
    delete dummy;
    return res;
}