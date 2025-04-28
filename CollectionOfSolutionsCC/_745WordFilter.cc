#include "Solution.h"

Leetcode701_800::Soltuion::WordFilter::WordFilter(vector<string>& words)
{
    // 构造函数，我们初始化两个字典树
    this->trie1 = make_unique<TrieNode>();
    this->trie2 = make_unique<TrieNode>();
    // 之后把 words 中的单词分别添加到两个字典树中
    for(int i = 0; i < words.size(); ++i)
    {
        string revStr = words[i];
        reverse(revStr.begin(), revStr.end());
        this->trie1->insertWord(words[i], i);
        this->trie2->insertWord(revStr, i);
    }
    // 初始化完成，返回即可
}

int Leetcode701_800::Soltuion::WordFilter::f(string pref, string suff)
{
    // 我们调用定义好的 searchPrePost 函数即可
    return searchPrePost(this->trie1, this->trie2, pref, suff);
}