#include "Solution.h"

// 对树对象进行初始化，我们实际上不需要执行任何操作
// Debug 后：放屁，你的智能指针都 tm 没初始化，make_unique 被你吃了？
Leetcode201_300::Solution::Trie() { this->root = make_unique<TrieNode>(); }

// 析构也一样
Leetcode201_300::Solution::~Trie() {}

void Leetcode201_300::Solution::insert(string word)
{
    // 将某个单词插入到这棵字典树中，操作应该是什么样的？
    // 不难想象我们应该顺着 word 在树中一个一个字符的检查，体现为对树进行深入
    // 路上如果遇到某一层不存在对应的字符，我们就构造对应的树结点，并继续深入
    // 直到整个单词遍历完成，我们还需要把最后一个树结点的 isEnd 参数标记为 true，代表如果通过这条路径找到了这里，我们可以断定这个单词已经添加过了
    // 直接对整个单词进行遍历
    // 取出裸指针来使用
    TrieNode* cur = this->root.get();
    for(const char& c: word)
    {
        // 如果这个结点中没有建立对应字符的映射，那么我们要添加这个结点并建立映射
        if(cur->mapping.find(c) == cur->mapping.end())
        {
            // 新建结点
            // 直接调用默认构造函数即可
            // 建立映射关系
            // 注意一点，这里如果你是先建立一个智能指针变量 newNode = make_unique<TrieNode>()
            // 再把它赋值给 cur->mapping[c]，那么会触犯 unique_ptr 不允许拷贝构造的天条，所以这里需要直接进行构造
            // 个人认为这样不会出错的原因可能在于：C++ 的哈希表只是建立一个对值的引用/指向关系，而我们的 make_unique 只会构建一次这个智能指针的临时变量，就被一个长期存在的哈希表给绑定了，所以它显然没有违反 unique_ptr 不允许拷贝构造的原则 
            cur->mapping[c] = make_unique<TrieNode>();
        }
        // 进行深入，到达字符 c 所在的结点位置
        cur = cur->mapping[c].get();
    }
    // 遍历完成，我们把这个树结点的 isEnd 标记标记为 true
    cur->isEnd = true;
    return;
}

bool Leetcode201_300::Solution::Trie::search(word)
{
    // 要实现在一棵前缀树中搜索某个单词，过程其实和添加单词是一模一样的，只是一些情况下的处理方法不同而已
    TrieNode* cur = this->root.get();
    for(const char& c: word)
    {
        if(cur->mapping.find(c) == cur->mapping.end())
        {
            // 此时，我们发现这个字符 c 没有存在于当前结点的下一个字符信息表中，说明这个单词一定不存在，直接返回 false 即可
            return false;
        }
        // 否则，我们继续深入到字符 c 所在的结点
        cur = cur->mapping[c].get();
    }
    // 最后，由于我们要找的是这个单词本身，而不是它是否是个前缀，所以还要检查这个结点的 isEnd 信息
    return cur->isEnd;
}

bool Leetcode201_300::Solution::Trie::startwWith(string prefix)
{
    // 也是和 search 几乎一样的过程，区别只在于我们最后返回的一定是 true，而不是还要检查一下 isEnd
    TrieNode* cur = this->root.get();
    for(const char& c: word)
    {
        if(cur->mapping.find(c) == cur->mapping.end())
        {
            return false;
        }
        cur = cur->mapping[c].get();
    }
    return true;
}