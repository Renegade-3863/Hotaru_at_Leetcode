#include "Solution.h"
/*
    class Node
    {
    public:
        int val;
        Node* next;
        Node* random;

        Node(int _val) {
            val = _val;
            next = NULL;
            random = NULL;
        }
    };
*/
Leetcode101_200::Node* Leetcode101_200::Solution::copyRandomList(Leetcode101_200::Node* head)
{
    // 题目要求我们根据一个给定的链表(包含随机分支)进行深拷贝
    // 那么我们可以使用和前面深拷贝图类似的方法来尝试求解
    // 依然先设定一个旧链表结点和新链表结点之间的映射哈希表
    unordered_map<Node*, Node*> mapping;
    // 使用递归/深搜的方式进行链表结点的构造
    function<void(Node*)> copy = [&](Node* original)
    {
        // 条件是，original 对应的结点已经被初始化过了
        // 先取出这个旧结点对应的新结点
        Node* cur = mapping[original];
        // 检查这个旧结点的几个指针域
        // 只有在没有被初始化时，我们才进行 next 指针的访问
        // 别忘了，如果这个旧结点本身没有后继指针，我们也不能进行下面 original->next->val 的调用
        if(original->next && mapping.find(original->next) == mapping.end())
        {
            // 创建这个新结点
            Node* newNode = new Node(original->next->val);
            // 存储好映射，同时也表明这个新结点已经被建立完成
            mapping[original->next] = newNode;
            // 赋值
            cur->next = newNode;
            // 深入进行后续复制
            copy(original->next);
        }
        // 再检查 random 指针
        // 注意，这里我们应该秉持这样的原则：
        // 如果这个指针指向的结点不存在，那么我们需要新创建这个指针(虽然从题意来看，这种情况不可能发生)
        // 如果这个指针指向的结点已经存在，那么我们仍然需要记录这个指向关系到新链表中
        if(original->random && mapping.find(original->random) == mapping.end())
        {
            // 创建这个由 random 指针链接到当前结点所在链表的结点
            Node* newNode = new Node(original->random->val);
            // 存储好映射
            mapping[original->random] = newNode;
            // 赋值
            cur->random = newNode;
            // 深入进行后续复制
            copy(original->random);
        }
        // 第二种情况，这个指针已经存在，那么我们不用新创建指针，只需要把 random 指针指向这个新结点
        else if(original->random)
        {
            cur->random = mapping[original->random];
        }
    };
    // 进行函数调用
    if(!head)
    {
        return nullptr;
    }
    Node* newHead = new Node(head->val);
    mapping[head] = newHead;
    copy(head);
    return newHead; 
}