#include "Solution.h"

Leetcode101_200::ListNode* Leetcode101_200::Solution::insertionSortList(Leetcode101_200::ListNode* head)
{
    // 题目要求我们给一个以链表形式表示的整数序列进行插入排序，是一道很基础的题目
    // 我们只需要模拟插入排序的逻辑即可
    // 插入排序的基本逻辑是：
    // 维护一个有序序列的结尾位置，以及已经遍历指针 k
    // 每次指针 k 移动到一个还未排好序的位置，就遍历前面已排好序的部分，找到这个 k 指针处的元素需要被放到的位置上即可
    // 明确了上面的逻辑，我们只需要写出代码即可
    // 用一个 sorted 链表来表示从开头开始最后一个已经排好序的元素位置
    // 为了方便统一代码逻辑，我们依然是新建一个哨兵结点
    ListNode* dummy = new ListNode(-1);
    dummy->next = head;
    ListNode* sorted = dummy, * cur = head, * prev = dummy;
    // 结束条件为所有结点均已排好序，这里我们用 cur 是否为空来指代这一信息
    while(cur)
    {
        // 每次移动 cur 指针，都保证这个结点会被放到正确的位置上
        // 注意，由于链表的首元结点可能会被修改，这里我们不能一直用 head 进行赋值，除非你在后面再用条件判断语句修改 head 的值，这里我们用简单一点的方式进行处理，使用哨兵结点记录的信息来进行初始化，这样可以保证赋值的正确性
        ListNode* traverse = dummy->next, * pre = dummy;
        // 遍历前面的链表
        // 检查结束条件有两种：
        // 1. 找到了前面有序序列中第一个比 cur 值大的元素，这个位置前面就是要插入的位置
        // 2. 遍历到了 cur 本身也没找到比 cur 值大的元素，此时 cur 保持原位即可，不需要移动
        while(cur != traverse)
        {
            if(cur->val < traverse->val)
            {
                break;
            }
            pre = pre->next;
            traverse = traverse->next;
        }
        // 检查时哪种情况退出了循环
        // 情况1. 此时需要把这个结点插入到前面 pre 结点后面
        if(cur != traverse)
        {
            // 按步骤来，不会出错
            // 1. 取出 cur 结点
            prev->next = cur->next;
            // 2. 插入到 pre 和 traverse 之间
            cur->next = pre->next;
            pre->next = cur;
            cur->next = traverse;
            // 调整 prev 和 traverse 结点
            // prev 不用动
            // cur 需要调回 prev->next
            cur = prev->next;
        }
        // 情况2. 此时不需要进行结点交换，直接跳过即可
        else
        {
            prev = prev->next;
            cur = cur->next;
        }
    }
    ListNode* res = dummy->next;
    delete dummy;
    return res;
}