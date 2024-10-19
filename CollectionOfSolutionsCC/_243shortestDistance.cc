#include "Solution.h"

int Leetcode201_300::Solution::shortestDistance(vector<string>& wordsDict, string word1, string word2)
{
    // 学到了，又是一道类似龟兔赛跑的问题，我们可以按照类似追逐比赛的方法来求解两个单词之间的最短距离
    // 一开始想用反向双指针的方案来求解，发现当两个指针分别指向 word1 和 word2 时，无法明确知道该先移动哪一侧的指针
    // 官解给出了一种同向双指针的方案
    // 基本思路如下：
    // 规定两个指针，分别指向 word1 和 word2
    // 每次找到一个 word1，我们令 word2 此时指向前面已经探查过的区域中最靠右的那个 word2，此时更新得到的就是当前 word1 和前面所有 word2 中距离最近的值
    // 每次找到一个 word2，我们同样令 word2 此时指向前面已经探查过的区域中最靠右的那个 word1，此时更新得到的就是当前 word2 和前面所有 word1 中距离最近的值
    int ptr1 = -1, ptr2 = -1;
    // 进行遍历
    int n = wordsDict.size();
    int res = wordsDict.size();
    for(int i = 0; i < n; ++i)
    {
        if(wordsDict[i] == word1)
        {
            if(ptr2 != -1)
            {
                res = min(res, i-ptr2);
            }
            ptr1 = i;
        }
        if(wordsDict[i] == word2)
        {
            if(ptr1 != -1)
            {
                res = min(res, i-ptr1);
            }
            ptr2 = i;
        }
    }
    return res;
}