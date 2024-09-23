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

    /* 二叉树/二叉搜索树的结构体定义 */
    struct TreeNode
    {
    public:
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int _val) : val(_val), left(nullptr), right(nullptr) {}
        TreeNode(int _val, TreeNode* _left, TreeNode* _right) : val(_val), left(_left), right(_right) {}

        int val;            /* 结点值 */
        TreeNode* left;     /* 左孩子指针 */
        TreeNode* right;    /* 右孩子指针 */
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
        /* 16. 最接近的三数之和 */  /* Mark */
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
        /* 32. 最长有效括号 */  /* Mark */
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
        /* 41. 缺失的第一个正数 */  /* Mark */
        int firstMissingPositive(vector<int>& nums);
        /* 42. 接雨水 */    /* Mark */
        int trap(vector<int>& trap);
        /* 43. 字符串相乘 */
        string multiply(string num1, string num2);
        /* 44. 通配符匹配 */
        bool isMatch44(string s, string p);
        /* 45. 跳跃游戏 */
        int jump(vector<int>& nums);
        /* 46. 全排列 */
        vector<vector<int>> permute(vector<int>& nums);
        /* 47. 全排列II */  /* Mark */
        vector<vector<int>> permuteUnique(vector<int>& nums);
        /* 48. 旋转图像 */
        void rotate(vector<vector<int>>& matrix);
        /* 49. 字母异位词分组 */
        vector<vector<string>> groupAnagrams(vector<string>& strs);
        /* 50. Pow(x, n) */
        double myPow(double x, int n);
        /* 51. N皇后 */
        vector<vector<string>> solveNQueens(int n);
        /* 52. N皇后 II */
        int totalNQueens(int n);
        /* 53. 最大子数组和 */
        int maxSubArray(vector<int>& nums);
        /* 54. 螺旋矩阵 */
        vector<int> spiralOrder(vector<vector<int>>& matrix);
        /* 55. 跳跃游戏 */
        bool canJump(vector<int>& nums);
        /* 56. 合并区间 */
        vector<vector<int>> merge(vector<vector<int>>& intervals);
        /* 57. 插入区间 */  /* Mark */
        vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval);
        /* 58. 最后一个单词的长度 */
        int lengthOfLastWord(string s);
        /* 59. 螺旋矩阵 II */
        vector<vector<int>> generateMatrix(int n);
        /* 60. 排列序列 */
        string getPermutation(int n, int k);
        /* 61. 旋转链表 */
        ListNode* rotateRight(ListNode* head, int k);
        /* 62. 不同路径 */
        int uniquePaths(int m, int n);
        /* 63. 不同路径 II */
        int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid);
        /* 64. 最小路径和 */
        int minPathSum(vector<vector<int>>& grid);
        /* 65. 有效数字 */  /* Mark */
        bool isNumber(string s);
        /* 66. 加1 */
        vector<int> plusOne(vector<int>& digits);
        /* 67. 二进制求和 */
        string addBinary(string a, string b);
        /* 68. 文本左右对齐 */  /* Mark */
        vector<string> fullJustify(vector<string>& words, int maxWidth);
        /* 69. x 的平方根 */
        int mySqrt(int x);
        /* 70. 爬楼梯 */
        int climbStairs(int n);
        /* 71. 简化路径 */
        string simplifyPath(string path);
        /* 72. 编辑距离 */
        int minDistance(string word1, string word2);
        /* 73. 矩阵置零 */
        void setZeroes(vector<vector<int>>& matrix);
        /* 74. 搜索二维矩阵 */
        bool searchMatrix(vector<vector<int>>& matrix, int target);
        /* 75. 颜色分类 */  /* Mark */
        void sortColors(vector<int>& nums);
        /* 76. 最小覆盖子串 */  /* Mark */
        string minWindow(string s, string t);
        /* 77. 组合 */
        vector<vector<int>> combine(int n, int k);
        /* 78. 子集 */
        vector<vector<int>> subsets(vector<int>& nums);
        /* 79. 单词搜索 */
        bool exist(vector<vector<char>>& board, string word);
        /* 80. 删除有序数组中的重复项 II */
        int removeDuplicates2(vector<int>& nums);
        /* 81. 搜索旋转排序数组II */    /* Mark */
        bool search2(vector<int>& nums, int target);
        /* 82. 删除排序链表中的重复元素 II */
        ListNode* deleteDuplicates(ListNode* head);
        /* 83. 删除排序链表中的重复元素 */  /* Mark */
        ListNode* deleteDuplicatesK(ListNode* head);
        /* 84. 柱状图中最大的矩形 */
        int largestRectangleArea(vector<int>& heights);
        /* 85. 最大矩形 */
        int maximalRectangle(vector<vector<char>>& matrix);
        /* 86. 分隔链表 */
        ListNode* partition(ListNode* head, int x);
        /* 87. 扰乱字符串 */
        bool isScramble(string s1, string s2);
        /* 88. 合并两个有序数组 */
        void merge(vector<int>& nums1, int m, vector<int>& nums2, int n);
        /* 89. 格雷编码 */
        vector<int> grayCode(int n);
        /* 90 子集 II */
        vector<vector<int>> subsetsWithDup(vector<int>& nums);
        /* 91. 解码方法 */
        int numDecodings(string s);
        /* 92. 翻转链表 II */
        ListNode* reverseBetween(ListNode* head, int left, int right);
        /* 93. 复原 IP 地址 */
        vector<string> restoreIpAddresses(string s);
        /* 94. 二叉树的中序遍历 */
        vector<int> inorderTraversal(TreeNode* root);
        /* 95. 不同的二叉搜索树 II */   /* Mark */
        vector<TreeNode*> generateTrees(int n);
        /* 96. 不同的二叉搜索树 */
        int numTrees(int n);
        /* 97. 交错字符串 */    /* Mark */
        bool isInterleave(string s1, string s2, string s3);
        /* 98. 验证二叉搜索树 */
        bool isValidBST(TreeNode* root);
        /* 99. 恢复二叉搜索树 */    /* Mark */  /* Mark */
        void recoverTree(TreeNode* root);
        /* 100. 相同的树 */
        bool isSameTree(TreeNode* p, TreeNode* q);
    };
}

#endif