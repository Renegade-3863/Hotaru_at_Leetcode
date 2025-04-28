/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
#include "Solution.h"

vector<ListNode*> Leetcode701_800::Soltuion::splitListToParts(ListNode* head, int k)
{
    // 基本的数学模拟题
    // 考虑题目的要求，我们举个例子来看下：
    /*
        list:
            1->2->3->4->5->6->7->8->9->10
        k:
            3
        那么要求的是分成 3 个部分，每部分的长度相差不超过 1
        我们的第一想法就是：获知 list 的总长度，也就是 10   
        然后用 10 去除以 3
        向下取整，得到每一组长度应该为 3 (可能需要向上取到 4)
        然后我们先按 3 个一组进行分配
        发现只能分成 3，3，3。还剩一个元素 
        那么我们就应该给第一组多分配一个
        也就是 4，3，3 (题目要求前面的组元素不能少雨后面的组，并且长度差距不能超过 1)
        我们总结一下具体的流程
        1. 首先，用 list 的长度除以 k，得到一个基本的 "每组元素基底"
        2. 之后，考虑再分配
            2.1 首先，剩下的元素个数一定小于 k 个
            2.2 上面一条性质意味着，我们一定可以用均分的方式，把剩下的这些元素均分给这些目前个数相等的组
            2.3 最后一点：每一组我们分配一个元素即可，这样一定能满足题目要求的：每两部分的长度差距不能超过 1 的要求 
    */
    // 之后我们就可以考虑写代码了
    // 首先，计算一下 list 的长度
    int len = 0;
    ListNode* cur = head;
    while(cur)
    {
        ++len;
        cur = cur->next;
    }
    // len 计算完毕，接下来计算 len/k
    int base = len/k;
    // 现在每一组都假定要分配 base 个元素，我们计算剩下元素的个数 rem
    int rem = len-base*k;
    // 这 rem 个元素均分给前面 rem 个组即可，注意：rem 一定不大于 k
    // 我们用一个 cnt 变量记录额外添加的元素个数，cnt 达到 rem 时我们就不再添加了
    int cnt = 0;
    // 为填写方便，我们先给每一行额外添加一个 dummy tail，注意，定义的是 tail 结点，这是为了方便添加元素
    vector<ListNode*> res(k);
    for(int i = 0; i < k; ++i)
    {
        res[i] = new ListNode(-1);
    }
    // cur 用于记录当前要分割链表的点位，每次我们都从这个 cur 处拆分原链表
    cur = head;
    // 记录 k 行链表的尾节点，用一个哈希表即可
    unordered_map<int, ListNode*> memo;
    for(int i = 0; i < k; ++i)
    {
        memo[i] = res[i];
    }
    // 之后，按顺序把链表中的元素添加到每一行中即可
    for(int i = 0; i < k; ++i)
    {
        int time = base;
        // 检查 cnt 和 rem 的关系，如果 cnt == rem，我们就只添加 base 个，否则，添加 base+1 个
        if(cnt < rem)
        {
            ++time;
            // 别忘了累加 cnt
            ++cnt;
        }
        memo[i]->next = cur;
        // 添加完成后，需要同步修改 memo 中的记录和 cur
        for(int j = 0; j < time; ++j)
        {
            memo[i] = memo[i]->next;
            cur = cur->next;
        }
        // 别忘了断开 memo[i]，此时也是对应 i 行的尾结点和原本后继结点的联系
        memo[i]->next = nullptr;
    }
    // 最后，别忘了清除最开始添加的 dummy head
    for(int i = 0; i < k; ++i)
    {
        ListNode* tmp = res[i];
        res[i] = res[i]->next;
        delete tmp;
        tmp = nullptr;
    }
    // 添加完成，返回 res 即可
    return res;
}