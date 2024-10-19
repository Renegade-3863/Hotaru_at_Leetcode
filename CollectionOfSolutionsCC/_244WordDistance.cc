#include "Solution.h"

// 解决办法1. 利用和 243 题一样的双指针方案配合哈希表存储过程结果进行效率优化 -> 仍然 TLE，问题在于：我们每次新的查找都需要遍历一整遍原字符串数组，这是不必要并且非常浪费时间的
// 初始化不需要做任何其它事情，只需要把传入的数组保存到类本地即可
#if 0
Leetcode201_300::Solution::WordDistance::WordDistance(vector<string>& wordsDict) 
{
    for(int i = 0; i < wordsDict.size(); ++i)
    {
        this->Dict.push_back(wordsDict[i]);
    }
}

int Leetcode201_300::Solution::WordDistance::shortest(string word1, string word2)
{
    // 记忆化操作：如果前面已经找到过这对单词的距离，我们直接返回结果即可
    stringPair p(word1, word2);
    if(memo.find(p) != 0)
    {
        return memo[p];
    }
    // 这里封装的方法和243题是一样的，都是使用同向双指针
    int res = this->Dict.size();
    int ptr1 = -1, ptr2 = -1, n = this->Dict.size();
    for(int i = 0; i < n; ++i)
    {
        if(this->Dict[i] == word1)
        {
            if(ptr2 != -1)
            {
                res = min(res, i-ptr2);
            }
            ptr1 = i;
        }
        if(this->Dict[i] == word2)
        {
            if(ptr1 != -1)
            {
                res = min(res, i-ptr1);
            }
            ptr2 = i;
        }
    }
    memo[p] = res;
    return res;
}
#endif
// 解决办法2. 根据官解的方案，把新的搜索遍历的范围限制到一个事先预处理好的下标哈希表中，这样可以大幅减少每次新的查找的遍历次数
Leetcode201_300::Solution::WordDistance::WordDistance(vector<string>& wordsDict)
{
    // 只在这里做一轮预处理即可
    int n = wordsDict.size();
    for(int i = 0; i < n; ++i)
    {
        indices[wordsDict[i]].push_back(i);
    }
}

Leetcode201_300::Solution::WordDistance::shortest(string word1, string word2)
{
    // 哈希记忆检查
    if(memo.find(stringPair(word1, word2)) != memo.end())
    {
        return memo[stringPair(word1, word2)];
    }
    // 查找过程，我们可以利用上面预处理出来的下标哈希表，省去不必要的遍历
    // 利用引用，防止多余的数组复制
    vector<int>& indices1 = indices[word1];
    vector<int>& indices2 = indices[word2];
    // 这里仍然利用双指针进行遍历
    int ptr1 = 0, ptr2 = 0;
    int m = indices1.size(), n = indices2.size();
    int res = INT_MAX;
    while(ptr1 < m && ptr2 < n)
    {
        // 声明一下两个指针的含义：
        // ptr1 指向的值是 indices1 中最靠左的还未检查完所有可能影响 res 结果的那个 word1 的下标
        // ptr2 指向的值是 indices2 中最靠左的还未检查完所有可能影响 res 结果的那个 word2 的下标
        // 根据两个指针指向的下标的大小关系讨论如何更新两个指针：
        // 1. indices1[ptr1] < indices2[ptr2]
        // 此时说明 ptr1 指向的这个 word1 的下标是小于当前 ptr2 指向的这个 word2 的下标的
        // 由于此时 ptr2 指向的这个 word2 左侧不存在未更新完全的 word2，我们可以明确此时 ptr1 指向的这个 word1 不会再对结果产生更多影响
        // 可以简单地右移 ptr1
        // 2. indices1[ptr1] > indices2[ptr2]
        // 类似1的推导，此时我们可以直接移动 ptr2
        // 先更新最终结果
        res = min(res, abs(indices1[ptr1]-indices2[ptr2]));
        if(indices1[ptr1] < indices2[ptr2])
        {
            ++ptr1;
        }
        else
        {
            ++ptr2;
        }
    }
    memo[stringPair(word1, word2)] = res;
    return res;
}