#include "Solution.h"

string Leetcode501_600::Soltuion::splitLoopedString(vector<string>& strs)
{
    // 说实话，这又是一道理解题意比解题更麻烦的题目。。
    // 总结一下，题目的意思是这样的
    // 我们一开始拼接子字符串的顺序是按照 strs 本身提供的顺序进行的
    // 不过拼接前，我们可以先对 strs 中的每个子字符串尝试进行翻转
    // 在拼接完成后，我们可以任意选择拼接后的结果字符串中的一个字符作为分割点，对拼接结果进行切割
    // 假设拼接串为 str，分割点为 j，被分割的字符串在原来的 strs 数组中是 strs[i]
    // 那么分割后的字符串就是 strs[i][j..strs[i].size()-1]+other+strs[i][0..j-1] (其中 other 代表的是其它所有子字符串的拼接结果)
    // 按照这样的思路把题目理解了之后，本题的基本解法就不难想到了
    // 我们枚举 strs 数组中的每一个字符串 s，把它作为结果 str 中被分割的那个子字符串
    // 之后把除了 s 之外的所有子字符串全部按顺序，以字典序最大的格式进行拼接
    // 最后，我们检查 s 的原字符串和反转字符串，看哪一种可以切割出字典序最大的前后子部分
    // 选出每一种 s 作为分割部分时结果字典序最大的那一种即可
    for(auto& str : strs)
    {
        string revStr = str;
        reverse(revStr.begin(), revStr.end());
        if(revStr > str)
        {
            str = revStr;
        }
    }
    // 把所有字符串都变成字典序更大的格式后，我们就可以遍历 s 了
    // ans 作为最终的结果字符串
    string ans;
    int n = strs.size();
    for(int i = 0; i < n; ++i)
    {
        // other 对应上面提到的其它子字符串的部分，这部分就是 "字典序越大越好"
        string other;
        string rev = strs[i];
        reverse(rev.begin(), rev.end());
        for(int j = i+1; j < n; ++j)
        {
            other.append(strs[j]);
        }
        for(int j = 0; j < i; ++j)
        {
            other.append(strs[j]);
        }
        // 之后是尝试对 strs[i]/rev(strs[i]) 进行分割，找出字典序最大的那一个分割
        // 拼接到 other 的头尾
        int m = strs[i].size();
        for(int j = 0; j < m; ++j)
        {
            string tmp = strs[i].substr(j)+other+strs[i].substr(0, j);
            if(tmp > ans)
            {
                ans = tmp;
            }
        }
        for(int j = 0; j < m; ++j)
        {
            string tmp = rev.substr(j)+other+rev.substr(0, j);
            if(tmp > ans)
            {
                ans = tmp;
            }
        }
    }
    // 检查完成，返回 ans 即可
    return ans;
}