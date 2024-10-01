#include "Solution.h"

void Leetcode101_200::Solution::reorderList(Leetcode101_200::ListNode* head)
{
    // 本题如果是数组为基础，会非常简单，不过它是基于单链表的，这样就会有些难度
    // 可以考虑下面的方案：
    // 1. 找到链表的中间结点
    // 2. 按中间结点把后半的链表进行反转
    // 3. 从头遍历前半和后半链表，每个后半结点插入到前半结点后面
    // 上面的方案看起来正确，不过有一个细节问题：如何找到单链表的中点？
    // 这同样可以通过快慢指针来实现
    // 规定一个快指针一个慢指针，快指针每次移动两个结点，慢指针每次移动一个结点
    // 如果快指针无法继续移动了，那么此时慢指针就已经指向了链表的中间结点
    // 空链表不需要重排
    if(!head)
    {
        return;
    }
    ListNode* fast = head->next, * slow = head;
    while(fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }/
    // 结束循环时，如果链表结点个数为奇数，那么 slow 指向的是中间结点
    // 如果链表结点个数为偶数，那么 slow 指向的是前半链表的最后一个结点
    // 我们只需要实现一个反转指定范围结点的链表的函数
    function<ListNode*(ListNode*, ListNode*)> reverse = [&](ListNode* head, ListNode* tail) -> ListNode*
    {
        if(!head)
        {
            return nullptr;
        }
        ListNode* pre = head, * cur = head->next;
        while(cur != tail)
        {
            ListNode* tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
        }
        // 最后把开头结点指向 tail 指针
        head->next = tail;
        // pre 就是反转后的链表的首元结点
        return pre;
    };
    // 记录好反转后的链表的首元结点
    ListNode* newHead = reverse(slow->next, nullptr);
    ListNode* check = newHead;
    // 别忘了把原来的前半链表的最后结点和后半结点之间的联系断开
    slow->next = nullptr;
    // 进行拼接即可
    slow = head;
    fast = newHead;
    // 无论链表总长是奇数还是偶数，fast 到达结尾都可以作为拼接循环结束的条件
    while(fast)
    {
        ListNode* tmp = slow->next;
        slow->next = fast;
        fast = fast->next;
        slow->next->next = tmp;
        slow = slow->next->next;
    }
    // 循环结束后，就可以直接返回了
    return;
}