#include "Solution.h"

bool Leetcode601_700::Soltuion::validPalindrome(string s)
{
    // 简单题，简单做
    // 无非是比直接判断是否是回文串多了一个最多可以反悔一次的条件
    // 我们依然用双指针即可
    int left = 0, right = s.size()-1;
    // 记录反悔次数
    int cnt = 0;
    while(left < right)
    {
        if(s[left] != s[right])
        {
            ++cnt;
            // 我们考虑删除一个字符
            // 我们考虑哪一个删除后，结果可以拿到回文串
            if(s[right-1] == s[left])
            {
                int l = left, r = right-1;
                while(l < r)
                {
                    if(s[l] != s[r])
                    {
                        break;
                    }
                    ++l;
                    --r;
                }
                if(l >= r)
                {
                    return true;
                }
            }
            if(s[left+1] == s[right])
            {
                int l = left+1, r = right;
                while(l < r)
                {
                    if(s[l] != s[r])
                    {
                        break;
                    }
                    ++l;
                    --r;
                }
                if(l >= r)
                {
                    return true;
                }
            }
            return false;
        }
        else
        {
            ++left;
            --right;
        }
    }
    return true;
}