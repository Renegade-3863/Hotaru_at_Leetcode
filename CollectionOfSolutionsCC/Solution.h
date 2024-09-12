#ifndef _SOLUTION_H_
#define _SOLUTION_H_

/* 统一包含的头文件，涵盖了Leetcode刷过的题目中需要的几乎所有需要的函数库 */
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <vector>
#include <queue>
#include <utility>
#include <map>
#include <set>
#include <algorithm>
#include <climits>

using namespace std;

// 前100道题使用的类定义，使用一个命名空间封装起来
namespace Leetcode1_100 
{
    /* 单链表的结构体定义 */
    struct ListNode
    {
    public:
        ListNode() : val(0), next(nullptr) {}
        ListNode(int _val) : val(_val), next(nullptr) {}

        int val;                    /* 结点值 */
        ListNode* next;             /* 下一个结点指针 */
    };

    
    class Solution 
    {
    public:
        /* 1. 两数之和 */
        vector<int> twoSum(vector<int>& nums, int target);
        /* 2. 两数相加 */
        ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);
        /* 3. 无重复字符的最长子串 */
        int lengthOfLongestSubstring(string s);
        /* 4. 寻找两个正序数组的中位数 */
        double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2);
        /* 5. 最长回文子串 */
        string longestPalindrome(string s);
        /* 6. Z 字形变换 */
        string convert(string s, int numRows);
        /* 7. 整数反转 */
        int reverse(int x);
        /* 8. 字符串转换整数 */
        int myAtoi(string s);
        /* 9. 回文数 */
        bool isPanlindrome(int x);
        /* 10. 正则表达式匹配 */
        bool isMatch(string s, string p);
        /* 11. 盛最多水的容器 */
        int maxArea(vector<int>& height);
        /* 12. 整数转罗马数字 */
        string intToRoman(int num);
        /* 13. 罗马数字转整数 */
        int romanToInt(string s);
        /* 14. 最长公共前缀 */
        string longestCommonPrefix(vector<string>& strs);
        /* 15. 三数之和 */
        vector<vector<int>> threeSum(vector<int>& nums);
        /* 16. 最接近的三数之和 */
        int threeSumClosest(vector<int>& nums, int target);
    };
}

#endif