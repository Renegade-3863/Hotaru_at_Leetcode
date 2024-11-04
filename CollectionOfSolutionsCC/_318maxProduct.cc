#include "Solution.h"

int Leetcode301_400::Solution::maxProduct(vector<int>& words)
{
    // 本题的核心逻辑是如何检查两个字符串之间是否存在重复的字符
    // 一开始只会带哈希表的时间 O(n)，空间 O(n) 的暴力方法，后来看答案，学到了一种很优秀的字符串编码策略
    // 针对本题的每个字符串，我们可以对其进行编码
    // 因为大多数计算机都包含32位整型数的存储结构，所以我们可以使用一个 int 整型来代表一个 word 中可能出现的所有字符(一共26种)
    // 我们只用低26位进行记录即可
    // 先预处理这 words.size() 个整型数
    int n = words.size();
    vector<int> encodes(n, 0);
    for(int i = 0; i < n; ++i)
    {
        int m = words[i].size();
        for(int j = 0; j < m; ++j)
        {
            encodes[i] = encodes[i] | (1 << (words[i][j]-'a'));
        }
    }
    // 结束后，encodes 数组中就保存了这些单词的编码结果
    // 之后我们就可以暴力检查所有数组对了
    // 记录全局的最大值
    int res = 0;
    for(int i = 0; i < n; ++i)
    {
        for(int j = i+1; j < n; ++j)
        {
            // 使用与运算，如果两个字符串没有重复，那么运算结果应该是 0
            if((encodes[i] & encodes[j]) == 0)
            {
                res = max(res, (int)words[i].size() * (int)words[j].size());
            }
        }
    }
    return res;
}