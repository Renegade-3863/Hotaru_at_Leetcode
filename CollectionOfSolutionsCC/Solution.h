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
    };
}
#endif