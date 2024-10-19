#include "Solution.h"

bool Leetcode201_300::Solution::isStrobogrammatic(string num)
{
    // 只能说是很奇葩的一道题，原先的回文字符串判断的是两个位置对称的字符是否相等，这道题要求判断的是位置对称的字符是否中心对称(图形层面上)
    // 个人能想到的只能是用哈希表来存储这种中心对称关系，来代替原来回文判断的全等符号。。。
    unordered_map<char, char> mapping = {{'0', '0'}, {'1', '1'}, {'8', '8'}, {'9', '6'}, {'6', '9'}};
    // 之后就是和回文数判断中类似的双指针比较
    int left = 0, right = num.size()-1;
    while(left <= right)
    {
        if(mapping.find(num[left]) != mapping.end() && mapping[num[left]] == num[right])
        {
            ++left;
            --right;
        }
        else
        {
            return false;
        }
    }
    return true;
}