#include "Solution.h"

Leetcode601_700::Soltuion::MapSum::MapSum()
{
    // 新建内部的结点，使用 make_unique 函数
    this->trie->root = make_unique<TrieNode>();
}

void Leetcode601_700::Soltuion::MapSum::insert(string key, int val)
{
    this->trie->addWord(key, val);
}

int Leetcode601_700::Soltuion::MapSum::sum(string prefix)
{
    return this->trie->checkPrefix(prefix);
}