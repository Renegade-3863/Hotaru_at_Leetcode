#include "Solution.h"

string Leetcode701_800::Soltuion::longestWord(vector<string>& words)
{
    // 看描述就知道是字典树了
    // 我们思考这样的问题处理方式：
    // 我们先把每个字符串都存储到一个字典树中
    // 之后遍历 words 中的每一个单词 word
    // 按每一个 word 的每一个字符拼起来的前缀，在字典树中寻找这个前缀是否存在
    // 获取一个字典树实例，用 unique_ptr 的形式存储
    unique_ptr<Node> root = make_unique<Node>();
    for(const auto& word : words)
    {
        // 之后把 words 中的每一个字符都保存到这个 root 树中即可
        insertWord(root, word);
    }
    // 保存完毕后，我们考虑重新遍历一遍每一个单词，检查它的每一个前缀，如果能在 root 中找到，就更新结果
    string res;
    for(const auto& word : words)
    {
        string prefix;
        bool canComp = true;
        for(const auto& c : word)
        {
            prefix += c;
            // 如果找不到，那么我们跳过这个单词即可
            if(!searchWord(root, prefix))
            {
                canComp = false;
                break;
            }
        }
        if(!canComp)
        {
            continue;
        }
        // 如果结束循环时 canComp 是 true，说明这个单词可以作为备选答案
        // 我们更新 res 即可
        if(prefix.size() > res.size())
        {
            res = prefix;
        }
        else if(prefix.size() == res.size())
        {
            // 如果 canComp 的长度和 res 相等，按题意，我们需要更新成字典序更小的那一个
            if(res > prefix)
            {
                res = prefix;
            }
        }
    }
    return res;
}