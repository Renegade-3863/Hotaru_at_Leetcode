class SkipList
{
public:
    struct Node
    {
        int val;    // 节点值
        vector<Node*> next; // 记录节点在每一层的 next，next[i] 表示当前节点第 i 层的 next

        Node(int _val) : val(_val) {
            // 构造函数
            next.resize(level, NULL);       // 初始化 next 数组的大小和层数 level 相同，初始值都指向 NULL
        }
    }*head;

    Skiplist()
    {
        head = new Node(-1);                // 初始化一个链表头节点
    }

    ~Skiplist()
    {
        delete head;                        // 析构函数删除 head
    }

    // 辅助函数，找到每一层 i 小于目标值 target 的最大结点 pre[i]，最后 pre 中存的就是每一层小于 target 的最大结点
    void find(int target, vector<Node*>& pre)
    {
        auto p = head;
        for(int i = level-1; i >= 0; --i)
        {
            while(p->next[i] && p->next[i]->val < target) 
            {
                p = p->next[i];
            }
            pre[i] = p; // while 结束时，找到了第 i 层小于 target 的最大结点，就是 p 结点
        }
    }

    // 从跳表中查找 target
    bool search(int target)
    {
        vector<Node*> pre(level);
        find(target, pre);                      // 先找到每一层 i 小于目标值 target 的最大结点 pre[i]

        auto p = pre[0]->next[0];               // 获取唯一可能等于 target 值的结点信息
        return p && p->val == target;
    }

    void add(int num)
    {
        vector<Node*> pre(level);
        find(num, pre);                         // 先找到每一层 i 小于目标值 num 的最大结点 pre[i]

        auto p = new Node(num);                 // 创建要加入的新结点
        for(int i = 0; i < level; ++i)          
        {
            // 遍历每一层，从上往下插入新结点
            p->next[i] = pre[i]->next[i];
            pre[i]->next[i] = p;
            // 每一层有 50% 的概率不插入结点，如果这一层没有这个结点，那么上层也就没有这个结点，可以直接 break
            // 但是基于这里的逻辑，我们可以发现，第一层，也就是 level 0，是一定会加入 num 结点的
            if(rand() % 2) 
            {
                break;
            }
        }
    }

    // 从跳表中删除 num
    bool erase(int num)
    {
        vector<Node*> pre(level);           
        find(num, pre);                 // 先找到每一层 i 小于目标值 num 的最大结点 pre[i]

        // 先判断 num 是否存在，不存在直接返回 false
        // 第 0 层存储的是全部结点，所以只需要判断 pre[0]->next[0]（小于 num 的最大结点在第 0 层的 next）是不是 num 即可
        auto p = pre[0]->next[0];
        if(!p || p->val != num)
        {
            return false;
        }
        
        // 否则，删除每一层的 num，如果 pre[i]->next[i] == p 说明存在 p
        // 如果某一层的 next[i] 不再等于 p 了，那么我们也就没必要继续执行删除逻辑了，因为在添加的过程中，并不会存在分段添加的情况
        for(int i = 0; i < level && pre[i]->next[i] == p; ++i)
        {
            pre[i]->next[i] = p->next[i];       // 单链表删除
        }
        delete p;

        return true;
    }

    static const int level = 8; 
};