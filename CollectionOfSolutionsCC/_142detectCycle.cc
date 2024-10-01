#include "Solution.h"

Leetcode101_200::ListNode* detectCycle(Leetcode101_200::ListNode* head)
{
    // 本身和上一题的方法是一样的，都是双指针
    // 不过上一题的方案，我们只能判断链表中是否存在环，并不能检查出环的入口点
    // 不过我们可以考察一下快慢指针重新相遇时候的状态值
    // 假设快指针走了 2a 步
    // 那么慢指针就走了 a 步
    // 而由于两个指针此时重合了，因而我们可以断定快指针比慢指针多走了 nc 步(假设环走一圈要 c 步)
    // 这里 n 代表快指针套了慢指针的圈数
    // 于是有 a == nc
    // 如果我们假设此时从环的入口点出发，到这个相遇点需要走 k 步
    // 不难看出 0 <= k < c
    // 我们知道 a == nc
    // 也就是慢指针正好走了 n 圈
    // 而由于此时慢指针在环内走出了 k 步的偏移，不难发现这个偏移量加上慢指针在环外走的量应该正好等于沿环走一圈的总步数 c
    // 那么我们是不是可以这样做：
    // 固定快指针，把它变为慢指针(也是每次走一步)
    // 让慢指针回到开头
    // 二者同步进行移动，这样二者最后就能最终相遇在环的开始位置了！
    // 思路想好了，代码写起来就很简单了
    ListNode* fast = head, * slow = head;
    // 同样的循环条件，循环退出的条件有两种：
    // 1. 链表无环，此时推出时要么 fast == nullptr，要么 fast->next == nullptr
    while(fast && fast->next)
    {
        // 两个指针按各自的顺序移动
        fast = fast->next->next;
        slow = slow->next;
        if(fast == slow)
        {
            break;
        }
    }
    // 判断一下是不是一个无环的链表
    if(!fast || !fast->next)
    {
        // 无环
        return nullptr;
    }
    // 如果是一个有环的链表
    // 就要按照上面的方案进行同步遍历
    slow = head;
    while(slow != fast)
    {
        fast = fast->next;
        slow = slow->next;
    }
    return slow;
}