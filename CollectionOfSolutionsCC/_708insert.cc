#include "Solution.h"

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val) {
        val = _val;
        next = NULL;
    }

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};
*/

Leetcode701_800::Node* Leetcode701_800::Soltuion::insert(Leetcode701_800::Node* head, int insertVal)
{
        if(!head)
        {
            head = new Node(insertVal);
            head->next = head;
            return head;
        }
        // 题目告诉我们 head 不一定是列表中最小的值，那么我们可以先统一一下 head 的定义
        // 我们规定一个新的头，命名为 newHead，它指向的是整个列表中最左侧的最小值结点
        Node* newHead = head;
        // 我们只需要找到第一个反转点即可
        // 反转点应该满足：newHead->next->val < newHead->val
        // 注意，如果整个列表中所有元素均相同，那么我们需要一个额外的退出条件
        // 添加一个 判断 newHead 是否等于 head 的条件即可
        // 在所有元素均相等的情况下，我们用哪一个作为最小值结点均可
        while(newHead->next->val >= newHead->val && newHead->next != head)
        {
            newHead = newHead->next;
        }
        // 循环结束时，newHead 指向的是整个列表中最大值所在的结点，我们只需要往后挪一位，就是全局最小值的结点
        // 不过由于后续代码的需要，这里我们先不挪了
        Node* rec1 = nullptr, * first = newHead->next;
        // first 从最小值结点开始遍历整个列表，找出第一个不小于 insertVal 的结点
        while(true)
        {
            // 如果 first->val 现在是不小于 insertVal 的，那么我们记录这个结点，并退出循环即可
            if(first->val >= insertVal)
            {
                rec1 = first;
                break;
            }
            // 否则，继续遍历
            first = first->next;
            // 走完了一圈，退出循环即可
            if(first == newHead->next)
            {
                break;
            }
        }
        // 如果 rec1 是空的，那么说明我们没有找到任何一个不小于 insertVal 的结点信息
        // 我们接着按同样的方法来寻找 rec2，定义为最后一个小于 insertVal 的结点信息
        Node* rec2 = nullptr, * second = newHead->next;
        // 注意：我们要找的是 "最后一个小于 insertVal 的结点"，所以我们实际上需要一个 pre 来记录信息，rec2 可以胜任这个职责
        while(true)
        {
            // 如果 first->val 现在是不小于 insertVal 的，那么 rec2 就是结果了
            if(second->val >= insertVal)
            {
                break;
            }
            // 否则，记录 rec2，并继续遍历
            rec2 = second;
            second = second->next;
            // 走完了一圈，结束循环即可
            if(second == newHead->next)
            {
                break;
            }
        }
        // 根据 rec1 和 rec2 的值，决定最后的处理
        Node* newNode = new Node(insertVal);
        // 1. rec1 为空，rec2 非空 (注意二者不可能全为空)
        if(!rec1)
        {
            // 此时 insertVal 大于列表中的所有结点，我们把 insertVal 接到 rec2 后面即可
            newNode->next = rec2->next;
            rec2->next = newNode;
            return head;
        }
        // 2. rec2 为空，rec1 非空
        if(!rec2)
        {
            // 类似上面的描述
            // insertVal 不大于列表中的所有结点
            // 那么我们直接把 insertVal 放到 rec1 前面即可
            // 不过注意，此时我们还需要一个全链表最大数据信息
            // 你会发现，这就是前面我们保留了的 newHead！(我知道很巧合，但这就是很巧合！)
            newNode->next = newHead->next;
            newHead->next = newNode;
            return head;
        }
        // 3. 二者均非空
        // 此时按定义来做就行
        newNode->next = rec1;
        rec2->next = newNode;
        return head;
}