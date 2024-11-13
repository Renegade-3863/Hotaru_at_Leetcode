#include "Solution.h"

string Leetcode301_400::Solution::reverseVowels(string s)
{
    // 和上一题没有任何本质上的区别，我们无非就是在移动双指针的时候跳过那些不是元音字母的位置
    unordered_set<char> board = {'A', 'a', 'E', 'e', 'I', 'i', 'O', 'o', 'U', 'u'};
    // 依然用双指针进行遍历
    int left = 0, right = s.size()-1;
    while(left < right)
    {
        if(board.find(s[left]) == board.end())
        {
            ++left;
        }
        else if(board.find(s[right]) == board.end())
        {
            --right;
        }
        else
        {
            // 位运算进行交换
            s[left] ^= s[right];
            s[right] ^= s[left];
            s[left] ^= s[right];
            ++left; --right;
        }
    }
    return s;
}