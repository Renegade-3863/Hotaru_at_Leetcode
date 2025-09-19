class Solution
{
public:
    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        // 简单的快慢指针
        // 快指针先走 N 步，慢指针不动
        ListNode* fast = head, * slow = head;
        // 哨兵结点
        ListNode* dummy = new ListNode();
        dummy->next = head;
        ListNode* prev = dummy;
        for(int i = 0; i < n; ++i)
        {
            fast = fast->next;
        }
        while(fast)
        {
            prev = prev->next;
            fast = fast->next;
            slow = slow->next;
        }
        prev->next = prev->next->next;
        delete slow;
        head = dummy->next;
        delete dummy;
        return head;
    }
};