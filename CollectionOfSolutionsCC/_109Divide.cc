#include "Solution.h"

Leetcode101_200::TreeNode* Divide(Leetcode101_200::ListNode* head)
{
    // 分治的思路依然和 108 题一致，本题我们需要思考的是如何在链表这种不能随机访问的结构中高效地找出一组结点的中间结点
    // 如果有经验的同学一定能很快想到快慢指针法
    // 这里不多赘述，先给代码，后讲原理
    // 如果传入的链表中没有结点，直接返回空树即可
    function<TreeNode*(ListNode*, ListNode*)> dfs = [&](ListNode* head, ListNode* tail) ->TreeNode*
    {
        if(head == tail)
        {   
            return nullptr;
        }
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        // 否则，需要先找到对应链表的中间结点
        ListNode* fast = head, * slow = head;
        while(fast != tail && fast->next != tail)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        // 结束后，slow 指向的就是中间结点中更靠近末尾的那一个(如果链表中有偶数个结点的话)
        // 另一种写法是
        // while(fast->next != tail && fast->next->next != tail)
        // 这种写法返回的是更靠近开头的那一个(如果是偶数个结点的话)
        // 当然这种写法需要额外检查链表为空的情况，不然会炸
        TreeNode* root = new TreeNode(slow->val);
        // 之后按 slow 作为中间分割点，递归构造前后两半子树
        root->left = dfs(head, slow);
        root->right = dfs(slow->next, tail);
        delete dummy;
        return root;
    };
    return dfs(head, nullptr);
}