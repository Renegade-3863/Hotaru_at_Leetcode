#include "Solution.h"

string Leetcode601_700::Soltuion::replaceWords(vector<string>& dictionary, string sentence)
{
    // 经典的字典树类问题 
    // 我们可以把所有 dictionary 中的元素保存到一棵高效查找的字典树 trie 中
    // 之后对 sentence 中的每一个用空格分隔的单词进行检索
    // 如果某个单词在 trie 中按前缀出现了
    // 那么我们就把它替换成这个前缀即可 (这样我们也可以实现题目要求的最短替换)
    // 获取一棵字典树
    Trie* trie = new Trie();
    string ans = "";
    // 之后把 dictionary 中的单词插入到 trie 中
    for(const auto& word : dictionary)
    {
        trie->TrieInsert(word);
    }
    // 插入完成，我们接下来对 sentence 中的单词进行分割查询
    // 并把每个单词的最后转化结果保存到一个 string 数组中
    vector<string> tmp;
    int n = sentence.size();
    // cur 用于记录 sentence 的每一个单词
    string cur = "";
    for(int i = 0; i <= n; ++i)
    {
        if(i == n || sentence[i] == ' ')
        {
            // 遇到了一个空格，或者整个 sentence 的结尾，我们需要对已经取出的这个单独的单词进行检查和可能的简化
            string simp = trie->TriePrefixSearch(cur);
            if(!simp.empty())
            {
                // 有前缀，就加前缀
                tmp.emplace_back(simp);
            }
            // 没前缀，就加原单词
            else
            {
                tmp.emplace_back(cur);
            }
            // 重置 cur
            cur = "";
        }
        else
        {
            // 一个单词还没结束，我们补充 cur 单词
            cur.push_back(sentence[i]);
        }
    }
    // 构造答案
    string res = "";
    for(const auto& word : tmp)
    {
        res += word;
        res.push_back(' ');
    }
    // 弹出最后一个空格
    res.pop_back();
    // 别忘了释放内存空间，或者对 trie 用 unique_ptr 也可以
    delete trie;
    return res;
}