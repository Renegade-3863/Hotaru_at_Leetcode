#include "Solution.h"

Leetcode601_700::Soltuion::AutocompleteSystem::AutocompleteSystem(vector<string> sentences, vector<int>& times)
{
    // 把 sentences 中的句子存储到 this->root 中，并把对应的 time 值存到
    int n = sentences.size();
    this->root = new trie('\0');
    for(int i = 0; i < n; ++i)
    {
        this->root->trieInsert(sentences[i], times[i]);
    }
}

Leetcode::Soltuion::AutocompleteSystem::~AutocompleteSystem()
{
    delete this->root;
}

vector<string> Leetcode601_700::Soltuion::AutocompleteSystem::input(char c)
{
    this->inputs.push_back(c);
    // cout << "Searching" << endl;
    vector<pair<string, int>> res = this->root->searchPrefix(this->inputs);
    // cout << "Problem above" << endl;
    sort(res.begin(), res.end(), [&](const pair<string, int>& a, const pair<string, int>& b) -> bool
    {
        return a.second == b.second ? a.first < b.first : a.second > b.second;
    });
    // 输出前三个即可
    vector<string> ans;
    for(int i = 0; i < res.size() && i < 3; ++i)
    {
        ans.push_back(res[i].first);
    }
    return ans;
}