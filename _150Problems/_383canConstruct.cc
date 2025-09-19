class Solution
{
public:
    bool canConstruct(string ransomNote, string magazine)
    {
        // 最简单的哈希表问题，我们用一个哈希表记录 magazine 中每个字符出现的次数
        // 之后在遍历 ransomNote 的时候，检查每个字符在哈希表中是否还有剩余即可
        unordered_map<char, int> cnts;
        for(const auto& c : magazine)
        {
            ++cnts[c];
        }
        for(const auto& c : ransomNote)
        {
            if(cnts[c] <= 0)
            {
                return false;
            }
            --cnts[c];
        }
        return true;
    }
};