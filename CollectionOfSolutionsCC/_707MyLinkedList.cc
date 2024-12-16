#include "Solution.h"

Leetcode701_800::Soltuion::MyLinkedList::MyLinkedList()
{
    // 初始化函数，我们需要构造头尾哨兵结点
    // 哨兵结点的值可以随便指定，这里指定为 -1
    this->head = new biListNode(-1);
    this->tail = new biListNode(-1);
    this->length = 0;
    // 连接两个哨兵结点
    this->head->next = this->tail;
    this->tail->prev = this->head;
    // 我们只想要一个双向链表，不是循环链表，所以其它指针不用修改
}

// 获取下标 index 处的元素，头结点被视为是下标 0
int Leetcode701_800::Soltuion::MyLinkedList::get(int index)
{
    biListNode* traverse = this->head;
    // while(traverse)
    // {
    //     cout << traverse->val << "->";
    //     traverse = traverse->next;
    // }
    // cout << endl;
    // 如果下标不合法，我们直接返回 -1
    if(index >= this->length)
    {
        // cout << index << "->" << this->length << endl;
        return -1;
    }
    // 要获取对应链表中对应 "下标" 上的元素值，这个方法最简单的实现方式就是线性遍历
    // 这也是链表对比数组的缺点之一，访问效率低
    biListNode* cur = this->head;
    for(int i = 0; i <= index; ++i)
    {
        cur = cur->next;
    }
    // 下标合法，那么我们直接返回对应结点中的值即可
    return cur->val;
}

// 头插方法
void Leetcode701_800::Soltuion::MyLinkedList::addAtHead(int val)
{
    // cout << "HeadAdd" << endl; 
    // 新建结点
    biListNode* newNode = new biListNode(val);
    // 结点插入
    newNode->next = this->head->next;
    this->head->next->prev = newNode;
    this->head->next = newNode;
    newNode->prev = this->head;
    // 链表长度加一
    ++this->length;
    biListNode* traverse = this->head;
    // while(traverse)
    // {
    //     cout << traverse->val << "->";
    //     traverse = traverse->next;
    // }
    // cout << endl;
}

// 尾插方法
void Leetcode701_800::Soltuion::MyLinkedList::addAtTail(int val)
{
    // cout << "TailAdd" << endl; 
    // 新建结点
    biListNode* newNode = new biListNode(val);
    // 结点插入
    newNode->next = this->tail;
    newNode->prev = this->tail->prev;
    this->tail->prev->next = newNode;
    this->tail->prev = newNode;
    // 链表长度加一
    ++this->length;
    biListNode* traverse = this->head;
    // while(traverse)
    // {
    //     cout << traverse->val << "->";
    //     traverse = traverse->next;
    // }
    // cout << endl;
}

// 在指定下标 index 之前插入一个新结点，值为 val
void Leetcode701_800::Soltuion::MyLinkedList::addAtIndex(int index, int val)
{
    // cout << "IndexAdd" << endl; 
    // 这里有一个要求：index 超出了链表长度的时候，不进行插入，所以我们可以在链表对象中再记录一个动态的长度值
    // 我们通过 this->length 就可以知道 index 有没有超范围
    if(this->length < index)
    {
        // 超范围了，就不添加，直接返回
        return;
    }
    if(this->length == index)
    {
        // cout << "switch to tail" << endl;
        // 下标等于链表长度，那么我们调用 addAtTail 进行添加即可
        this->addAtTail(val);
        return;
    }
    // 否则，正常添加
    // 先线形遍历到下标为 index 的结点
    biListNode* cur = this->head;
    for(int i = 0; i <= index; ++i)
    {
        cur = cur->next;
    } 
    // 之后通过 prev 指针找出前驱结点，再进行结点插入
    // 新建结点
    biListNode* newNode = new biListNode(val);
    // 进行插入
    cur->prev->next = newNode;
    newNode->prev = cur->prev;
    cur->prev = newNode;
    newNode->next = cur;
    ++this->length;
    // biListNode* traverse = this->head;
    // while(traverse)
    // {
    //     cout << traverse->val << "->";
    //     traverse = traverse->next;
    // }
    // cout << endl;
}

// 删除下标为 index 的结点
void Leetcode701_800::Soltuion::MyLinkedList::deleteAtIndex(int index)
{
    // 我们先通过 this->length 判断下标是否有效
    if(this->length <= index)
    {
        // 下标不合法，直接返回，不进行删除操作
        return;
    }
    // 下标合法，我们可以执行删除操作
    // 还是需要通过遍历找到要删除的结点
    biListNode* cur = this->head;
    for(int i = 0; i <= index; ++i)
    {
        cur = cur->next;
    }
    // 通过 prev 指针找出前驱，执行删除操作
    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;
    delete cur;
    --this->length;
}