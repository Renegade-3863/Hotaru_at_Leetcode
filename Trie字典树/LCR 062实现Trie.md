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
    ![a picture](https://github.com/Renegade-3863/Hotaru_at_Leetcode/blob/main/Trie%E5%AD%97%E5%85%B8%E6%A0%91/LCR%20062%E5%AE%9E%E7%8E%B0Trie.jpeg)