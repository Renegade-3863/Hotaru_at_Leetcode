# 实现一棵Trie字典树

&emsp; 本题个人认为是一道很不错的数据结构基础题目, **字典树**是一种数据库及其它后端套件中非常常用的高效搜索结构
形象的图片讲解可以看OI wiki的相关讲解: [字典树](https://oi-wiki.org/string/trie/)。

### 基本实现思路
- 按层记录已有字典单词中的每一个字符(注意不一定是常规的大小写字符)
- 每一层的每个字符本身都对应了一个子字典树
#### 按上面的结构设计, 不难写出如下的数据结构定义:
``` C++
class Trie {
    // 当前访问的结点字符值
    char c;
    // 当前字符对应的所有可能的子字典树
    // 注意这里使用了unique_ptr智能指针, 用于便利内存的分配回收
    unordered_map<char, unique_ptr<Trie>> data;
    bool isEnd

    // Trie的构造函数
    Trie();
    
    // insert函数用于向树中插入一个新的单词
    void insert(const string& word);
    
    // search函数用于查找目前的树中是否存在查询的单词word
    void search(const string& word);

    // prefix函数用于查找目前的树中是否存在查询的前缀prefix
    void isPrefix(const string& prefix);
};
```

#### 这也是本题(LCR 062)考察的内容

&emsp; 如何实现上面的三个函数呢?

- 基本思路:
1. insert函数:
    - 遍历整个字符串word, 对每一个字符c进行插入
    - 插入动作为: 
        - 如果树中当前层存在c对应的子树, 那么无需任何操作, 直接向下深入一层进入下一层的子字典树
        - 否则, 在当前层新建一个字符c对应的子树, 并向下深入一层进入到下一层的字典树
        - 当对于整个字符串的插入已经结束, 将当前层的isEnd标记计做true
2. search函数:
    - 遍历整个字符串word, 对每一个字符c进行检查
    - 检查操作为:
        - 如果树中当前层存在c对应的子树, 那么直接深入一层进入下一层的子字典树
        - 当对于整个字符串的检查已经结束, 那么检查当前层的isEnd标记, 如果isEnd为true, 那么表明这个字符串整体是存在的, 否则不存在
3. isPrefix函数:
    - 遍历整个前缀串prefix, 对每一个字符c进行检查
    - 检查操作为:
        - 如果树中当前层存在c对应的子树, 那么直接深入一层进入下一层的子字典树
        - 当对于整个前缀串的检查已经结束, 那么代表当前字典树中记录有以当前前缀串作为前缀的字符串, 直接返回true即可

&emsp; 下面是整个树结构一部分的图片描述
![a picture](https://github.com/Renegade-3863/Hotaru_at_Leetcode/blob/main/Trie%E5%AD%97%E5%85%B8%E6%A0%91/LCR%20062%E5%AE%9E%E7%8E%B0Trie.jpeg)

可以想象成, 最上面一层的结点的char字段没有有意义的字符值, 每一个字符都有一个对应的isEnd字段, 代表是否存在一个到当前字符结束的单词

有人可能会对这种实现机制有一点质疑: 是否会存在错误记录, 就是有相同后缀的单词, 字典树只记录了其中一个, 然而后续搜索的时候错误判断了另一个单词的存在?

**显然不可能** 
- 如果只有真后缀相等: 比如mit和hit, 记录了mit, 要查找hit, 那么在第一位的m和h处, search函数就已经判定h在字典树中不存在而返回false了, 不会进行到最后一步对isEnd的判断
- 否则, 如果后缀相等, 那么代表要找的字符串和记录的字符串一致, 那么返回true也是对的

根据上面的理解, 就不难写出下面的实现代码:
``` C++
class Trie {
private:
    unordered_map<char, unique_ptr<Trie>> data;
    bool isEnd;
public:
    /** Initialize your data structure here. */
    Trie() : isEnd(false) {}
    
    /** Inserts a word into the trie. */
    void insert(const string& word) {
        // 一个指向Trie类型对象的指针cur
        Trie* cur = this;
        for(const char& c: word) {
            if(cur->data.find(c) == cur->data.end())
                cur->data[c] = make_unique<Trie>();
            cur = cur->data[c].get();
        }
        cur->isEnd = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(const string& word) {
        const Trie* cur = this;
        for(const char& c: word) {
            if(cur->data.find(c) == cur->data.end())
                return false;
            cur = cur->data.at(c).get();
        }
        return cur->isEnd;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(const string& prefix) {
        const Trie* cur = this;
        for(const char& c: prefix) {
            if(cur->data.find(c) == cur->data.end())
                return false;
            cur = cur->data.at(c).get();
        }
        return true;
    }
};
```