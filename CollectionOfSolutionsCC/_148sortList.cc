#include "Solution.h"

// 首次尝试的快排方案，放弃了，难度过大，细节过多
Leetcode101_200::ListNode* Leetcode101_200::Solution::sortList(Leetcode101_200::ListNode* head)
{
    // 本题可以简单利用上一题写好的插入排序方案，不过这样是 O(n^2) 的复杂度，显然不是最优的
    // 题目也提出了优化问题：使用 O(nlogn) 的时间和 O(1) 的空间进行排序
    // 那么考虑常规的数组排序，O(nlogn) 的常用方案有归并排序、快速排序、堆排序这几种
    // 而快排和归并可以实现 O(1) 的空间复杂度
    // 我们这里尝试使用快排来对这个链表进行排序操作
    // 规定这样的 partition 函数
    // partition(ListNode* head, ListNode* tail)
    // 它执行的是对 head 到 tail 之间(左闭右闭区间)结点的切分操作，分割的值是内部随机一个结点的值
    // 先把这个函数写出来
    // n 是后加入的参数，用于告诉 partition 函数传入的这部分链表的长度
    // preTail 是最后一个结点的前驱结点，用于选定切分点时的交换操作
    // function<ListNode*(ListNode*, ListNode* tail, int)> partition = [&](ListNode* head, ListNode* preTail, ListNode* tail, int n)
    // {
    //     // 判断一个基本条件：如果 head == tail，或者 head 根本就是空结点，那么我们可以不用切分，直接返回
    //     if(!head || head == tail)
    //     {
    //         return head;
    //     }
    //     // 依然是使用一个哨兵结点
    //     ListNode* dummy = new ListNode(-1);
    //     dummy->next = head;
    //     // res 存储返回值
    //     ListNode* res = nullptr;
    //     // 先随机选一个切分点
    //     int random = rand() % n;
    //     // 判断，如果选出的不是最后一个结点，就要把这个结点和最后一个结点进行交换，否则不需要
    //     if(random != n-1)
    //     {
    //         ListNode* pre = dummy, * cur = dummy->next;
    //         // 把 cur 挪到这第 random 个结点上
    //         for(int i = 0; i < random; ++i)
    //         {
    //             pre = pre->next;
    //             cur = cur->next;
    //         }
    //         // 进行结点交换
    //         preTail->next = cur;
    //         pre->next = tail;
    //         ListNode* tmp = tail->next;
    //         tail->next = cur->next;
    //         cur->next = tmp;
    //         // 为了保证下面表述的统一性，我们把 tail 的指向做一下修改
    //         tail = cur;
    //     }
    //     dummy->next = head;
    //     ListNode* i = dummy;        // 对应快排里面的 i = -1
    //     ListNode* prej = dummy, * j = head;
    //     for(; j->next != tail; j = j->next, prej = prej->next)         // 对应快排里面的 for(int j = 0; j < n-1; ++j)
    //     {
    //         // 遇到一个值不大于切分值的，就把它放到 i 指针之后的第一个位置上
    //         if(j->val <= tail->val)
    //         {
    //             ListNode* pre = i;
    //             i = i->next;
    //             // 进行结点交换
    //             prej->next = i;
    //             pre->next = j;
    //             ListNode* tmp = j->next;
    //             j->next = i->next;
    //             i->next = tmp;
    //             // 维护 i, j 指针的位置
    //             j = prej->next;
    //             i = pre->next;
    //         }
    //     }
    //     // 先记录 res 的值
    //     res = i;
    //     // 最后把最后的结点也交换过来
    //     ListNode* pre = i;
    //     i = i->next;
    //     if(i != tail)
    //     {
    //         // 进行结点交换
    //         preTail->next = i;
    //         pre->next = tail;
    //         ListNode* tmp = tail->next;
    //         tail->next = i->next;
    //         i->next = tmp;
    //     }
    //     // 全部结束后返回 res 即可
    //     delete dummy;
    //     return res;
    // };
    // // 基于上面的逻辑，不难发现我们的 partition 函数返回的是完成切分后的前后两半的分割点前面一个的位置结点
    // // 我们可以基于这个逻辑模拟快排的递归方案
    // function<void(ListNode*, ListNode*)> quickSort = [&](ListNode* head, ListNode* tail)
    // {
    //     // 1. 选出中间值
    //     // 这可以用快慢指针实现 O(logn) 级别的定位
    //     // 但是我们还需要另一个：结尾指针的前驱结点指针？？？
    //     // 写到这，我放弃了快排方案，需要的额外参数实在是太多了，导致写起来可读性极差，而且细节问题很多很多
    //     ListNode* 
    // };
}

Leetcode101_200::ListNode* sortList(Leetcode101_200::ListNode* head)
{
    // 更换思路，使用归并的方案对链表进行排序，归并需要的数据并没有快排那么冗杂，写起来更加简便易懂
    // 先实现一个 merge 步骤的函数
    // 功能是 merge head 到 mid，以及 mid 后继到 tail 之间这两个链表的，返回的是合并后的长链表的首元结点
    // 注意，调用这个函数之前，需要把 mid->next 置空，否则会出现很奇妙的现象，可以自己思考一下为什么
    function<ListNode*(ListNode*, ListNode*)> merge = [&](ListNode* head1, ListNode* head2) -> ListNode*
    {
        // 链表模拟归并步骤即可
        ListNode* i = head1, * j = head2;
        ListNode* dummy = new ListNode(-1);
        ListNode* k = dummy;
        while(i && j)
        {
            if(i->val <= j->val)
            {
                k->next = i;
                i = i->next;
            }
            else
            {
                k->next = j;
                j = j->next;
            }
            k = k->next;
        }
        // 结束后检查是哪个链表用完了
        if(!i)
        {
            // 前半用完了，把后半剩下的部分接上来即可
            k->next = j;
        }
        else
        {
            // 后半用完了，把前半剩下的部分接上来即可
            k->next = i;
        }
        // 返回的是哨兵后连接的首元结点
        ListNode* res = dummy->next;
        delete dummy;
        return res;
    };
    // 写出递归本题函数即可
    function<ListNode*(ListNode*, ListNode*)> mergeSort = [&](ListNode* head, ListNode* tail) ->ListNode*
    {
        // 定义出递归的基本情况：
        if(!head || head == tail)
        {
            return head;
        }
        // 其它情况下，递归进行排序
        // 先通过常规的快慢指针法找出链表的中间结点
        ListNode* slow = head, * fast = head->next;
        while(fast && fast->next)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        ListNode* tmp = slow->next;
        slow->next = nullptr;
        // 回忆，此时 slow 指向的，如果是奇数个结点，就正好是链表中间的结点
        // 如果是偶数个结点，就正好是链表前半部分的最后一个结点
        // 所以我们可以简单的用 head, slow; slow->next, tail 来递归调用 mergeSort 过程
        ListNode* newHead1 = mergeSort(head, slow);
        ListNode* newHead2 = mergeSort(tmp, tail);
        // 对这两部分进行合并
        return merge(newHead1, newHead2);
    };
    // 写好了，我们直接调用这个过程即可
    return mergeSort(head, nullptr);
}