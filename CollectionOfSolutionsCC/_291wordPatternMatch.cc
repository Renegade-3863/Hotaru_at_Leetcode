#include "Solution.h"

bool Leetcode201_300::Solution::wordPatternMatch(string pattern, string s)
{
    // 最好想到的办法无非就是暴力回溯
    // 定义下面的函数
    // backtrack(idx, idxC)
    // 以及一个存储当前记录的映射关系的哈希表
    // 一个全局的 valid 变量记录当前是否找到了一个可行的映射关系
    // 如果提前找到了，即 valid == true，那么我们就可以提前返回 true
    bool valid = false;
    int m = pattern.size(), n = s.size();
    // 用于检查一对多问题
    unordered_map<char, string> mapping;
    // 用于检查多对一问题
    unordered_map<string, char> reMapping;
    function<void(int, int)> backtrack = [&](int idx, int idxC)
    {
        // 思考：什么时候递归结束？
        // 我们可以固定：当 idx == s.size() 的时候，如果 idxC 也恰好等于了 s.size()，那么说明我们正好找出了一组可行的匹配规则，可以给 valid 修改成 true
        // 或者当 idxC == pattern.size() 的时候，如果 idx 也恰好等于了 pattern.size()，那么同样说明我们恰好找出了一组可行的匹配机制，可以给 valid 修改成 true
        // 否则只返回，不修改 valid
        if(idx == n || idxC == m)
        {
            valid = (idx == n && idxC == m);
            return;
        } 
        // 从当前位置开始，往后找长度递增的字符串和 pattern 当前的字符进行映射
        // 如果我们在某次递归结束后回来，我们找到了合法的匹配规则，我们就可以直接结束了
        for(int i = idx; i < n && !valid; ++i)
        {
            // for(const auto& it: mapping)
            // {
            //     cout << it.first << ": " << it.second << " ";
            // }
            // cout << endl;
            // 取出一个子串
            string cur = s.substr(idx, i-idx+1);
            // 取出当前的字符进行匹配
            char curC = pattern[idxC];
            // 首先检查是否有一对多问题
            if(mapping.find(curC) != mapping.end() && mapping[curC] != cur)
            {
                // 此时出现了一对多问题，不用进一步递归了
                continue;
            }
            // 其次检查是否有多对一问题
            if(reMapping.find(cur) != reMapping.end() && reMapping[cur] != curC)
            {
                // 此时出现了多对一问题，不用进一步递归了
                continue;
            }
            // 其它情况下，这个映射目前是合法的，我们可以进行记录后递归
            bool added = (mapping.find(curC) != mapping.end());
            mapping[curC] = cur;
            reMapping[cur] = curC;
            backtrack(i+1, idxC+1);
            // 回溯
            // 一个小细节，注意可能会出现这种问题
            // 我们当前的 curC 之前就记录过，这里我们把它删掉了，可能会丢失前面的记录导致问题
            // 所以前面要先检查是不是之前就记录过，如果前面记录过，这里不能删
            if(!added)
            {
                mapping.erase(curC);
                reMapping.erase(cur);
            }
        }
    };
    // 调用递归函数即可
    backtrack(0, 0);
    return valid;
}