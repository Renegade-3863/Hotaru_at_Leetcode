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
#include <stack>

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
        ListNode(int _val, ListNode *_next) : val(_val), next(_next) {}

        // 这里我们把成员变量也设置为 public，是为了方便在算法代码中调用和修改对应的成员变量，正常的结构设计原则不提倡这种方式
        int val;        /* 结点值 */
        ListNode *next; /* 下一个结点指针 */
    };

    class Solution
    {
    public:
        /* 1. 两数之和 */
        vector<int> twoSum(vector<int> &nums, int target);
        /* 2. 两数相加 */
        ListNode *addTwoNumbers(ListNode *l1, ListNode *l2);
        /* 3. 无重复字符的最长子串 */
        int lengthOfLongestSubstring(string s);
        /* 4. 寻找两个正序数组的中位数 */
        double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2);
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
        int maxArea(vector<int> &height);
        /* 12. 整数转罗马数字 */
        string intToRoman(int num);
        /* 13. 罗马数字转整数 */
        int romanToInt(string s);
        /* 14. 最长公共前缀 */
        string longestCommonPrefix(vector<string> &strs);
        /* 15. 三数之和 */
        vector<vector<int>> threeSum(vector<int> &nums);
        /* 16. 最接近的三数之和 */
        int threeSumClosest(vector<int> &nums, int target);
        /* 17. 电话号码的字母组合 */
        vector<string> letterCombinations(string digits);
        /* 18. 四数之和 */
        vector<vector<int>> fourSum(vector<int> &nums, int target);
        /* 19. 删除链表的倒数第N个结点 */
        ListNode *removeNthFromEnd(ListNode *head, int n);
        /* 20. 有效的括号 */
        bool isValid(string s);
        /* 21. 合并两个有序链表 */
        ListNode* mergeTwoLists(ListNode* list1, ListNode* list2);
        /* 22. 括号生成 */
        vector<string> generateParenthesis(int n);
        /* 23. 合并 K 个升序链表*/
        ListNode* mergeKLists(vector<ListNode*>& lists);
        /* 24. 两两交换链表中的结点 */
        ListNode* swapPairs(ListNode* head);
        /* 25. K个一组翻转链表 */
        ListNode* reverseKGroup(ListNode* head, int k);
        /* 26. 删除有序数组中的重复项 */
        int removeDuplicates(vector<int>& nums);
        /* 27. 移除元素 */
        int removeElement(vector<int>& nums, int val);
        /* 28. 找出字符串中第一个匹配项的下标 */
        int strStr(string haystack, string needle);
        /* 29. 两数相除 */
        int divide(int dividend, int divisor);
        /* 30. 串联所有单词的子串 */
        vector<int> findSubstring(string s, vector<string>& words);
        /* 31. 下一个排列 */
        void nextPermutation(vector<int>& nums);
        /* 32. 最长有效括号 */
        int longestValidParentheses(string s);
        /* 33. 搜索旋转排序数组 */
        int search(vector<int>& nums, int target);
        /* 34. 在排序数组中查找元素的第一个和最后一个位置 */
        vector<int> searchRange(vector<int>& nums, int target);
        /* 35. 搜索插入位置 */
        int searchInsert(vector<int>& nums, int target);
        /* 36. 有效的数独 */
        bool isValidSudoku(vector<vector<char>>& board);
        /* 37. 解数独 */
        void solveSudoku(vector<vector<char>>& board);
        /* 38. 外观数列 */
        string countAndSay(int n);
        /* 39. 组合总和 */
        vector<vector<int>> combinationSum(vector<int>& candidates, int target);
        /* 40. 组合总和II */
        vector<vector<int>> combinationSum2(vector<int>& candidates, int target);
        /* 41. 缺失的第一个正数 */
        int firstMissingPositive(vector<int>& nums);
        /* 42. 接雨水 */
        int trap(vector<int>& trap);
    };
}

#endif