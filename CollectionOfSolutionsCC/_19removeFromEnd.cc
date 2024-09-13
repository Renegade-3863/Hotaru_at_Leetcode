#include "Solution.h"

Leetcode1_100::ListNode *Leetcode1_100::Solution::removeNthFromEnd(ListNode *head, int n)
{
    // 本题要求我们删除一个链表中倒数第 n 个结点，这可以通过快慢指针的方式简单实现
    // 不过直接思考可能比较困难，我们可以先正向思考
    // 这是一个单链表，如果它是一个双向/循环链表，那么我们可以很简单地进行先找结尾再定量移动后删除的方法，但这显然无法在单链表中实现
    // 观察一个特征：要被删除的结点和结尾结点(这里我们视空结点为尾结点)之间的距离是固定的(就是 n)
    // 那么我们是否可以利用这个信息呢？
    // 采用一种类似平移的方法，我们可以把这个等距的关系转变成首元结点和后面的一个链表结点之间的等距关系！
    // 这就是所谓的快慢指针法，很巧妙的一种转换方法
    ListNode *slow = head, *fast = head;
    // 把快指针后移 n 步即可
    for(int i = 0; i < n; ++i)
    {
        // 这是一种错误情况，只在 n 大于链表长度的时候发生
        // 为了避免空指针访问，我们指定此时返回 nullptr
        if(!fast)
        {
            return nullptr;
        }
        fast = fast->next;
    }
    // 记录一个前驱指针，用于进行结点删除，初始指向一个哨兵结点
    ListNode* dummy = new ListNode();
    dummy->next = head;
    ListNode* pre = dummy;
    // 把 fast 指针移动到尾指针处，循环结束后 slow 指针就指向了要删除的结点
    while(fast)
    {
        pre = slow;
        slow = slow->next;
        fast = fast->next;
    }
    // 进行删除
    pre->next = slow->next;
    // 我们假设链表中的结点是动态分配的
    delete slow;
    // 返回哨兵结点的直接后继而不是 head 指针，因为我们可能会把 head 结点删除
    ListNode* res = dummy->next;
    // 不要忘记删掉哨兵结点
    delete dummy;
    return res;
}