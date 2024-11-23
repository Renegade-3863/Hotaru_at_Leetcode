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
#include <unique_ptr>
#include <priority_queue>
#include <deque>

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
        /* 560. 和为 K 的子数组 */  /* Mark */  /* Mark */
        int subarraySum(vector<int>& nums, int k);
    };
}

// 101-200题使用的类定义，使用一个命名空间封装起来
namespace Leetcode101_200
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

    struct Node 
    {
    public:
        int val;
        Node* left;
        Node* right;
        Node* next;

        Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}
        Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}
        Node(int _val, Node* _left, Node* _right, Node* _next) : val(_val), left(_left), right(_right), next(_next) {}
    };

    class Node
    {
    public:
        int val;
        Node* next;
        Node* random;

        Node(int _val) {
            val = _val;
            next = NULL;
            random = NULL;
        }
    };

    class Node
    {
    public:
        int val;
        vector<Node*> neighbors;
        Node() {
            val = 0;
            neighbors = vector<Node*>();
        }
        Node(int _val) {
            val = _val;
            neighbors = vector<Node*>();
        }
        Node(int _val, vector<Node*> _neighbors) {
            val = _val;
            neighbors = _neighbors;
        }
    };

    class Solution
    {
    public:
        /* 101. 对称二叉树 */   /* Mark */  /* Mark */
        bool isSymmetric(TreeNode* root);
        /* 102. 二叉树的层序遍历 */
        vector<vector<int>> levelOrder(TreeNode* root);
        /* 103. 二叉树的锯齿形层序遍历 */   /* Mark */  /* Mark */
        vector<vector<int>> zigzagLevelOrder(TreeNode* root);
        /* 104. 二叉树的最大深度 */
        int maxDepth(TreeNode* root);
        /* 105. 从前序与中序遍历序列构造二叉树 */
        TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder);
        /* 106. 从中序与后序遍历序列构造二叉树 */
        TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder);
        /* 107. 二叉树的层序遍历 II */
        vector<vector<int>> levelOrderBottom(TreeNode* root);
        /* 108. 将有序数组转换为二叉搜索树 */
        TreeNode* sortedArrayToBST(vector<int>& nums);
        /* 109. 有序链表转换二叉搜索树 */
        TreeNode* Divide(ListNode* head);
        /* 110. 平衡二叉树 */
        bool isBalanced(TreeNode* root);
        /* 111. 二叉树的最小深度 */
        int minDepth(TreeNode* root);
        /* 112. 路径总和 */
        bool hasPathSum(TreeNode* root, int targetSum);
        /* 113. 路径总和 II */  /* Mark */
        vector<vector<int>> pathSum(TreeNode* root, int targetSum);
        /* 437. 路径总和 III */ /* Mark */  /* Mark */
        int pathSum3(TreeNode* root, int targetSum);
        /* 114. 二叉树展开为链表 */
        void flatten(TreeNode* root);
        /* 115. 不同的子序列 */
        int numDistinct(string s, string t);
        /* 116. 填充每个结点的下一个右侧结点指针 */
        Node* connect(Node* root);
        /* 117. 填充每个结点的下一个右侧结点指针 II */      /* Mark */  /* Mark */
        Node* connect2(Node* root);
        /* 118. 杨辉三角 */
        vector<vector<int>> generate(int numRows);
        /* 119. 杨辉三角 II */  /* Mark */  /* Mark */
        vector<int> getRow(int rowIndex);
        /* 120. 三角形最小路径和 */
        int minimumTotal(vector<vector<int>>& triangle);
        /* 121. 买卖股票的最佳时机 */
        int maxProfit(vector<int>& prices);
        /* 188. 买卖股票的最佳时机 IV */
        int maxProfit4(int k, vector<int>* prices);
        /* 123. 买卖股票的最佳时机 III */
        int maxProfit3(vector<int>& prices);
        /* 122. 买卖股票的最佳时机 II */
        int maxProfit2(vector<int>& prices);
        /* 124. 二叉树中的最大路径和 */
        int maxPathSum(TreeNode* root);
        /* 125. 验证回文串 */
        bool isPanlindrome(string s);
        /* 126. 单词接龙 II */      /* Mark */      /* Mark */
        vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList);
        /* 127. 单词接龙 */         /* Mark */      /* Mark */
        int ladderLength(string beginWord, string endWord, vector<string>& wordList);
        /* 128. 最长连续序列 */     /* Mark */      /* Mark */
        int longestConsecutive(vector<int>& nums);
        /* 129. 求根结点到叶结点数字之和 */
        int sumNumbers(TreeNode* root);
        /* 130. 被围绕的区域 */
        void solve(vector<vector<char>>& board);
        /* 131. 分割回文串 */
        vector<vector<string>> partition(string s);
        /* 132. 分割回文串 II */    /* Mark */      /* Mark */
        int minCut(string s);
        /* 133. 克隆图 */
        Node* cloneGraph(Node* node);
        /* 134. 加油站 */
        int canCompleteCircuit(vector<int>& gas, vector<int>* cost);
        /* 135. 分发糖果 */
        int candy(vector<int>& ratings);
        /* 136. 只出现一次的数字 */
        int singleNumber(vector<int>& nums);
        /* 137. 只出现一次的数字 II */  /* Mark */      /* Mark */
        int singleNumber2(vector<int>& nums);
        /* 138. 随机链表的复制 */
        Node* copyRandomList(Node* head);
        /* 139. 单词拆分 */
        bool wordBreak(string s, vector<string>& wordDict);
        /* 140. 单词拆分 II */
        vector<string> wordBreak2(string s, vector<string>& wordDict);
        /* 141. 环形链表 */
        bool hasCycle(ListNode* head);
        /* 142. 环形链表 II */
        ListNode* detectCycle(ListNode* head);
        /* 143. 重排链表 */
        void reorderList(ListNode* head);
        /* 144. 二叉树的前序遍历 */
        vector<int> preorderTraversal(TreeNode* root);
        /* 145. 二叉树的后序遍历 */
        vector<int> postorderTraversal(TreeNode* root);
        /* 146. LRU 缓存 */
        // 本题要求我们实现一个高效的处理一串依据数据访问次序进行存储的数据结构
        // 要求访问次序最近的放到数据存储结构的最前端
        // 这显然是一种类似链表的结构
        // 而本题由于我们还需要调动链表中的结点，因而我们考虑使用双向链表
        struct duLinkedNode {
        public:
            duLinkedNode(int _val, int _key) : val(_val), key(_key), prev(nullptr), next(nullptr) {}
            int key;
            int val;
            duLinkedNode* prev;
            duLinkedNode* next;
        };
        class LRUCache {
        public:
            LRUCache(int _capacity);
            ~LRUCache();
            int get(int _key);
            void put(int _key, int _value);

            // 我们存储一个双向链表的首元和尾结点
            // 以及这个链表可以存储的结点最大数量 capacity
            // 同时，我们还需要一种高效地根据值查找链表结点的数据结构，这可以通过哈希表来实现
            int capacity;
            // size 用于记录链表中的总结点个数，用于判断体积是否超出了容量
            int size;
            duLinkedNode* head;
            duLinkedNode* tail;
            unordered_map<int, duLinkedNode*> mapping;
        };
        /* 147. 对链表进行插入排序 */
        ListNode* insertionSortList(ListNode* head);
        /* 148. 排序链表 */     /* Mark */  /* Mark */
        ListNode* sortList(ListNode* head);
        /* 149. 直线上最多的点数 */
        int maxPoints(vector<vector<int>>& points);
        /* 150. 逆波兰表达式求值 */     /* Mark */
        int evalRPN(vector<string>& tokens);
        /* 151. 反转字符串中的单词 */   /* Mark */  /* Mark */
        string reverseWords(string s);
        /* 152. 乘积最大子数组 */
        int maxProduct(vector<int>& nums);
        /* 153. 寻找旋转排序数组中的最小值 */
        int findMin(vector<int>& nums);
        /* 154. 寻找旋转排序数组中的最小值 II */
        int findMin2(vector<int>& nums);
        /* 155. 最小栈 */
        /*
            又是一道设计类题目，本题的要求是实现一个数据结构，支持常规栈道入栈、出栈、取栈顶元素操作
            并且可以在常数时间内拿到最小元素的栈
            我们可以通过两个栈分别实现要求的两种功能，一个栈用于存储实际的数据，另一个栈用做单调栈，存储一个单调递减序列即可
        */
        class MinStack {
        public:
            MinStack();
            ~MinStack();
            void push(int val);
            void pop();
            int top();
            int getMin();

            stack<int> original;
            stack<int> mono;
        };
        /* 159. 至多包含两个不同字符的最长子串 */
        int lengthOfLongestSubstringTwoDistinct(string s);
        /* 160. 相交链表 */
        ListNode* getIntersectionNode(ListNode* headA, ListNode* headB);
        /* 161. 相隔为1的编辑距离 */
        bool isOneEditDistance(string s, string t);
        /* 162. 寻找峰值 */
        int findPeakElement(vector<int>& nums);
        /* 1901. 寻找峰值 II */     /* Mark */  /* Mark */
        vector<int> findPeakGrid(vector<vector<int>>& mat);
        /* 163. 缺失的区间 */
        vector<vector<int>> findMissingRanges(vector<int>& nums, int lower, int upper);
        /* 164. 最大间距 */         /* Mark */  /* Mark */
        int maximumGap(vector<int>& nums);
        /* 165. 比较版本号 */
        int compareVersion(string version1, string version2);
        /* 166. 分数到小数 */       /* Mark */  /* Mark */
        string fractionToDecimal(int numerator, int denominator);
        /* 167. 两数之和 II - 输入有序数组 */   /* Mark */  /* Mark */
        vector<int> twoSum2(vector<int>& numbers, int target);
        /* 168. Excel 表列名称 */       /* Mark */  /* Mark */
        string convertToTitle(int columnNumber);
        /* 169. 多数元素 */
        int majorityElement(vector<int>& nums);
        /*
            170. 两数之和 III - 数据结构设计
        */
        class TwoSum {
        public:
            TwoSum();
            void add(int number);
            bool find(int value);
            // 本题要求我们实现一个高效查找已经添加的数据中是否存在和为 target 的两数数对的结构
            // 可以使用类似记忆化的方式提高查找效率
            unordered_set<int> memo;
            // 维护一个有序数组合用于记录某个数据的存在，用于记忆化哈希表中不存在对应记忆的时候执行实际的检查
            vector<int> values;
        };
        /* 171. Excel 表列序号 */
        int titleToNumber(string columnTitle);
        /* 172. 阶乘后的零 */       /* Mark */  /* Mark */
        int trailingZeroes(int n);
        /* 173. 二叉搜索树迭代器 */
        class BSTIterator {
            BSTIterator(TreeNode* root);
            int next();
            bool hasNext();
            // 本题要求我们实现一个能够对
            // 因而我们只需要使用类似迭代的方式存中序遍历所需要的所有结点信息
            // 根据我们对中序遍历迭代方式的写法认知，这可以通过一个栈和一个结点指针实现
            TreeNode* cur;
            stack<TreeNode*> stk;
        };
        /* 174. 地下城游戏 */
        int calculateMinimumHP(vector<vector<int>>& dungeon);
        /* 179. 最大数 */
        string largestNumber(vector<int>& nums);
        /* 187. 重复的 DNA 序列 */
        vector<string> findRepeatedDnaSequences(string s);
        /* 189. 轮转数组 */
        void rotate(vector<int>& nums, int k);
        /* 190. 颠倒二进制位 */     /* Mark */  /* Mark */
        uint32_t reverseBits(uint32_t n);
        /* 191. 位1的个数 */        /* Mark */  /* Mark */
        int hammingWeight(int n);
        /* 198. 打家劫舍 */
        int rob(vector<int>& nums);
        /* 199. 二叉树的右视图 */
        vector<int> rightSideView(TreeNode* root);
        /* 200. 岛屿数量 */
        int numIslands(vector<vector<char>>& grid);
    };  
}

