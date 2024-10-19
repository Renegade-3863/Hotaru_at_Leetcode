#include "Solution.h"

int Leetcode201_300::Solution::shortestWordDistance(vector<string>& wordsDict, string word1, string word2)
{
    // 基本思路和 243 题类似，只需要在更新结果的时候增加一条判断条件即可
    int ptr1 = -1, ptr2 = -2;
    int n = wordsDict.size();
    int res = wordsDict.size();
    for(int i = 0; i < n; ++i)
    {
        if(wordsDict[i] == word1)
        {
            if(ptr2 != -2 && ptr2 != i)
            {
                res = min(res, i-ptr2);
            }
            ptr1 = i;
        }
        if(wordsDict[i] == word2)
        {
            if(ptr1 != -1 && ptr1 != i)
            {
                res = min(res, i-ptr1);
            }
            ptr2 = i;
        }
    }
    return res;
}