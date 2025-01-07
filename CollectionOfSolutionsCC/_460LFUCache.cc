#include "Solution.h"

// 比较经典的一道数据结构设计题，难度不大，但是涉及到的细节问题较多，所以可能会需要我们在编写程序的时候更加细致入微
// 我们先研究一下题目的要求：
// 其实最基本，也是最关键的要求就是：
// 在插入一个新的、不存在的键值对的时候，如果容量达到了上限，那么我们需要逐出 "最久未使用的键值对"
// 其它的基本存储单元用链表/双向链表都是可以简单实现的
// 而题目要求我们在删除 "最久未使用的键值对" 的时候也要 O(1) 的时间复杂度，所以我们需要一种高效的结构来定位到一个要删除的结点
// 那么我们就可以使用一种类似哈希表+双向链表的格式来进行结构设计
// 具体地，我们可以维护一组双向链表
// 每条双向链表维护一组特定出现次数的键值对
// 同时用另一个键-值哈希表来满足 get 函数的定位要求
// 最后，为了高效地定位对应出现次数的双向链表，我们可以在这一组双向链表外面嵌套一层哈希表
// 即：<出现次数, 对应的双向链表头结点>
// 至于双向链表的实现，我们可以尝试自己来写，也可以使用 C++ STL 的 list 结构，这里我们给出自定义的实现方法
// duLinkedNode 的结构定义在 Solution.h 中对应位置实现

// 声明一下，下面的第一版代码实际上是假的 "全 O(1)"
// 以身犯法给大家演示一下思考不细致导致的结果
// 一个很关键的注意点：
// 题目还有一个细节要求：在 "最久未使用链表" 中做删除的时候，不能随意的删除任何一个，需要删除最早被使用的那一个结点，换句话说，如果我们按照头插法进行结点添加
// 那么就不得不在删除的时候用线性的时间遍历对应的双向链表，这样时间复杂度就不完美了
// 可行的解决办法是使用双向 "循环" 链表，不过第一版代码要改成这样太麻烦了，不如后面有时间的来重写一遍第二版。。。
// 以此警示自己，也警示所有刷这道题的人吧。。。 =^=

Leetcode401_500::Soltuion::LFUCache::LFUCache(int _capacity) : capacity(_capacity), size(0), minCnt(INT_MAX)
{
    // 不需要做其它事情，两个哈希表编译器会帮我们自动初始化
}

int Leetcode401_500::Soltuion::LFUCache::get(int key)
{
    // get 函数的目的是定位一个键值对是否存在于 cache 中，我们可以用 mapping 来实现检索
    // get 函数的目的是定位一个键值对是否存在于 cache 中，我们可以用 mapping 来实现检索
    if(mapping.find(key) == mapping.end())
    {
        // 不存在，此时直接返回 -1
        return -1;
    }
    // 否则，键值对存在，但是我们还需要调整这个键值对，修改它所在的链表
    // 检出这个键值对的出现次数，存储在 freq 值中
    int cnt = mapping[key]->freq;
    // 别忘了给 mapping[key]->freq 加一，以保持数据的一致性
    ++mapping[key]->freq;
    // 获取对应链表的头结点
    duLinkedNode* head1 = lists[cnt];
    // 之后是尝试获取 cnt+1 对应的双向链表的头结点，如果不存在，那么需要先创建再做后续处理
    if(lists.find(cnt+1) == lists.end())
    {
        lists[cnt+1] = new duLinkedNode();
    }
    duLinkedNode* head2 = lists[cnt+1];
    // head1 和 head2 都获取完成，剩下的就是调用 moveduLinkedNode 函数了
    moveduLinkedNode(head1, head2, mapping[key]);
    // 如果清除对应结点后，链表空了，那么要删除记录
    if(!lists[cnt]->next)
    {
        delete lists[cnt];
        lists.erase(cnt);
    }
    // 别忘了维护 minCnt 变量的值
    if(lists.find(mapping[key]->freq-1) == lists.end() && minCnt == mapping[key]->freq-1)
    {
        minCnt = mapping[key]->freq;
    }
    // 移动完成后，我们要处理的事情就都完成了，返回 mapping[key]->value 即可
    return mapping[key]->value;
}

void Leetcode401_500::Soltuion::LFUCache::put(int _key, int _value)
{
    // put 函数比较复杂，我们一步步来看
    // 第一步：检查 key 键是否已经存在于 cache 中了
    duLinkedNode* curNode = nullptr;
    if(mapping.find(_key) != mapping.end())
    {
        // 如果已经存在了，那么我们需要修改对应结点的值
        mapping[_key]->value = _value;
        curNode = mapping[_key];
        // 给对应结点的 freq 增加一次
        ++curNode->freq;
        // 之后是结点的移动，这个 if 不涉及到超容量的问题，比较简单
        // 依然是检查 curNode->freq 对应的双向链表是否存在
        if(lists.find(curNode->freq) == lists.end())
        {
            // 不存在，需要先创建
            lists[curNode->freq] = new duLinkedNode();
        }
        // 之后是进行移动
        // 把 curNode 从 lists[curNode->freq-1] 移动到 lists[curNode->freq] 中
        moveduLinkedNode(lists[curNode->freq-1], lists[curNode->freq], curNode);
        if(!lists[curNode->freq-1]->next)
        {
            delete lists[curNode->freq-1];
            lists.erase(curNode->freq-1);
        }
        // 维护 minCnt 的定义
        if(lists.find(curNode->freq-1) == lists.end() && minCnt == curNode->freq-1)
        {
            minCnt = curNode->freq;
        }
        // 逻辑结束
    }
    else
    {
        // 对应结点不存在，那么我们需要新建结点并添加
        // 1. cache 已经满了，那么我们需要 "逐出最久未使用的一个结点"
        if(size == capacity)
        {
            // 根据 minCnt 定位保存了最久未使用结点的双向链表
            // cout << minCnt << endl;
            duLinkedNode* target = lists[minCnt];
            while(target->next)
            {
                target = target->next;
            }
            int tmpKey = target->key;
            deleteduLinkedNode(lists[minCnt], target);
            // 如果删除后，target->next 为空，我们需要删除这个空表
            // 别忘了删除 mapping 中对应的记录
            mapping.erase(tmpKey);
            if(!lists[minCnt]->next)
            {
                delete lists[minCnt];
                lists.erase(minCnt);
                // 维护 minCnt
                // 注意，这个情况下我们总是要新添加一个结点，所以 minCnt 应该总是 1
                // 所以这一步可以挪出去
            }
            // 否则，target 链表非空，那么不用做其它事
            // 维护 size
            --size;
        }
        // 2. cache 没满，这一步实际上和上面捏合到一起了，所以上面才需要 --size
        // 新建结点，用 _key 和 _value 对
        curNode = new duLinkedNode(_key, _value);
        // 执行插入操作，要插入到出现次数为 1 的链表中，需要先检查是否存在这个链表
        if(lists.find(1) == lists.end())
        {
            // 不存在，那么我们需要新建这个双向链表
            lists[1] = new duLinkedNode();
        }
        // 插入 curNode 即可
        insertduLinkedNode(lists[1], curNode);
        // 维护 minCnt
        minCnt = 1;
        ++size;
    }
    // 最后，别忘了给 mapping 赋值
    mapping[_key] = curNode;
    // 全部操作完成，返回
}