namespace Leetcode201_300
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

    class Solution {
    public:
        /* 201. 数字范围按位与 */
        int rangeBitwiseAnd(int left, int right);
        /* 202. 快乐数 */   /* Mark */
        bool isHappy(int n);
        /* 203. 移除链表元素 */
        ListNode* removeElements(ListNode* head, int val);
        /* 204. 计数质数 */     /* Mark */  /* Mark */
        int countPrimes(int n);
        /* 205. 同构字符串 */
        bool isIsomorphic(string s, string t);
        /* 206. 反转链表 */     /* Mark */
        ListNode* reverseList(ListNode* head);
        /* 207. 课程表 */       /* Mark */  /* Mark */  /* Mark */
        bool canFinish(int numCourses, vector<vector<int>>& prerequisites);
        /* 208. 实现 Trie (前缀树) */
        class Trie {
        public:
            Trie();
            ~Trie();
            void insert(string word);
            bool search(const string& word);
            bool startsWith(const string& prefix);
            
            // 一棵前缀树一定有且仅有一个根结点(当然这里说的知识最基本的前缀树，要是想处理变形的 Trie 树，那当我没说)
            // TrieNode* root;
            // 这里我们做一下优化，由于树这种东西本身定义上就涉及到了递归，因而垃圾处理一定不会很简单，所以我们利用智能指针对裸指针进行一下包装，提高程序的安全性
            unique_ptr<TrieNode> root;
        };
        struct TrieNode {
        public:
            TrieNode() : isEnd(false) {}
            ~TrieNode();

            // 这个变量用于判断单词，而不是前缀，如果某个单词在 search 函数中循环结束后遇到了一个 isEnd == true，那么就说明我们找到了这个单词，否则，它只能是某个已经添加过单词的前缀
            bool isEnd;
            // 对于一棵字典树，每一个结点都有一个(键域为所有可能的字符，值域为对应的下一个结点的指针)存储它已有数据的哈希表，这个哈希表结构是不同层的树结点之间进行链接的桥梁
            // unordered_map<char, TrieNode*> mapping;
            // 同样做一下智能指针的包装
            unordered_map<char, unique_ptr<TrieNode>> mapping;
        };
        /* 209. 长度最小的子数组 */
        int minSubArrayLen(int target, vector<int>& nums);
        /* 210. 课程表 II */
        vector<int> findOrder2(int numCourses, vector<vector<int>>& prerequisites);
        /* 211. 添加与搜索单词 - 数据结构设计 */
        /*
            本题基于 208 字典树的题目做了一点点修改，添加了一个通配符 '.'，不过总体上难度没什么变化，只需要一点细微的条件判断即可
            主体部分还是一棵传统的字典树
        */
        // 字典树结点的定义和之前是一样的
        struct wordNode {
        public:
            wordNode() : isEnd(false) {}
            ~wordNode();
            bool isEnd;
            unordered_map<char, unique_ptr<wordNode>> mapping;
            // 考虑到本题的特殊性，我们可以添加一个额外的记忆化哈希表，记录一下已经递归搜索过的结果，避免重复搜索
            unordered_set<string> memo;
        };
        // 到具体实现中再加细节处理 '.' 即可
        class WordDictionary {
        public: 
            WordDictionary();
            // 使用默认的析构函数即可
            ~WordDictionary() = default;
            void addWord(string word);
            bool search(string word);
        
            // 字典树对象需要拥有一个根结点
            unique_ptr<wordNode> root;
        };
        /* 212. 单词搜索 II */  /* Mark */  /* Mark */  /* Mark */
        vector<string> findWords(vector<vector<char>>& board, vector<string>& words);
        /* 213. 打家劫舍 II */
        int rob(vector<int>& nums);
        /* 214. 最短回文串 */   /* Mark */  /* Mark */
        string shortestPalindrome(string s);
        /* 215. 数组中的第 K 个最大元素 */      /* Mark */  /* Mark */  /* Mark */
        int findKthLargest(vector<int>& nums, int k);
        /* 216. 组合总和 III */
        vector<vector<int>> combinationSum3(int k, int n);
        /* 217. 存在重复元素 */
        bool containDuplicate(vector<int>& nums);
        /* 218. 天际线问题 */   /* Mark */  /* Mark */  /* Mark */
        /* 具体关于线段树的内容详见同一库中的 Markdown 文档 */
        const int N = 20010;
        struct Node 
        {
            int left;
            int right;
            int height; // 本题需要维护的属性值就是高度的最大值
        }tree[4*N];
        void build(int p, int l, int r)
        {
            // 先构建根结点
            // 假设我们用数组的形式来存储线段树(也是二叉树)的各个结点
            // 这个数组的名字是 tree
            tree[p].left = l; tree[p].right = r;
            // 递归构造的结束条件：当前区间只有一个结点
            // 此时已经无需进一步深入了，之间返回即可
            if(l == r)
            {
                return;
            }
            // 否则，需要进一步深入递归构造左右孩子结点
            int mid = ((r-l)>>1)+l;
            // 2*p 代表左孩子
            build(2*p, l, mid);
            // 2*p+1 代表右孩子
            build(2*p+1, mid+1, r);
        }

        void lazyUpdate(int p)
        {
            // 关于层间的更新，我们只需要从当前结点通知它的两个子结点：上头有检查的了，我把我知道的信息告诉你，你被查的时候告诉上头的人就行
            // 如果当前结点中存在数据(本身也是懒数据)
            // 可以向孩子结点扩散的，那么就进行扩散
            if(tree[p].height != 0)
            {
                tree[2*p].height = max(tree[p].height, tree[2*p].height);
                tree[2*p+1].height = max(tree[p].height, tree[2*p+1].height);
            }
        }

        // 要更新的是 [l, r] 上所有的下标，要更新的可能值是 h
        // 注意，这个区间是受到结点 p 的限制
        void update(int p, int l, int r, int h)
        {
            // 情况1. 要更新的区间囊括了当前结点整体，我们便不再需要分裂，进一步更新这个结点的分支结点
            if(tree[p].left >= l && tree[p].right <= r)
            {
                // 那么我们可以把这个更新完全 "委托" 给这个被完全包住的结点，不需要再继续深入修改
                tree[p].height = max(tree[p].height, h);
                return;
            }
            // 否则，我们会需要继续递归地更新当前结点被 [l, r] 覆盖到了的那部分
            // 注意，在更新之前，我们需要先进行一次 "懒更新"，也就是上面说到的，"需要被用到" 的状态
            // 因为这个时候可能会有这样的情况：
            // 我们之前对这个区间进行过 "懒更新"，因而此时它的两个孩子还没有实际获知这个 "懒更新" 的内容，因而我们需要先进行更新后再分别深入修改
            lazyUpdate(p);
            // 此时两个孩子已经知道了之前懒更新的内容，我们可以继续分开深入进行更新了
            // 还是先切分当前结点的区间
            int mid = ((tree[p].right-tree[p].left)>>1)+tree[p].left;
            // 关注两半区间是否都需要进行进一步的修改
            if(l <= mid)
            {
                update(2*p, l, r, h);
            }
            if(r >= mid+1)
            {
                update(2*p+1, l, r, h);
            }
        }

        int query(int p, int x)
        {
            // 类似的递归结束条件，如果当前结点维护的区间长度为1，那么我们就可以直接返回这个单一结点的值(注意，可能需要对结果的合法性进行检查，因为我们可能并没有在当前线段树中存储这个 x 下标，所以额外进行一下检查也是可以的)
            if(tree[p].left == tree[p].right)
            {
                return tree[p].height;
            }
            // 否则，我们尝试对这个区间的两个子区间进行搜索
            // 并且，在深入递归搜索之前，我们依然需要把可能的 "懒更新" 信息先传递给两个孩子
            lazyUpdate(p);
            // 这里和二叉搜索树的二分操作的基本模式是一样的
            int mid = ((tree[p].right-tree[p].left)>>1)+tree[p].left;
            // x 在 mid 的左侧，我们需要递归检查左孩子
            if(mid >= x)
            {
                return query(2*p, x);
            }
            // 否则，x 在 mid 的右侧，我们需要递归检查右孩子
            return query(2*p+1, x);
        }
        /* 219. 存在重复元素 II */
        bool containsNearbyDuplicate(vector<int>& nums, int k);
        /* 220. 存在重复元素 III */     /* Mark */  /* Mark */  /* Mark */
        bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff);
        /* 221. 最大正方形 */
        int maximalSquare(vector<vector<char>>& matrix);
        /* 222. 完全二叉树的结点个数 */     /* Mark */  /* Mark */  /* Mark */
        int countNodes(TreeNode* root);
        /* 223. 矩形面积 */     /* Mark */  /* Mark */  /* Mark */
        int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2);
        /* 224. 基本计算器 */   /* Mark */
        int calculate(string s);
        /* 225. 用队列实现栈 */
        class MyStack {
        public:
            MyStack();
            void push(int x);
            int pop();
            int top();
            bool empty();

            queue<int> q;
        };
        /* 227. 基本计算器 II */
        int calculate2(string s);
        /* 228. 汇总区间 */
        vector<string> summaryRanges(vector<int>& nums);
        /* 229. 多数元素 II */  /* Mark */  /* Mark */
        vector<int> majorityElement(vector<int>& nums);
        /* 230. 二叉搜索树中第 K 小的元素 */
        int kthSmallest(TreeNode* root, int k);
        /* 231. 2的幂 */
        bool isPowerOfTwo(int n);
        /* 232. 用栈实现队列 */ /* Mark */  /* Mark */
        class MyQueue {
        public:
            MyQueue();
            void push(int x);
            int pop();
            int peek();
            bool empty();
            
            stack<int> stk1;
            stack<int> stk2;
        };
        /* 233. 数字1的个数 */
        int countDigitOne(int n);
        /* 234. 回文链表 */
        bool isPalindrome(ListNode* head);
        /* 235. 二叉搜索树的最近公共祖先 */
        TreeNode* lowestCommonAncestorBST(TreeNode* root, TreeNode* p, TreeNode* q);
        /* 236. 二叉树的最近公共祖先 */ /* Mark */  /* Mark */
        TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q);
        /* 237. 删除链表中的结点 */
        void deleteNode(ListNode* node);
        /* 238. 除自身以外数组的乘积 */
        vector<int> productExceptionSelf(vector<int>& nums);
        /* 239. 滑动窗口最大值 */   /* Mark */  /* Mark */
        vector<int> maxSlidingWindow(vector<int>& nums, int k);
        /* 240. 搜索二维矩阵 */
        bool searchMatrix(vector<vector<int>>& matrix, int target);
        /* 241. 为运算表达式设计优先级 */   /* Mark */  /* Mark */
        vector<int> diffWaysToCompute(string expression);
        /* 242. 有效的字母异位词 */
        bool isAnagram(string s, string t);
        /* 243. 最短单词距离 */
        int shortestDistance(vector<string>& wordsDict, string word1, string word2);
        /* 244. 最短单词距离 II */  /* Mark */  /* Mark */
        // 本题的一个较为有用的点是学习一遍如何对 C++ 自带的 STL unordered_map 进行自定义键的使用
        // 重点在于对哈希函数和全等运算符的重载，这两个函数是 unordered_map 其它各个成员函数 (find, [], at 等) 调用过的基础函数，必须把这两个函数进行重载
        // 或者也可以使用仿函数对全等函数进行封装，再传给 unordered_map，效果是一样的
        // 最关键的一点：重载这些函数/运算符的时候，必须给函数限定 const，保证不能在函数体内部修改结构体的成员变量，不然编译器不会接受你的重载！！！
        struct stringPair {
            stringPair(string _s1, string _s2) : s1(_s1), s2(_s2) {}
            // 第二种重载方法，在自定义数据结构内部重载全等符号定义
            bool operator==(const stringPair& p) const
            {
                return s1 == p.s1 && s2 == p.s2;
            }
            string s1;
            string s2;
        };
        // 使用异或重载字符串数对的哈希函数
        struct hashFunc {
            size_t operator() (const stringPair& p) const {
            return hash<string>()(p.s1) ^ hash<string>()(p.s2);
            }
        };
        // 第一种重载方法，使用仿函数进行包装
        struct EqualFunc {
            bool operator() (const stringPair& p1, const stringPair& p2) const
            {
                return p1.s1 == p2.s1 && p1.s2 == p2.s2;
            }
        };
        class WordDistance {
        public:
            WordDistance(vector<string>& wordsDict);
            int shortest(string word1, string word2);
            vector<string> Dict;
            // 为了提高后序相同检索的速率，我们可以在本类中保存一个哈希表结构存储检查过的记录，同时这需要重载一次哈希表的哈希函数
            // 这可以利用仿函数实现
            unordered_map<stringPair, int, hashFunc, EqualFunc> memo;
            // 这个结构是为解法2服务的，关注解法1的时候不需要在意这个哈希表
            unordered_map<string, vector<int>> indices;
        };
        /* 245. 最短单词距离 III */
        int shortestWordDistance(vector<string>& wordsDict, string word1, string word2);
        /* 246. 中心对称数 */
        bool isStrobogrammatic(string num);
        /* 247. 中心对称数 II */
        vector<string> findStrobogrammatic(int n);
        /* 248. 中心对称数 III */   /* Mark */  /* Mark */  /* Mark */
        int strobogrammaticInRange(string low, string high);
        /* 249. 移位字符串分组 */
        vector<vector<string>> groupStrings(vector<string>& strings);
        /* 250. 统计同值子树 */
        int countUnivalSubtrees(TreeNode* root);
        /* 251. 展开二维向量 */
        class Vector2D {
        public:
            Vector2D(vector<vector<int>>& vec);
            int next();
            bool hasNext();
        };
        /* 252. 会议室 */
        bool canAttendMeetings(vector<vector<int>>& intervals);
        /* 253. 会议室 II */    /* Mark */  /* Mark */
        int minMeetingRooms(vector<vector<int>>& intervals);
        /* 254. 因子的组合 */   /* Mark */  /* Mark */
        vector<vector<int>> getFactors(int n);
        /* 255. 验证二叉搜索树的前序遍历序列 */
        bool verifyPreorder(vector<int>& preorder);
        /* 256. 粉刷房子 */
        int minCost(vector<vector<int>>& costs);
        /* 257. 二叉树的所有路径 */
        vector<string> binaryTreePaths(TreeNode* root);
        /* 258. 各位相加 */
        int addDigits(int num);
        /* 259. 较小的三数之和 */
        int threeSumSmaller(vector<int>& nums, int target);
        /* 260. 只出现一次的数字 III */
        vector<int> singleNumber3(vector<int>& nums);
        /* 261. 以图判树 */ /* Mark */  /* Mark */
        bool validTree(int n, vector<vector<int>>& edges);
        /* 263. 丑数 */
        bool isUgly(int n);
        /* 264. 丑数 II */
        int nthUglyNumber(int n);
        /* 265. 粉刷房子 II */
        int minCostII(vector<vector<int>>& costs);
        /* 266. 回文排列 */
        bool canPermuteParlindrome(string s);
        /* 267. 回文排列 II */
        vector<string> generatePalindromes(string s);
        /* 268. 丢失的数字 */
        int missingNumber(vector<int>& nums);
        /* 269. 火星词典 */ /* Mark */
        string alienOrder(vector<string>& words);
        /* 270. 最接近的二叉搜索树值 */
        int closestValue(TreeNode* root, double target);
        /* 271. 字符串的编码与解码 */
        class Codec {
        public:
            // Encodes a list of strings to a single string.
            string encode(vector<string>& strs);
            // Decodes a single string to a list of strings
            vector<string> decode(string s);
        };
        /* 272. 最接近的二叉搜索树值 II */
        vector<int> closestKValues(TreeNode* root, double target, int k);
        /* 273. 整数转换英文表示 */
        string numberToWords(int num);
        /* 274. H 指数 */   /* Mark */  /* Mark */
        int hIndex(vector<int>& citations);
        /* 275. H 指数 II */
        int hIndex2(vector<int>& citations);
        /* 276. 栅栏涂色 */
        int numWays(int n, int k);
        /* 277. 搜寻名人 */ /* Mark */  /* Mark */
        int findCelebrity(int n);
        /* 278. 第一个错误的版本 */
        int firstBadVersion(int n);
        /* 279. 完全平方数 */   /* Mark */  /* Mark */  /* Mark */  /* Mark */
        int numSquares(int n);
        /* 280. 摆动排序 */
        void wiggleSort(vector<int>& nums);
        /* 281. 锯齿迭代器 */
        class zigzagIterator {
        public:
            zigzagIterator(vector<int>& v1, vector<int>& v2);
            int next();
            bool hasNext();
            vector<vector<int>> msg;
            int cnt;
            int total;
        };
        /* 282. 给表达式添加运算符 */   /* Mark */  /* Mark */
        vector<string> addOperators(string num, int target);
        /* 283. 移动零 */
        void moveZeroes(vector<int>& nums);
        /* 284. 窥视迭代器 */
        class PeekingIterator : public Iterator 
        {
        public: 
            PeekingIterator(const vector<int>& nums);
            int peek();
            int next();
            bool hasNext() const;
        };
        /* 285. 二叉搜索树的中序后继 */
        TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p);
        /* 286. 墙与门 */
        void wallsAndGates(vector<vector<int>>& rooms);
        /* 287. 寻找重复数 */   /* Mark */  /* Mark */  /* Mark */  /* Mark */
        int findDuplicate(vector<int>& nums);
        /* 288. 单词的唯一缩写 */
        class ValidWordAbbr 
        {
        public:
            ValidWordAbbr(vector<string>& dictionary);
            bool isUnique(string word);
            // 比较简单的实现方法是：
            // 使用一个哈希表套哈希集合的结构，保存每个缩写在当前字典中已经存储过的所有不同单词
            unordered_map<string, unordered_set<string>> memo;
        };
        /* 289. 生命游戏 */
        void gameOfLife(vector<vector<int>>& board);
        /* 290. 单词规律 */
        bool wordPattern(string pattern, string s);
        /* 291. 单词规律 II */  /* Mark */  /* Mark */
        bool wordPatternMatch(string pattern, string s);
        /* 292. Nim游戏 */  /* Mark */  /* Mark */
        bool canWinNim(int n);
        /* 293. 翻转游戏 */
        vector<string> generatePossibleNextMoves(string currentState);
        /* 294. 翻转游戏 II */  /* Mark */  /* Mark */  // 注意回溯的新用法
        bool canWin(string currentState);
        /* 295. 数据流的中位数 */
        class MedianFinder
        {
        public:
            MedianFinder();
            void addNum(int num);
            double findMedian();
            // 最简单的实现方法就是维护两个优先队列，一个小优先，保存更大的那一半元素
            // 一个大优先，保存更小的那一半元素
            // 大优先队列
            priority_queue<int, vector<int>, less<int>> bigQ;
            // 小优先队列
            priority_queue<int, vector<int>, greater<int>> smallQ;
            // 一个变量记录当前添加过的所有元素个数，初始值为 0
            int cnt;
        };
        /* 296. 最佳的碰头地点 */   /* Mark */  /* Mark */  /* Mark */  /* Mark */
        int minTotalDistance(vector<vector<int>>& grid);
        /* 297. 二叉树的序列化与反序列化 */
        class CodecTree {
        public:
            string serialize(TreeNode* root);
            TreeNode* deserialize(string data);
        };
        /* 298. 二叉树最长连续序列 */
        int longestConsecutive(TreeNode* root);
        /* 299. 猜数字游戏 */   /* Mark */  /* Mark */
        string getHint(string secret, string guess);
        /* 300. 最长递增子序列 */
        int lengthOfLIS(vector<int>& nums);
    };
}

