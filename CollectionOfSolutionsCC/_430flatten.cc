#include "Solution.h"

Node* Leetcode401_500::Solution::flatten(Node* head)
{
    // 经典的递归类问题，这种问题我们最好的解决办法就是分层对问题进行拆解
    // 定义一个递归的回调函数，用于扁平化以某个结点开头的多级双向链表
    // 此函数的返回值就是 curHead 扁平化后的结尾结点，结合 curHead，我们可以进行扁平化后列表的插入任务
    function<Node*(Node*)> subFlatten = [&](Node* curHead) -> Node* 
    {
        // 如果这个链表本身就是没有下一级的，我们实际上不用做任何事，但问题在于它可能有
        // 所以我们必须对整个链表进行遍历
        Node* cur = curHead;
        Node* pre = nullptr;
        while(cur)
        {
            // 分两种情况
            // 1. 这个结点没有 child 内容
            if(!cur->child)
            {
                // 那么我们只需要跳过这个结点即可
                pre = cur;
                cur = cur->next;
            }
            else
            {
                // 否则，这个结点有 child，那么我们需要对这个孩子链表进行扁平化后，插入到当前结点和它的后继结点之间
                Node* last = subFlatten(cur->child);
                // 检查，如果它的后继有结点，那么进行设置，这样做是为了防止空指针访问
                if(cur->next)
                {
                    cur->next->prev = last;
                }
                last->next = cur->next;
                cur->child->prev = cur;
                cur->next = cur->child;
                // 置空当前结点的 child 结点，防止错误指向
                cur->child = nullptr;
                // 把 cur 置于下一个指针的位置上
                pre = last;
                cur = last->next;
            }
        }
        // 扁平化完成，返回结果链表的结尾结点
        return pre;
    };
    // 我们只需要调用上面写好的函数即可
    subFlatten(head);
    return head;
}