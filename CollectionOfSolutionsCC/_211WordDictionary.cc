#include "Solution.h"

// 构造函数只需要对智能指针对象进行构造即可
Leetcode201_300::Solution::WordDictionary() { this->root = make_unique<wordNode>(); }

void Leetcode201_300::Solution::addWord(string word)
{
    // 要将某个单词插入到这棵字典树中，我们需要检查的都有什么？
    // 常规的检查肯定是需要的
    // 首先拿到代表根结点的裸指针
    wordNode* cur = this->root.get();
    // 遍历这个单词进行字符添加
    for(const char& c: word)
    {
        if(cur->mapping.find(c) == cur->mapping.end())
        {
            // 如果当前结点的下一层中不存在这个字符，那么我们就需要新建一个结点，并建立映射
            // 注意，这里我们需要用 make_unique 来构造一个新的结点，因为 unique_ptr 不允许拷贝构造
            cur->mapping[c] = make_unique<wordNode>();
        }
        // 深入到下一层
        cur = cur->mapping[c].get();
    }
    cur->isEnd = true;
    // 构造完成，直接返回即可
}

bool Leetcode201_300::Solution::search(string word)
{
    // 注意到，我们上面的添加过程不会针对 '.' 进行任何的特殊处理，在搜索函数中，我们需要特殊注意这样的情况
    // 依然是拿出裸根结点
    return searchNode(this->root.get(), word);
}

// 递归函数，用于确认以某个树结点为根的子树中是否存在当前单词 subWord
bool searchNode(wordNode* subRoot, string subWord)
{
    if(subRoot->memo.find(subWord) != subRoot->memo.end())
    {
        return true;
    }
    wordNode* cur = subRoot;
    int n = subWord.size();
    for(int i = 0; i < n; ++i)
    {
        char c = subWord[i];
        // 如果下一个字符是一个 '.'，那么我们就递归地搜索当前层的每一个子结点指针，直到搜索完成
        if(c == '.')
        {
            // 遍历当前层所有孩子，检查剩下的字符串是否存在于对应子树中
            for(const auto& [key, value]: cur->mapping)
            {
                if(searchNode(value.get(), subWord.substr(i+1)))
                {
                    value->memo.insert(subWord.substr(i+1));
                    return true;
                }
            }
            // 检查完了所有结点，我们还是没有找到对应的子单词，那么久可以返回 false 了
            return false;
        }
        // 否则，是一个正常的字符，我们可以进行常规的判断
        else
        {
            // 如果当前结点中不存在这个字符，那么我们就返回 false
            if(cur->mapping.find(c) == cur->mapping.end())
            {
                return false;
            }
            // 否则，我们继续深入到下一层
            cur = cur->mapping[c].get();
        }
    }
    return cur->isEnd;
}