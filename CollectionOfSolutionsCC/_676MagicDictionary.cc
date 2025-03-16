#include "Solution.h"

class Leetcode601_700::Soltuion::MagicDictionary::MagicDictionary()
{
    this->trie = new Trie();
}

void Leetcode601_700::Soltuion::MagicDictionary::buildDict(vector<string> dictionary)
{
    for(const auto& word : dictionary)
    {
        this->trie->addWord(word);
    }
}

bool Leetcode601_700::Soltuion::MagicDictionary::search(string searchWord)
{
    return this->trie->checkModifiable(searchWord);
}