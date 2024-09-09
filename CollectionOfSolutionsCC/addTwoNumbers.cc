#include "Solution.h"

Leetcode1_100::ListNode* Leetcode1_100::Solution::addTwoNumbers(ListNode* l1, ListNode* l2)
{
    {
        // 可以采取先合并，再进位的方式进行计算，这样代码写起来会比较有条理性
        // 本题较为简单的原因在于，链表本身是按逆序存储的，因而对其进行加法不需要进行按位的对齐，只需要从头(最低位)开始进行合并即可
        Leetcode1_100::ListNode* cur1 = l1, * cur2 = l2;
        // 第一轮遍历只需要检查两个数的各个位的和，不需要对数据的进位进行考虑，把他们包含在链表本结点当中即可，故while循环只需要检查到其中一个链表到达尾部即可
        while(cur1 && cur2)
        {
            int sum = cur1->val + cur2->val;
            // 因为不知道哪个链表更长，我们把这个和值同时赋给两个链表的对应结点，因为后面也不会再用到它们的原值了
            cur1->val = cur2->val = sum;
            // 后移两个指针
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
        Leetcode1_100::ListNode* res = nullptr;
        // 根据哪一个链表更长，决定要把哪个链表作为答案返回
        // l2更长或者二者一样长
        if(!cur1)
        {
            // 复位cur2
            cur2 = l2;
            // 如果对应位上还有进位
            while(cur2)
            {
                if(cur2->next)
                {
                    cur2->next->val += cur2->val / 10;
                }
                // 额外情况处理，最后一位上还有进位的情况
                else if(cur2->val / 10)
                {
                    cur2->next = new Leetcode1_100::ListNode(1);
                }
                cur2->val = cur2->val % 10;
                cur2 = cur2->next;
            }
            res = l2;
        }
        // 否则l1更长，此时我们默认用l1作为答案
        else
        {
            cur1 = l1;
            while(cur1)
            {
                if(cur1->next)
                {
                    cur1->next->val += cur1->val / 10;
                }
                else if(cur1->val / 10)
                {
                    cur1->next = new Leetcode1_100::ListNode(1);
                }
                cur1->val = cur1->val % 10;
                cur1 = cur1->next;
            }
            res = l1;
        }
        return res;
    }
}