namespace Leetcode301_400
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
        /* 301. 删除无效的括号 */
        vector<string> removeInvalidParentheses(string s);
        /* 302. 包含全部黑色像素的最小矩形 */
        int minArea(vector<vector<char>>& image, int x, int y);
        /* 303. 区域和检索 - 数组不可变 */
        class NumArray
        {
        public:
            // 简单的前缀和问题，我们只需要在类中记录一个数组，保存所有的前缀和即可
            NumArray(vector<int>& nums);
            int sumRange(int left, int right);
            vector<int> preSum;
        };
        /* 304. 二维区域和检索 - 矩阵不可变 */
        class NumMatrix
        {
        public:
            NumMatrix(vector<vector<int>>& matrix);
            int sumRegion(int row1, int col1, int row2, int col2);
            vector<vector<int>> preSum;
        };
        /* 305. 岛屿数量 II */  /* Mark */  /* Mark */  // 并查集最好掌握，复习的时候可以看一下这道题
        vector<int> numIslands2(int m, int n, vector<vector<int>>& positions);
        /* 306. 累加数 */   /* Mark */  /* Mark */
        bool isAdditiveNumber(string num);
        /* 307. 区域和检索 - 数组可修改 */
        // 再重写一遍线段树的基本结构
        // 定义线段树结点的数据结构
        struct SegNode
        {
        public:
            // 构造函数
            SegNode(int _leftVal, int _rightVal) : hasLazy(false), lazy(0), val(0), leftVal(_leftVal), rightVal(_rightVal), left(nullptr), right(nullptr) {}
            // 鉴于题目给出的结点个数范围是最多 3x10^4 个，所以我们只能考虑使用动态开点点线段树结构，没法使用静态方式
            // 每个结点内部保存两个指针，分别指向它的两个孩子结点，未动态开点前，左右指针都是空的，只有需要开点的时候，我们才会初始化对应的指针
            SegNode* left;
            SegNode* right;
            int leftVal;
            int rightVal;
            // 记录当前结点是否拥有懒数据
            bool hasLazy;
            // 记录懒更新数据
            int lazy;
            // 记录的是当前区间的结果(对于本题，因为要的是区间和，val 就代表的是区间的和)
            int val;
            // 总结一下要实现的几个方法
            // 1. 将一个线段树结点中的一些数据更新为新值，更新区间为 [l, r]，更新值为 value
            void update(int l, int r, int value)
            {
                // 我们知道当前结点代表的区间，这个信息保存在结点的内部
                // 1. 要修改的区间包括了当前结点所在的这个区间
                if(this->leftVal >= l && this->rightVal <= r)
                {
                    // 此时直接更新懒信息即可，不用进一步深入更新
                    this->hasLazy = true;
                    this->lazy = value;
                    // 别忘了更新区间的和
                    this->val = (this->rightVal-this->leftVal+1)*value;
                    return;
                } 
                // 2. 要修改的区间和当前结点所在的区间有交集
                // 注意，本题由于我们是直接修改元素的值，而不会利用数组中元素原本的值，所以懒信息在这里并不需要先向下扩散，只有检查的时候需要更新
                // 此时先二分当前结点代表的区间
                int mid = ((this->rightVal-this->leftVal)>>1)+this->leftVal;
                // 2.1 要修改的区间区间包括了当前结点的左孩子右边界
                if(mid >= l)
                {
                    // 此时我们需要进一步修改左孩子
                    // 如果左孩子为空，那么我们需要动态开点
                    if(!this->left)
                    {
                        this->left = new SegNode(this->leftVal, mid);
                    }
                    this->left->update(l, r, value);
                }
                // 2.2 要修改的区间包括了当前结点的右孩子左边界
                if(mid+1 <= r)
                {
                    if(!this->right)
                    {
                        this->right = new SegNode(mid+1, this->rightVal);
                    }
                    this->right->update(l, r, value);
                }
                // 更新当前大区间的 val 值
                this->val = 0;
                if(this->left)
                {
                    this->val += this->left->val;
                }
                if(this->right)
                {
                    this->val += this->right->val;
                }
            }
            // 2. 根据给定的区间值检查对应区间的区间和
            int query(int l, int r)
            {
                // 1. 如果要查询的区间包括了当前结点表示的全部区间，那么直接返回 value 即可
                if(this->leftVal >= l && this->rightVal <= r)
                {
                    return this->val;
                }
                // 2. 否则，查询子结点之前，我们需要先进行懒更新
                int mid = ((this->rightVal-this->leftVal)>>1)+this->leftVal;
                // 我们稍后实现一下即可
                if(this->hasLazy)
                {
                    this->lazyUpdate(mid);
                }
                // 之后就是类似的判断过程
                // 记录最终的返回值
                int ret = 0;
                // 2.1 要查询的区间包括了当前结点的左孩子右边界
                if(mid >= l)
                {
                    ret += this->left->query(l, r);
                }
                // 2.2 要查询的区间包括了当前结点的右孩子左边界
                if(mid+1 <= r)
                {
                    ret += this->right->query(l, r);
                }
                // 查询完成，返回结果即可
                return ret;
            }
            // 3. 懒更新函数
            void lazyUpdate(int mid)
            {
                // 递归结束条件：
                // 当前结点已经是一个叶子结点了
                // 此时不用做任何事，直接返回即可
                if(this->leftVal == this->rightVal)
                {
                    return;
                }
                // 我们需要在左右孩子不存在的时候对其进行初始化
                if(!this->left)
                {
                    this->left = new SegNode(this->leftVal, mid);
                }
                if(!this->right)
                {
                    this->right = new SegNode(mid+1, this->rightVal);
                }
                // 之后，把父结点的数据传递给孩子结点
                this->left->lazy = this->lazy;
                this->left->val = this->lazy * (mid-this->leftVal+1);
                this->left->hasLazy = true;
                this->right->lazy = this->lazy;
                this->right->val = this->lazy * (this->rightVal-mid);
                this->right->hasLazy = true;
                this->lazy = 0;
                this->hasLazy = false; 
            }
        };
        class NumArray2 
        {
        public:
            NumArray(vector<int>& nums);
            void update(int index, int val);
            int sumRange(int left, int right);
            // 保存一个线段树根结点即可
            SegNode* root;
        };
        /* 308. 二维区域和检索 - 矩阵可修改 */
        // 不要被 "困难" 标签吓到，二维的题目完全可以压缩成一维来进行计算
        // 我们甚至仍然可以复用上一题写好的线段树结构
        class NumMatrix2
        {
        public:
            NumMatrix2(vector<vector<int>>& matrix);
            void update(int row, int col, int val);
            int sumRegion(int row1, int col1, int row2, int col2);
            // 依然是保存一个线段树的根结点
            SegNode* root;
            // 多保存一个数据，记录我们保存的矩阵的列数
            int cols;
        };
        /* 309. 买卖股票的最佳时机含冷冻期 */
        int maxProfit5(vector<int>& prices);
        /* 310. 最小高度树 */   /* Mark */  /* Mark */
        vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges);
        /* 311. 稀疏矩阵的乘法 */
        vector<vector<int>> multiply(vector<vector<int>>& mat1, vector<vector<int>>& mat2);
        /* 312. 戳气球 */   /* Mark */  /* Mark */  /* Mark */  /* Mark */
        int maxCoins(vector<int>& nums);
        /* 313. 超级丑数 */
        int nthSuperUglyNumber(int n, vector<int>& primes);
        /* 314. 二叉树的垂直遍历 */
        vector<vector<int>> verticalOrder(TreeNode* root);
        /* 315. 计算右侧小于当前元素的个数 */   /* Mark */  /* Mark */  /* Mark */  /* Mark */
        vector<int> countSmaller(vector<int>& nums);
        /* 316. 取出重复字母 */ /* Mark */  /* Mark */  /* Mark */  /* Mark */
        string removeDuplicateLetters(string s);
        /* 317. 离建筑物最近的距离 */   /* Mark */  /* Mark */  /* Mark */
        int shortestDistance2(vector<vector<int>>& grid);
        /* 318. 最大单词长度乘积 */ /* Mark */  /* Mark */  /* Mark */  /* Mark */
        int maxProduct(vector<string>& words);
        /* 319. 灯泡开关 */ /* Mark */  /* Mark */  /* Mark */  /* Mark */
        int bulbSwitch(int n);
        /* 320. 列举单词的全部缩写 */   /* Mark */  /* Mark */  /* Mark */  /* Mark */
        vector<string> generateAbbreviations(string word);
        /* 321. 拼接最大数 */   /* Mark */  /* Mark */  /* Mark */  /* Mark */
        vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k);
        /* 322. 零钱兑换 */ /* Mark */  /* Mark */  /* Mark */
        int coinChange(vector<int>& coins, int amount);
        /* 323. 无向图中连通分量的数目 */
        int countComponents(int n, vector<vector<int>>& edges);
        /* 324. 摆动排序 II */  /* Mark */  /* Mark */  /* Mark */  /* Mark */      // 三路快排是很优秀的一种优化快排的方案，一定要掌握
        void wiggleSort2(vector<int>& nums);
        /* 325. 和等于 k 的最长子数组长度 */    /* Mark */  /* Mark */  /* Mark */  /* Mark */
        int maxSubArrayLen(vector<int>& nums, int k);
        /* 326. 3 的幂 */
        bool isPowerOfThree(int n);
        /* 327. 区间和的个数 */ /* Mark */  /* Mark */  /* Mark */  /* Mark */
        struct SegNode2 
        {
        // 本题是一道比较经典的用线段树结构加速值搜索速度的题目，不过我们的线段树结构和方法需要做出一些调整以适应题目要求
        public:
            // 结点构造函数
            SegNode2(long long _leftVal, long long _rightVal) : left(nullptr), right(nullptr), count(0), leftVal(_leftVal), rightVal(_rightVal), lazy(0) {}
            // 1. 提供一个函数，用于更新一个区间内所有元素的值，本题我们需要的是给这个区间增加一个值 value，而不是变为新值 value
            void update(long long l, long long r, long long value)
            {
                /* TODO: 实现区间值更新逻辑 */
                // 递归结束情况：
                // 如果当前结点的左右边界被我们要更新的区间覆盖了，那么我们可以直接记录懒更新信息并返回，不用继续深入递归
                if(this->leftVal >= l && this->rightVal <= r)
                {
                    // cout << l << ", " << r << endl;
                    // cout << this->leftVal << " to " << this->rightVal << endl;
                    // 注意，本题的结构是 "更新值"，所以我们需要使用 "+=" 而不是 "="
                    this->lazy += value;
                    // 更新本结点的内容
                    this->count += (this->rightVal-this->leftVal+1)*value;
                    return;
                }
                // 一般情况：当前结点的区间和我们要更新的 [l, r] 区间有交集
                // 那么此时我们就需要对当前区间进行二分处理
                long long mid = ((this->rightVal-this->leftVal)>>1)+this->leftVal;
                // 先对孩子进行懒更新
                this->lazyUpdate(mid);
                // 根据区间中点和 [l, r] 的关系来进行进一步的递归
                // 1. mid 值覆盖了至少 l 这个下标，那么我们需要进一步更新左半区间
                if(mid >= l)
                {
                    // 同时注意动态开点，防止空指针访问
                    if(!this->left)
                    {
                        this->left = new SegNode2(this->leftVal, mid);
                    }
                    this->left->update(l, r, value);
                }
                // 2. mid+1 这个值覆盖了至少 r 这个下标，那么我们需要进一步更新右半区间
                if(mid+1 <= r)
                {
                    // 同时注意动态开点，防止空指针访问
                    if(!this->right)
                    {
                        this->right = new SegNode2(mid+1, this->rightVal);
                    }
                    this->right->update(l, r, value);
                }
                // 左右孩子更新完成后，我们需要回来更新大区间的结果
                this->count = this->left->count + this->right->count;
                return;
            }
            // 2. 提供一个函数，用于检索一个区间的结果
            int query(long long l, long long r)
            {
                /* TODO: 实现区间的查询逻辑 */
                // 递归结束情况
                // 如果当前要查询的区间包含了我们这个结点的区间，那么直接返回这个结点内部保存的结果即可
                if(this->leftVal >= l && this->rightVal <= r)
                {
                    return this->count;
                }
                // 否则，在向下递归搜索之前，我们需要先分发懒更新信息给子结点
                long long mid = ((this->rightVal-this->leftVal)>>1)+this->leftVal;
                this->lazyUpdate(mid);
                // 之后，根据计算出来的中点，向两侧深入搜索
                long long ret = 0;
                if(mid >= l)
                {
                    ret += this->left->query(l, r);
                }
                if(mid+1 <= r)
                {
                    ret += this->right->query(l, r);
                }
                return ret;
            }
            // 3. 懒更新函数
            void lazyUpdate(long long mid)
            {
                /* TODO: 实现一个懒更新函数 */
                // 这个函数要做的事情很简单
                // 就是把父结点内部保存的懒信息传递给自己的两个直接孩子即可
                // 如果当前结点已经是一个叶结点了，那么我们就不能进一步寻找孩子结点了
                // 直接返回即可
                if(this->leftVal == this->rightVal)
                {
                    return;
                }
                // 否则，在检查了子结点存在的基础上，对子结点的数据进行更新
                if(!this->left)
                {
                    this->left = new SegNode2(this->leftVal, mid);
                }
                if(!this->right)
                {
                    this->right = new SegNode2(mid+1, this->rightVal);
                }
                // 把父结点的数据传给子结点
                this->left->lazy = this->lazy;
                this->right->lazy = this->lazy;
                this->left->count += this->lazy*(mid-this->leftVal+1);
                this->right->count += this->lazy*(this->rightVal-mid);
                this->lazy = 0;
            }

            SegNode2* left;
            SegNode2* right;
            // count 用于记录值位于 [leftVal, rightVal] 之间的元素个数    
            long long count;
            // 懒更新信息
            long long lazy;
            // 记录的前缀和区间左界 [leftVal]
            long long leftVal;
            // 记录的前缀和区间右界 [rightVal]
            long long rightVal;
        };
        int countRangeSum(vector<int>& nums, int lower, int upper);
        /* 328. 奇偶链表 */
        ListNode* oddEvenList(ListNode* head);
        /* 329. 矩阵中的最长递增路径 */
        int longestIncreasingPath(vector<vector<int>>& matrix);
        /* 330. 按要求补齐数组 */
        int minPatches(vector<int>& nums, int n);
        /* 331. 二叉树的前序序列化 */
        bool isValidSerialization(string preorder);
        /* 332. 重新安排行程 */
        vector<string> findItinerary(vector<vector<string>>& tickets);
        /* 333. 最大二叉搜索子树 */
        int largestBSTSubtree(TreeNode* root);
        /* 334. 递增的三元子序列 */
        bool increasingTriplet(vector<int>& nums);
        /* 335. 路径交叉 */ /* Mark */  /* Mark */  /* Mark */
        bool isSelfCrossing(vector<int>& distance);
        /* 336. 回文对 */   /* Mark */  /* Mark */  /* Mark */
        vector<vector<int>> palindromePairs(vector<string>& words);
        /* 337. 打家劫舍 III */
        int rob(TreeNode* root);
        /* 338. 比特位计数 */   /* Mark */  /* Mark */  /* Mark */  /* Mark */
        vector<int> countBits(int n);
        /* 339. 嵌套列表加权和 */
        int depthSum(vector<NestedInteger>& nestedList);
        /* 340. 至多包含 K 个不同字符的最长子串 */
        int lengthOfLongestSubstringKDistinct(string s, int k);
        /* 341. 扁平化嵌套列表迭代器 */
        class NestedIterator {
        public:
            NestedIterator(vector<NestedInteger>& nestedList);
            int next();
            bool hasNext();

            vector<int> memo;
            int idx;
        };
        /* 342. 4 的幂 */
        bool isPowerOfFour(int n);
        /* 343. 整数拆分 */
        int integerBreak(int n);
        /* 344. 反转字符串 */
        void reverseString(vector<char>& s);
        /* 345. 反转字符串中的元音字母 */
        string reverseVowels(string s);
        /* 346. 数据流中的移动平均值 */
        class MovingAverage 
        {
        public:
            MovingAverage(int size);
            double next(int val);
            double sum;
            int maxSize;
            queue<int> q;
        };
        /* 347. 前 K 个高频元素 */
        vector<int> topKFrequent(vector<int>& nums, int k);
        /* 348. 设计井字棋 */
        class TicTacToe
        {
        public:
            TicTacToe(int n);
            int move(int row, int col, int player);
            unordered_map<int, vector<int>> rows;
            unordered_map<int, vector<int>> cols;
            unordered_map<int, vector<int>> dias;
            unordered_map<int, vector<int>> antiDias;
            int size;
        };
        /* 349. 两个数组的交集 */
        vector<int> intersection(vector<int>& nums1, vector<int>& nums2);
        /* 350. 两个数组的交集 II */
        vector<int> intersect(vector<int>& nums1, vector<int>& nums2);
        /* 351. 安卓系统手势解锁 */
        int numberOfPatterns(int m, int n);
        /* 352. 将数据流变为多个不相交区间 */   /* Mark */  /* Mark */  /* Mark */  /* Mark */
        class SummaryRanges 
        {
        public: 
            SummaryRanges();
            void addNum(int value);
            vector<vector<int>> getIntervals();
            vector<int> parents;
        };
        /* 353. 贪吃蛇 */
        // 这题就略过了，没什么技术含量的细节模拟题，面试出的概率也不大。。。
        /* 354. 俄罗斯套娃信封问题 */   /* Mark */  /* Mark */  /* Mark */
        int maxEnvelopes(vector<vector<int>>& envelopes);
        /* 355. 设计推特 */ /* Mark */  /* Mark */  /* Mark */  /* Mark */
        class Twitter   
        {
        public:
            struct Tweet 
            {
            public:
                Tweet(int _id, int _timeStamp) : id(_id), timeStamp(_timeStamp), next(nullptr) {}
                int id;
                // 时间戳，用于记录这个推发布的时间
                int timeStamp;
                // 模拟链表结构，这里存储一个指向当前用户下一个推的指针
                Tweet* next;
            };
            struct cmp 
            {
            public:
                bool operator() (Tweet* a, Tweet* b)
                {
                    return a->timeStamp < b->timeStamp;
                }
            };
            Twitter();
            void postTweet(int userId, int tweetId);
            vector<int> getNewsFeed(int userId);
            void follow(int followerId, int followeeId);
            void unfollow(int followerId, int followeeId);
            // 我们本质上需要两个数据结构
            // 1. 用于记录每个用户关注的其它人的列表
            // 2. 用于记录每个人推文 (按时间戳排序) 的列表
            // 第二个可以通过优先队列实现自排序
            // 第一个实际上一个嵌套哈希表就可以实现
            unordered_map<int, unordered_set<int>> follows;
            // 另一个哈希表，数组本身就提供了时间戳的有序性
            // 记录每个用户发布的所有推
            unordered_map<int, Tweet*> twitts;
            // 记录一个时间戳，初始时间为0
            int timeStamp;
        };
        /* 356. 直线镜像 */ /* Mark */  /* Mark */
        bool isReflected(vector<vector<int>>& points);
        /* 357. 统计各位数字都不同的数字个数 */
        int countNumbersWithUniqueDigits(int n);
        /* 358. K 距离间隔重排字符串 */ /* Mark */  /* Mark */  /* Mark */  /* Mark */
        string rearrangeString(string s, int k);
        /* 359. 日志速率限制器 */
        class Logger 
        {
        public:
            Logger();
            bool shouldPrintMessage(int timestamp, string message);
            // 我们只需要记录一个哈希表，记录每个添加过的单词上一次被打印的时间戳
            unordered_map<string, int> memo;
        };
        /* 360. 有序转化数组 */
        vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c);
        /* 361. 轰炸敌人 */
        int maxKilledEnemies(vector<vector<char>>& grid);
        /* 362. 敲击计数器 */   /* Mark */  /* Mark */
        // 很经典的队列应用问题
        // 队列一个很经典的作用，就是维护一组固定长度的窗口，记住这一点，很多题目都用到了这个性质
        // 敲击结构体，我们记录这个敲击发生的时间戳，以及它的发生次数(题目说明：同一时间戳可以发生多次敲击)
        struct Hit 
        {
        public:
            Hit(int _timestamp) : timestamp(_timestamp), cnt(1) {}
            int timestamp;
            int cnt;
        };
        class HitCounter
        {
        public: 
            HitCounter();
            void hit(int timestamp);
            int getHits(int timestamp);
            // 维护一个双端队列，保证队列里面的元素的时间戳和可能查询的时间戳之间的时间差距不超过5分钟
            deque<Hit> visible;
            // 加快返回时的信息获取效率，我们记录一个内部变量
            int size;
        };
        /* 363. 矩形区域不超过 K 的最大数值和 */    /* Mark */  /* Mark */  /* Mark */  /* Mark */  /* 面试题 17.24 */
        int maxSumSubmatrix(vector<vector<int>>& matrix, int k);
        /* 364. 嵌套列表加权和 */
        int depthSumInverse(vector<NestedInteger>& nestedList);
        /* 365. 水壶问题 */
        bool canMeasureWater(int x, int y, int target);
        /* 366. 寻找二叉树的叶子结点 */
        vector<vector<int>> findLeaves(TreeNode* root);
        /* 367. 有效的完全平方数 */
        bool isPerfectSquare(int num);
        /* 368. 最大整除子集 */ /* Mark */  /* Mark */  /* Mark */  /* Mark */
        vector<int> largestDivisibleSubset(vector<int>& nums);
        /* 369. 给单链表加一 */
        ListNode* plusOne(ListNode* head);
        /* 370. 区间加法 */ /* Mark */  /* Mark */  /* Mark */  /* Mark */
        vector<int> getModifiedArray(int length, vector<vector<int>>& updates);
        /* 371. 两整数之和 */
        int getSum(int a, int b);
        /* 372. 超级次方 */
        int superPow(int a, vector<int>& b);
        /* 373. 查找和最小的 K 对数字 */
        vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k);
        /* 374. 猜数字大小 */
        int guessNumber(int n);
        /* 375. 猜数字大小 II */
        int getMoneyAmount(int n);
        /* 376. 摆动序列 */ /* Mark */  /* Mark */  /* Mark */  /* Mark */
        int wiggleMaxLength(vector<int>& nums);
        /* 377. 组合总和 IV */  /* Mark */  /* Mark */  /* Mark */
        int combinationSum4(vector<int>& nums, int target);
        /* 378. 有序矩阵中第 K 小的元素 */
        int kthSmallest(vector<vector<int>>& matrix, int k);
        /* 379. 电话目录管理系统 */
        class PhoneDirectory
        {
        public:
            PhoneDirectory(int maxNumbers);
            int get();
            bool check(int number);
            void release(int number);
            // 具体的实现逻辑见对应文件，这里不做赘述
            // 负责顶层索引的下标值
            int idx;
            // 负责底层索引的位图
            vector<unsigned int> mappingBottom;
            int constraint;
            int maxNumber;
        };
        /* 380. O(1) 时间插入、删除和获取随机元素 */    /* Mark */  /* Mark */  /* Mark */  /* Mark */
        class RandomizedSet 
        {
        public:
            RandomizedSet();
            bool insert(int val);
            bool remove(int val);
            int getRandom();
            vector<int> memo;
            unordered_map<int, int> remapping;
        };
        /* 381. O(1) 时间插入、删除和获取随机元素 - 允许重复 */ /* Mark */  /* Mark */  /* Mark */  /* Mark */
        class RandomizedCollection
        {
        public:
            RandomizedCollection();
            bool insert(int val);
            bool remove(int val);
            int getRandom();
            vector<int> memo;
            // 记录某个值在结构中出现的所有位置下标
            unordered_map<int, unordered_set<int>> remapping;
        };
        /* 382. 链表随机结点 */ /* Mark */  /* Mark */  /* Mark */  /* Mark */
        class Solution
        {
        public:
            Solution(ListNode* head);
            int getRandom();
            ListNode* memo;
        };
        /* 383. 赎金信 */
        bool canConstruct(string ransomNote, string magazine);
        /* 384. 打乱数组 */ /* Mark */  /* Mark */  /* Mark */  /* Mark */
        class Solution
        {
        public:
            Solution(vector<int>& nums);
            vector<int> reset();
            vector<int> shuffle();
            // 用于 reset 函数恢复原值
            vector<int> memo;
            vector<int> res;
        };
        /* 385. 迷你语法分析器 */   /* Mark */  /* Mark */  /* Mark */
        NestedInteger deserialize(string s);
        /* 386. 字典序排数 */
        vector<int> lexicalOrder(int n);
        /* 387. 字符串中的第一个唯一字符 */
        int firstUniqChar(string s);
        /* 388. 文件的最长路径 */   /* Mark */  /* Mark */  /* Mark */
        int lengthLongestPath(string input);
        /* 389. 找不同 */
        char findDifference(string s, string t);
        /* 390. 消除游戏 */ /* Mark */  /* Mark */  /* Mark */  /* Mark */
        int lastRemaining(int n);
        /* 391. 完美矩形 */ /* Mark */  /* Mark */  /* Mark */  /* Mark */
        bool isRectangleCover(vector<vector<int>>& rectangles);
        /* 392. 判断子序列 */
        bool isSubSequence(string s, string t);
        /* 393. UTF-8 编码验证 */
        bool validUtf8(vector<int>& data);
        /* 394. 字符串解码 */
        string decodeString(string s);
        /* 395. 至少有 K 个重复字符的最长子串 */    /* Mark */  /* Mark */  /* Mark */  /* Mark */
        int longestSubstring(string s, int k);
        /* 396. 旋转函数 */
        int maxRotateFunction(vector<int>& nums);
        /* 397. 整数替换 */
        int integerReplacement(int n);
        /* 398. 随机数索引 */
        class Solution
        {
        public:
            Solution(vector<int>& nums);
            int pick(int target);
            // 保存一个 数值 -> 下标集合 的映射关系
            unordered_map<int, vector<int>> memo;
        };
        /* 399. 除法求值 */
        vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries);
        /* 400. 第 N 位数字 */  /* Mark */  /* Mark */  /* Mark */  /* Mark */
        int findNthDigit(int n);
    };
}

