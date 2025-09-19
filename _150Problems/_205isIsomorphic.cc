class Solution
{
public:
    bool isIsomorphic(string s, string t)
    {
        // 简单来说，我们可以使用一个哈希表来记录字符之间的映射关系
        // 题目要求必须是一一映射，我们按照这个要求做就行了
        unordered_map<char, char> mapping;
        // 用一个新的集合来记录所有 "被映射过" 的字符，防止多对一映射
        unordered_set<char> memo;
        int m = s.size();
        // 题目限定了 s 与 t 的长度相同，这样就好处理了
        for(int i = 0; i < m; ++i)
        {
            // 如果当前字符 s[i] - t[i] 在 mapping 中不存在，那么我们就进行映射
            if(mapping.find(s[i]) == mapping.end())
            {
                // 再检查一下：是否出现了多对一映射
                if(memo.find(t[i]) != memo.end())
                {
                    return false;
                }
                mapping[s[i]] = t[i];
                memo.insert(t[i]);
            }
            else
            {
                // 否则，说明已经存在映射关系了，我们检查一下是否满足映射关系
                if(mapping[s[i]] != t[i])
                {
                    // 不满足映射关系，返回 false 即可
                    return false;
                }
                // 否则，满足要求，我们继续检查即可
            }
        }
        return true;
    }
};