#include "Solution.h"

Leetcode401_500::ListNode* Leetcode401_500::Soltuion::addTwoNumbers(Leetcode401_500::ListNode* l1, Leetcode401_500::ListNode* l2)
{
    // 基本的逻辑和正常的字符串式大数加法是完全一致的
    // 不过本题是按单链表的形式进行数据存储的，所以我们如果想和字符串形式的大数加法一样从最低位开始求解，会有无法回访的问题
    // 所以我们可能会需要对链表进行反转处理后，再进行对应的操作
    // 首先考虑如何对一个单链表进行反转，写一个调用方法函数即可
    // 这个函数用于反转以 head 为首元结点的单链表，返回的是反转后链表的首元结点
    // len: 传入传出信息，表示反转链表的长度
    function<ListNode*(ListNode*, int&)> reverse = [&](ListNode* head, int& len) -> ListNode*
    {
        if(!head)
        {
            return nullptr;
        }
        // 初始化链表长度为 1
        len = 1;
        // 基本的逻辑是：
        // 遍历一轮整个链表，从头到尾，按把每个相邻对都进行指向反转
        ListNode* cur = head->next, * pre = head;
        pre->next = nullptr;
        // 循环的退出条件为：cur 为空，此时说明整个链表已经反转完成了
        while(cur)
        {
            ListNode* tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
            // 每反转一次，链表长度加一
            ++len;
        }
        // 循环结束后，pre 指向的就是新的首元结点，返回即可
        return pre;
    };  
    // 反转两个链表
    int len1 = 0, len2 = 0;
    ListNode* newL1 = reverse(l1, len1);
    ListNode* newL2 = reverse(l2, len2);
    ListNode* traverse = newL1;
    // while(traverse)
    // {
    //     cout << traverse->val << " ";
    //     traverse = traverse->next;
    // }
    // cout << "Reversed" << endl;
    // 之后从头开始逐对结点进行求和运算
    // 运算过程中也要把进位值考虑进来
    int carry = 0;
    ListNode* cur1 = newL1, * cur2 = newL2;
    ListNode* tail = len1 >= len2 ? cur1 : cur2;
    while(cur1 || cur2)
    {
        // 取出两侧结点的实际值，空结点的值为 0
        int val1 = cur1 ? cur1->val : 0, val2 = cur2 ? cur2->val : 0;
        // 算上 carry 进行求和
        // 这里还有一个问题，我们可能需要提前确认两个链表长度，把更长的那一个链表作为最后输出结果的链表
        // 我们在前面进行一下处理
        // 处理完毕，现在我们知道 len1 和 len2，那么要做的就是比较 len1 和 len2 的大小，把结果储存到更长的那一个链表中
        // 长度相同时，默认存储到第一个链表中
        ListNode* curr = len1 >= len2 ? cur1 : cur2;
        curr->val = val1+val2+carry;
        // 更新进位值
        carry = curr->val / 10;
        // 更新该位实际值
        curr->val %= 10;
        // 后移两个指针
        if(cur1)
        {
            cur1 = cur1->next;
        }
        if(cur2)
        {
            cur2 = cur2->next;
        }
        if(curr->next)
        {
            tail = tail->next;
        }
    }    
    // 最后，如果求和后总位数变多了，别忘了在最后一位上接上一个新结点
    if(carry)
    {
        tail->next = new ListNode(carry);
    }
    if(len1 >= len2)
    {
        return reverse(newL1, len1);
    }
    return reverse(newL2, len2);
}