namespace Leetcode401_500
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
        /* 401. 二进制手表 */
        vector<string> readBinaryWatch(int turnedOn);
        /* 402. 移掉 K 位数字 */
        string removeKdigits(string num, int k);
        /* 403. 青蛙过河 */
        bool canCross(vector<int>& stones);
        /* 404. 左叶子之和 */
        int sumOfLeftLeaves(TreeNode* root);`
        /* 405. 数字转换为十六进制数 */
        string toHex(int num);
        /* 406. 根据身高重建队列 */
        vector<vector<int>> reconstructQueue(vector<vector<int>>& people);
        /* 407. 接雨水 II */
        int trapRainWater(vector<vector<int>>& heightMap);
        /* 408. 有效单词缩写 */
        bool validWordAbbreviation(string word, string abbr);
        /* 409. 最长回文串 */
        int longestPalindrome(string s);
        /* 410. 分割数组的最大值 */
        int splitArray(vector<int>& nums, int k);
        /* 411. 最短独占单词缩写 */
        string minAbbreviation(string target, vector<string>& dictionary);
        /* 412. Fizz Buzz */
        vector<string> fizzBuzz(int n);
        /* 413. 等差数列划分 */
        int numberOfArithmeticSlices(vector<int>& nums);
        /* 414. 第三大的数 */
        int thirdMax(vector<int>& nums);
        /* 415. 字符串相加 */
        string addStrings(string num1, string num2);
        /* 416. 分割等和子集 */
        bool canPartition(vector<int>& nums);
        /* 417. 太平洋大西洋水流问题 */ /* Mark */  /* Mark */  /* Mark */  /* Mark */
        vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights);
        /* 418. 屏幕可显示句子的数量 */
        int wordsTyping(vector<string>& sentence, int rows, int cols);
        /* 424. 替换后的最长重复字符 */
        int characterReplacement(string s, int k);
        /* 432. 全 O(1) 的数据结构 */   /* Mark */  /* Mark */  /* Mark */  /* Mark */
        // 注：本题引用了 Leetcode 中文站 Aisakave 大佬的题解代码 https://leetcode.cn/problems/all-oone-data-structure/solutions/2949695/shu-ju-jie-gou-she-ji-gao-pin-ti-qi-by-r-p3hx/
        // 个人认为是最好理解的类 LFU 实现了
        struct Bucket 
        {
            unordered_set<string> set;
            int cnt;
            Bucket* last;
            Bucket* next;
            // 构造函数
            Bucket(const string& s, int c) : cnt(c), last(nullptr), next(nullptr) 
            {
                set.insert(s);
            }
        };
        class AllOne 
        {
        public:
            AllOne();
            void inc(string key);
            void dec(string key);
            string getMaxKey();
            string getMinKey();
            void insert(Bucket* cur, Bucket* pos);
            void remove(Bucket* cur);
            Bucket* head;   // 哨兵头结点
            Bucket* tail;   // 哨兵尾结点
            unordered_map<string, Bucket*> map;  // 字符串 -> 对应桶的映射
        };
        /* 433. 最小基因变化 */
        int minMutation(string startGene, string endGene, vector<string>& bank);
        /* 434. 字符串中的单词数 */
        int countSegments(string s);
        /* 435. 无重叠区间 */
        int eraseOverlapIntervals(vector<vector<int>>& intervals);
        /* 440. 字典序的第 K 小数字 */
        int findKthNumber(int n, int k);
    };
}

namespace Leetcode601_700
{
    class Solution
    {
        /* 652. 寻找重复的子树 */
        vector<TreeNode*> findDuplicateSubtrees(TreeNode* root);
        /* 654. 最大二叉树 */
        TreeNode* constructMaximumBinaryTree(vector<int>& nums);
        /* 679. 24 点游戏 */
        bool judgePoint24(vector<int>& cards);
        /* 698. 划分为 k 个相等的子集 */
        bool canPartitionKSubsets(vector<int>& nums, int k);
    };
}
#endif