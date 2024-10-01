#include "Solution.h"

Leetcode101_200::Solution::LRUCache::LRUCache(int _capacity) : capacity(_capacity), size(0) {
    duLinkedNode* dummy = new duLinkedNode(-1, -1);
    this->head = dummy;
    this->tail = dummy;
    this->head->prev = this->tail;
    this->head->next = this->tail;
    this->tail->prev = this->head;
    this->tail->next = this->head;
}

Leetcode101_200::Solution::LRUCache::~LRUCache()
{
    // 需要删除哨兵结点，防止内存泄漏
    delete head;
}

int Leetcode101_200::Solution::LRUCache::get(int _key) {
    // 注意，我们可以通过哈希表简单地判断出 _key 值是否存在于存储中，不过还需要对链表进行调整
    // 把刚访问的数据结点放到链表的头部
    // 如果数据不存在于存储中，因而也无需对链表进行调整，可以直接返回-1
    if(mapping.find(_key) == mapping.end())
    {
        return -1;
    }
    // 先定位对应结点
    duLinkedNode* node = mapping[_key];
    // 把这个结点挪到链表的头部
    // 按步骤来，不会出问题
    // 1. 把结点从链表中拿出来
    node->prev->next = node->next;
    node->next->prev = node->prev;
    // 2. 把结点插到链表头部
    head->next->prev = node;
    node->next = head->next;
    head->next = node;
    node->prev = head;
    // 返回对应结点中存储的值
    return node->val;
}

void Leetcode101_200::Solution::LRUCache::put(int _key, int _value) {
    // 还是先确认链表中是否存在这个要添加的结点 {_key, _value}
    if(mapping.find(_key) != mapping.end())
    {
        duLinkedNode* node = mapping[_key];
        // 修改结点的值
        node->val = _value;
        // 同时别忘了把这个结点调整到链表头部
        // 1. 把结点从链表中拿出来
        node->prev->next = node->next;
        node->next->prev = node->prev;
        // 2. 把结点插到链表头部
        head->next->prev = node;
        node->next = head->next;
        head->next = node;
        node->prev = head;
        // 调整结束后，就可以结束了
        return;
    }
    // 否则，这个结点不存在，我们需要新建一个结点插入到链表的头部
    duLinkedNode* newNode = new duLinkedNode(_key, _value);
    // 进行头插
    head->next->prev = newNode;
    newNode->next = head->next;
    head->next = newNode;
    newNode->prev = head;
    // 在哈希表中添加记录
    mapping[_key] = newNode;
    // 别忘了，如果当前链表中的结点总数超出了 capacity，我们需要逐出最久未使用的结点
    if(++size > capacity)
    {
        // 通过 tail 指针找到链表的最后一个结点
        duLinkedNode* deserted = tail->prev;
        // 把最后一个结点抽出来
        deserted->prev->next = deserted->next;
        deserted->next->prev = deserted->prev;
        // 删去哈希表中对应的记录
        mapping.erase(deserted->key);
        // 删掉这个最后一个结点即可
        delete deserted;
        // 调整 size
        --size;
    }
    // 结束后返回
    return;
}