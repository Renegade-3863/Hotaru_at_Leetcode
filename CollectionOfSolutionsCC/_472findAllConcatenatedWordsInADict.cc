#include "Solution.h"

// 字典树的结点，每个结点存储一个包含 26 个指向下一个字符的指针的数组
class TrieNode
{
public:
    // 以及一个标记位，用于记录这个字符是不是一个存储过的单词的结尾
    bool isEnd;
    // nxt 数组代表下一步可以走的字符
    // 这里使用 unique_ptr 的原因在于：字典树本身是个复杂的结构，内部 new 出来的内存空间很多，当然可以自己写 delete 递归返还空间，但是用智能指针自动化处理更方便快捷
    unordered_map<char, unique_ptr<TrieNode>> nxt;

    // 构造和析构函数
    TrieNode() : isEnd(false) {}
    ~TrieNode() = default;
};

class Trie
{
public:
    unique_ptr<TrieNode> root;
    Trie() { this->root = make_unique<TrieNode>(); }
    // 一棵字典树必然包含一个根结点，实际上这里的实现可以和 TrieNode 合并，不过我们为了定义上更好理解，做了一下封装
    // 成员函数，我们回忆一下字典树都需要哪些操作
    // 1. 字典树需要一个向其中添加一个新单词的方法，我们命名为 addWord
    // word 为要添加的字符串
    void addWord(const string& word)
    {
        // 获取根结点，用于后面的遍历操作
        TrieNode* cur = this->root.get();
        // 我们需要按字符把 word 中的每个字符都添加到 root 对应的结点中去，所以遍历循环就是按照 word 来进行的
        for(const auto& c : word)
        {
            // 检查 cur 内存储的数组的对应下标处是否有新结点，如果没有，就需要新建对应结点来代表对应字符的存在
            if(cur->nxt.find(c) == cur->nxt.end())
            {
                // 不存在，那么我们要进行新建
                cur->nxt[c] = make_unique<TrieNode>();
            }
            // 向下走一步
            cur = cur->nxt[c].get();
        }
        // 遍历完成，把对应位置结点的 isEnd 位设置为 true，代表这里结束了一个单词
        cur->isEnd = true;
        return;
    }

    // 2. 字典树需要从其中检索一个单词是否存在的方法，我们命名为 searchWord
    // word 为要搜索的字符串
    bool searchWord(const string& word)
    {
        // 获取根结点，用于后面的遍历操作
        TrieNode* cur = this->root.get();
        // 按字符进行检查，中间如果有找不到了的字符就直接退出
        for(const auto& c : word)
        {
            if(cur->nxt.find(c) == cur->nxt.end())
            {
                // 要找的单词在字典树中不存在，返回 false 即可
                return false;
            }
            // 否则，可以继续查找，深入一层
            cur = cur->nxt[c].get();
        }
        // 正常结束，不过我们需要确保这个 word 不是一个前缀
        return cur->isEnd;
    }
    
    // 3. 虽然一般的字典树都支持前缀查找，不过本题用不到，就不写了
};

// dfs 函数的定义修正一下：代表在 trie 指向的这个字典树中，是否存在至少两个单词可以构成 word 以 start 开始的子字符串
bool dfs(const string& word, int start, const Trie* trie)
{
    // 定义一个递归的基本结果：word.size() == start，此时说明 word 已经走到了结尾，start 代表的是一个空串，那么结果肯定是 true
    if(word.size() == start)
    {
        return true;
    }
    // 否则，我们在 trie 中按顺序检查 word[start] 以及后面的字符组成的序列是否存在于 trie 中
    TrieNode* cur = trie->root.get();
    for(int i = start; i < word.size(); ++i)
    {
        if(cur->nxt.find(word[i]) == cur->nxt.end())
        {
            // 遇到了一个不存在的字符，那么我们直接返回 false，代表不存在即可
            return false;
        }
        // 否则，遍历这个字符
        cur = cur->nxt[word[i]].get();
        // 如果下一个字符就是一个结尾，那么代表我们已经找到了一个子串，那么需要进一步检查下一半字符串
        if(cur->isEnd)
        {
            // 这里多说一句：本题限定了 words 中不包含重复，不然这里有可能会找出：word 本身 + 一个空的结尾字符串的情况
            // 如果放宽限定，允许包含重复单词，那么这里还要多加一步检查找出来的是不是上面这种非法情况
            if(dfs(word, i+1, trie))
            {
                // 后面的部分在字典树中找到了，那么我们直接返回 true 即可
                return true;
            }
            // 否则，没找到，那么我们丢弃这个 isEnd 符号，继续往后检查
        }
    }
    // 整个遍历完成，没有在中间找到分割点，那么说明我们要么是整个字符串都在字典树中，要么是这个字符串是一个前缀，两种情况都不符合题意，返回 false 即可
    return false;
}

vector<string> Leetcode401_500::Soltuion::findAllConcatenatedWordsInADict(vector<string>& words)
{
    // 字典树模版题，我们借机会再复习一下字典树的设计逻辑
    // 字典树的结构声明和方法定义单独写在外面
    // 定义好了字典树的基本结构，我们获取一个字典树对象来用就行
    // 不用额外 new 空间，声明一个自动变量就行
    Trie* trie = new Trie();
    // 我们重新检查一下题目的要求
    // 题目要求我们返回所有可以由列表中另外两个单词构成的字符串组成的集合
    // 那么我们可以把 words 数组按照字符串长度进行排序，因为长度短的字符串一定不会由更长的字符串构成
    // 所以我们先把那些长度更短的字符串添加到字典树中，可以方便后面对更长字符串的检查
    // 排序用 sort 函数即可，自己再写个快排有点太费时间了
    // 排序规则为：长度更短的在前，长度相等的不用重新排序，保持原来的相对顺序就行
    sort(words.begin(), words.end(), [&](const string& a, const string& b) -> bool {
        return a.size() < b.size();
    });
    // 用来保存结果的数组
    vector<string> res;
    // 排序完成后，剩下的就是遍历+检查了
    for(const auto& word : words)
    {
        // 对于每个单词，我们先对其进行遍历，检查它是不是由两个长度更短的字符串构成的
        // 写到这里忽然发现本题的字典树搜索函数需要进行一些变形，因为我们要找的东西的定义实际上是：
        // 对于单词 word，内部是否存在两个起点 a 和 b，这两个起点分别对应两个在字典树中存在的单词
        // 那么我们可以在上面定义这样的一个函数：
        // dfs(const string& word, int start, const Trie& trie)
        // 代表：trie 代表的字典树中，是否存在以 word 单词的 start 下标开始，向后延伸一定长度的一个单词
        // 内部的具体实现就根据本题的要求进行即可
        // 跳过空串，否则结果中会包含空串，这是错误的
        if(word.size() == 0)
        {
            continue;
        }
        // 如果这个单词是连接词，那么我们把它添加到结果数组中即可，不用添加到字典树中，因为这样会导致重复遍历
        if(dfs(word, 0, trie))
        {
            res.push_back(word);
        }
        else
        {
            trie->addWord(word);
        }
    }
    return res;
}