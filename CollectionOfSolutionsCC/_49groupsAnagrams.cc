#include "Solution.h"

vector<vector<string>> groupAnagrams(vector<string>& strs)
{
    // 要求找出所有字母异位词分组，我们可以使用类似哈希表键值对比较的方式来判断两个单词是不是异位词
    // 使用一个哈希表记录数组中出现过的所有字母搭配不同的字符串对应的 "特征字符串"
    // 我们可以在遍历整个 strs 数组的同时动态更新这个哈希表
    // 哈希表中记录的是具有对应特征字符串的字符串在 res 数组中应该存在的位置下标
    unordered_map<string, int> mapping;
    vector<vector<string>> res;
    // 进行遍历即可
    int n = strs.size();
    // 记录每个遍历到的字符串的特征字符串
    string fea = "";
    for(int i = 0; i < n; ++i)
    {
        // 用数组记录每个字符出现的次数
        vector<int> cnts(26, 0);
        for(int j = 0; j < strs[i].size(); ++j)
        {
            ++cnts[strs[i][j]-'a'];
        }
        // 按字典序遍历 cnts 数组，构造特征字符串
        for(int j = 0; j < 26; ++j)
        {
            if(cnts[j] > 0)
            {
                fea += (char)(cnts[j]+'0');
                fea += (char)(j+'a');
            }
        }
        // 检查特征字符串是否出现过，如果出现过，就加入到对应的 res 下标中
        // 否则就新建一个 res 表项，并更新哈希表
        if(mapping.find(fea) == mapping.end())
        {
            mapping[fea] = res.size();
            res.push_back(vector<string>());
        }
        res[mapping[fea]].emplace_back(strs[i]);
        // 重置两个数组
        fea = "";
    }
    return res;
}