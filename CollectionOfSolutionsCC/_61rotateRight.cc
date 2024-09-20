#include "Solution.h"

ListNode* Leetcode1_100::Solution::rotateRight(ListNode* head, int k)
{
    // 可能有人觉得这道题又是一道传统的链表模拟题，实际上它更像是一道脑筋急转弯
    // 如果存储结构是数组，我们可能的确需要进行模拟交换操作，不过本题存储用的是链表
    // 那么就可以取巧
    // 我们只需要把倒数第 k 个结点的后继指针修改到首元结点身上，而原来的后继结点改成首元结点即可
    // 至于寻找倒数第 k 个结点的方案，其实是一道简单快慢指针类的题目
    /*
        四个主要指针的定义
        1. fast：快指针，循环结束后定义为指向末尾空结点的指针
        2. preF：快指针的前驱结点，定义为始终指向 fast 的前驱
        3. slow：慢指针，循环结束后定义为指向倒数第 (k%n) 个结点的指针
        4. preS：慢指针的前驱结点，定义为始终指向 slow 的前驱
        使用两个前驱的意义：可以画个图理解一下，我们要修改的链接不是倒数第 k 个结点，而是这个结点的前驱结点的后继指针，同时我们还需要把最后一个结点的指针接到首元结点上，故还需要一个指向最后一个结点的指针
    */
    ListNode* fast = head, * slow = head;
    ListNode* dummy = new ListNode(-1);
    dummy->next = head;
    ListNode* preS = dummy, * preF = dummy;
    // 先把快指针后移 k 次
    // 问题：可能会移动超过链表长度次
    // 有一个较难想到，但比较巧妙的解决方案(官方的解法)
    // 先把头尾接上，再执行 k 次后移
    // 不过这样的话，反正都需要先遍历一遍整个链表，其实也可以先计算出链表总长度 n，之后后移 n % k 次即可
    // 额外添加一句：官方的解法一致性比较好，不会因为 n == 0 或者 n % k == 0 这样的数学问题而导致程序崩溃，因而建议还是用这种先连链表再拆开的方案，比较安全
    // 下面只给出自己的方案代码
    int n = 0;
    while(fast)
    {
        ++n;
        fast = fast->next;
    }
    // 其它情况：如果链表原来就为空，或者我们旋转的次数等于链表长度的整数倍，就可以直接返回原链表首元结点
    // 实际上，后面的算法逻辑会和下面这两种情况冲突，因而它们必须被单取出来检查
    if(n == 0 || k % n == 0)
    {
        return head;
    }
    fast = head;
    // 注意，如果 k % n == 0， 这里无法把 fast 放到正确的位置上
    // 如果 n == 0，这里甚至会报 "Division by zero" 错误
    for(int i = 0; i < k % n; ++i)
    {
        preF = preF->next;
        fast = fast->next;
    }
    // 之后两个指针同步后移，直到快指针到达末尾的空指针
    while(fast)
    {
        preS = preS->next;
        preF = preF->next;
        slow = slow->next;
        fast = fast->next;
    }
    // 现在只需要把与这个结点有关的指针进行修改即可
    preS->next = nullptr;
    preF->next = head;
    head = slow;
    delete dummy;
    return head;
}