struct duLinkedNode
{
public:
    duLinkedNode() = default;
    duLinkedNode(int _key, int _value) : key(_key), value(_value), prev(nullptr), next(nullptr) {}

    duLinkedNode* prev;
    duLinkedNode* next;
    int key;
    int value;
};

class LRUCache
{
public:
    LRUCache(int _capacity) : capacity(_capacity), size(0)
    {
        // 新建双向链表的头和尾结点
        this->head = new duLinkedNode();
        this->tail = new duLinkedNode();

        // 初始化相关的指针
        this->head->next = this->tail;
        this->tail->prev = this->head;
    }

    int get(int key)
    {
        // key 不存在，那么直接返回 -1 即可
        if(this->mapping.find(key) == this->mapping.end())
        {
            return -1;
        }
        // 否则，我们先保存结果
        duLinkedNode* node = this->mapping[key];
        // 把 node 提升到双向链表的头部
        // helper function
        moveToHead(node);
        return node->value;
    }

    void put(int key, int value)
    {
        // key 不存在，那么我们新建结点并进行添加，注意添加 mapping 中的对应项
        duLinkedNode* node = nullptr;
        if(this->mapping.find(key) == this->mapping.end())
        {
            node = new duLinkedNode(key, value);
            this->mapping[key] = node;
            // 修改缓存大小，如果超容量了，需要逐出 tail->prev 这个结点
            ++this->size;
            if(this->size > this->capacity)
            {
                deleteLast();
                // 修正 size
                --size;
            }
            // 把新结点添加到链表头部
            addToHead(node);
            // 到这里，处理完成，可以直接返回了
            return;
        }
        // key 已经存在，那么我们修改对应的键值，并把对应结点放到链表头部即可
        node = this->mapping[key];
        moveToHead(node);
        node->value = value;
        // 处理完成，返回即可
    }

    /*
        Helper Functions
    */
    void moveToHead(duLinkedNode* node)
    {
        // 1. 把 node 从链表中取出
        node->prev->next = node->next;
        node->next->prev = node->prev;
        
        // node->next = nullptr
        // node->prev = nullptr

        // 2. 把 node 插入到链表头部
        node->next = this->head->next;
        node->prev = this->head;
        node->next->prev = node;
        this->head->next = node;
    }

    void deleteLast()
    {
        // 1. 获取最后一个结点的信息
        duLinkedNode* node = this->tail->prev;
        // 删除 mapping 中对应的键值对
        this->mapping.erase(node->key);
        // 删除节点，别忘了 delete
        node->prev->next = this->tail;
        this->tail->prev = node->prev;
        delete node;
        node = nullptr;
    }

    void addToHead(duLinkedNode* node)
    {
        this->head->next->prev = node;
        node->next = this->head->next;
        this->head->next = node;
        node->prev = this->head;
    }

    duLinkedNode* head;
    duLinkedNode* tail;
    int capacity;
    int size;
    unordered_map<int, duLinkedNode*> mapping;
};