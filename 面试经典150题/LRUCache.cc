#include <iostream>

class LinkedNode {
public:
    // 前向指针
    LinkedNode* prev;
    // 后向指针
    LinkedNode* next;
    // 数据块
    int value;
    // 用于反向追踪索引对
    int key;
    LinkedNode() = default;
    LinkedNode(int _key, int _value) : prev(nullptr), next(nullptr), key(_key), value(_value) {}
};


class LRUCache
{
public:
    LRUCache(int _capacity)
    {
        // 初始化缓存大小，以及初始化一对表头和表尾结点
        this->capacity = _capacity;
        this->size = 0;
        this->head = new LinkedNode();
        this->tail = new LinkedNode();
        // 维护好指针的关系
        this->head->next = this->tail;
        this->tail->prev = this->head;
        // 链表不需要循环
    }

    int get(int key)
    {
        // 获取对应 key 的值，并把对应的结点（如果存在）放到链表表头
        if(this->mapping.find(key) != this->mapping.end())
        {
            // 索引存在，那么我们直接返回链表对应结点中保存的值即可
            // 但是别忘了把结点提升到表头
            LinkedNode* node = this->mapping[key];
            this->moveToHead(node);
            // 返回结果即可
            return node->value;
        }
        // 否则，不存在对应结点，返回 -1 即可
        return -1;
    }
    
    void put(int key, int value)
    {
        // 不存在，要新建
        if(this->mapping.find(key) == this->mapping.end())
        {
            // 新建一个结点，并记录到 mapping 中
            this->mapping[key] = new LinkedNode(key, value);
            // 把新结点插入到链表表头
            this->addToHeaed(this->mapping[key]);
            // 对 size 加 1，如果超容量了，要删除最久未使用的结点
            if(++size > capacity)
            {
                LinkedNode* node = this->tail->prev;
                if(node != head)
                {
                    this->mapping.erase(node->key);
                }
                this->deleteNode();
                --size;
            }
            // 不用做其它事务了
            return;
        }
        // 否则，已经存在，我们需要修改 value 的值，并进行结点提升
        this->mapping[key]->value = value;
        // cout << "Put move\n";
        this->moveToHead(this->mapping[key]);
        // size 不用修改
        return;
    }
    int capacity;
    // 记录当前缓存的大小
    int size;
    LinkedNode* head;
    LinkedNode* tail;
    // 哈希索引
    unordered_map<int, LinkedNode*> mapping;

    // 编写一些 helper function，先在这里进行声明
    /*
        把一个链表结点 node 提升到 this 代表的双向链表的表头
    */

    // 注意，node 不能是 head/tail 结点本身
    void moveToHead(LinkedNode* node)
    {
        // 步骤1. 把 node 从链表中取出来
        // 提问：如果 node 就是 this->head->next，会有问题吗？
        // 下面的代码在这种情况下，会先把 node 从链表中分离出来，再把结点插回表头，实际上是无用功，可以省略
        if(node == this->head->next)
        {
            return;
        }
        // cout << "Moving...";
        // cout << node->value << endl;
        node->prev->next = node->next;
        node->next->prev = node->prev;
        node->prev = this->head;
        node->next = this->head->next;
        node->next->prev = node;
        this->head->next = node;
    } 

    /*
        删除当前链表中最久未使用的结点
    */
    void deleteNode()
    {
        // 如果链表中没有任何结点，那么我们什么也不做
        if(this->head->next == this->tail)
        {
            return;
        }
        // 否则，我们删除 this->tail->prev 即可
        // 别忘了修改一下 capacity，不过为了写法统一，我们不在这里写
        LinkedNode* node = this->tail->prev;
        // 注意修改其它相关指针
        this->tail->prev = node->prev;
        node->prev->next = this->tail;
        // cout << "Deleted: " << node->value << endl;
        delete node;
        node = nullptr; 
    }
    
    /*
        头插法，把 node 添加插入到当前链表的头部
    */
    void addToHeaed(LinkedNode* node)
    {
        this->head->next->prev = node;
        node->next = this->head->next;
        this->head->next = node;
        node->prev = this->head;
    }
};

/*
    LRU 缓存全名为：Least Recent Usage 缓存，即 “最近最少使用缓存”
    根据对它特性的研读，我们可以自然地想到可以使用链表来实现这个缓存
    基本的想法是：
    使用一个数据层，也就是一个链表（双向），来保存实际的数据结点
    再使用一个类似哈希表的索引结构，来对链表中的数据结点进行跟踪
    哈希表的基本结构是：key -> 链表结点，而不是 key -> value，value 保存在对应的链表结点中即可
    之后，每次的 put 操作，我们只需要在上层的哈希结构中查找是否存在对应的 key 值即可
    如果存在对应的 key 值，那么我们可以把对应的双向链表结点提升到链表的表头（即修改成最近使用过的数据）
    否则，就向链表表头插入一个新的数据结点，并把索引插入到哈希表中即可
*/