#include "Solution.h"

Leetcode1_100::ListNode* Leetcode1_100::Solution::mergeKLists(vector<ListNode*>& lists)
{
    // 本题要求合并 k 个原先就已经是升序排列的链表到一个链表中，比较简单的想法是直接使用 k-1 次之前写过的合并 2 个升序链表的方法，不过这样可能会有很多不必要的重复检查
    // 比如前面的某个链表的前面结点的值明明很小，可是由于我们合并两个链表的函数总是从开头开始进行合并，会多次对其进行重复的比较操作
    // 这样会降低算法的最终效率
    // 考虑一种优化的、使用优先队列的解决方案
    // 我们维护一个大小为 k 的小顶堆，保证堆中存放的总是我们已有的 k 个链表中每一个的最小元素(未检查的部分的首元结点)
    // 其它情况：如果某个链表的元素被用光了，我们就可以不再维护堆的大小为 k 这一条件了
    // 或者可以说，我们维护的是所有还未检查完毕的链表的最小元素构成的堆
    // 使用自定义的比较函数，方便我们在堆中存储结点指针，而不是存储结点值，这样可以避免额外新建结点
    struct cmp 
    {
        // 给优先队列使用的比较函数，用法如下：
        // 我们对堆的 pop 操作弹出的是存储媒介 (vector, list) 末尾的元素，也就是说，如果硬要说顺序的话
        // 大顶堆，数组尾部存储的是最小的元素；小顶堆，数组尾部存储的是最大的元素，因而我们决定存储顺序的比较函数应该是和堆本身的名称相反的功能
        // 比如下面这个函数，它告诉 STL 更大的元素有更高的优先级，因而它就会把最小的元素放到容器的末尾供我们弹出
        bool operator() (ListNode* a, ListNode* b)
        {
            return a->val >= b->val;
        }
    };
    // 小顶堆
    priority_queue<ListNode*, vector<ListNode*>, cmp> minQ;
    int k = lists.size();
    // 哨兵结点，用于构建新链表
    ListNode* dummy = new ListNode(-1);
    // 用尾插法添加结点
    ListNode* tail = dummy;
    for(int i = 0; i < k; ++i)
    {
        // 一点边界情况的处理：比如给出了这个例子： [[]]
        // 此时 lists[0] 中没有实际的结点存在，我们需要跳过这个子链表
        if(lists[i])
        {
            minQ.push(lists[i]);
        }
    }
    // 循环直到小顶堆中不再有元素，即已经完成了 k 个链表的整合
    while(!minQ.empty())
    {
        // 先进行结果提取，后检查可行的添加操作
        ListNode* node = minQ.top();
        minQ.pop();
        tail->next = node;
        tail = tail->next;
        // 如果本次添加的结点还有后继，就把它添加到优先队列中
        if(node->next)
        {
            minQ.push(node->next);
        }
    }
    ListNode* res = dummy->next;
    delete dummy;
    return res;
}