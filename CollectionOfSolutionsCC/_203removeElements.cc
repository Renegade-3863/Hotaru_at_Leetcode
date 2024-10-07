#include "Solution.h"

Leetcode201_300::ListNode* Leetcode201_300::Solution::removeElements(Leetcode201_300::ListNode* head, int val)
{
    // 简单的模拟题，遍历一遍整个链表，记录前驱结点和当前结点，把所有值等于 val 的当前结点都扔掉即可
    // 搞一个哨兵结点，加强定义的统一性
    ListNode* dummy = new ListNode(-1);
    dummy->next = head;
    ListNode* pre = dummy, * cur = head;
    while(cur)
    {
        // 1. 当前结点值等于 val，进行如下处理
        if(cur->val == val)
        {
            pre->next = cur->next;
            delete cur;
            cur = pre->next;
        }
        // 2. 当前结点值不等于 val，简单跳过即可
        else
        {
            pre = pre->next; cur = cur->next;
        }
    }
    // 为了防止 head 结点被删掉的问题，我们使用 dummy->next 代替直接使用 head 的赋值手段
    ListNode* res = dummy->next;
    delete dummy;
    return res;
}

// 本题题解特意说明了有递归的解法，那么我们这里就不看题解，自己写一版递归的解法，毕竟了解一下总没坏处
Leetcode201_300::ListNode* removeElements(Leetcode201_300::ListNode* head, int val)
{
    // 定义一个递归的回调函数体
    // dfs(ListNode* head) 用于清除以 head 为首元结点的链表中所有值为 val 的结点
    // 我们只需要按照这个定义进行嵌套调用即可
    // 注意到上面这个回调函数和题解的母函数之间功能的重复性，我们可以直接利用母函数
    // 递归结束条件：空链表不需要进行任何删除
    if(!head)
    {
        return nullptr;
    }
    // 否则，检查当前结点是否需要删除
    if(head->val == val)
    {
        // 需要删除，返回后面部分删除后的首元结点
        return removeElements(head->next, val);
    }
    // 否则，不删除，把当前结点链接到后面的删除完成的结果上并返回即可
    head->next = removeElements(head->next, val);
    return head;
}