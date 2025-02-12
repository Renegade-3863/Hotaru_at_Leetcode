#include "Solution.h"

Leetcode501_600::TreeNode* Leetcode501_600::Leetcode501_600::Soltuion::str2tree(string s)
{
    if(s.empty())
    {
        return nullptr;
    }
    // 一道不难的 DFS 类题目，我们需要一个过程变量来跟踪程序处理到的字符下标
    int idx = 0;
    // 定义一个函数，dfs，用于处理当前还未被处理的剩余子串
    function<TreeNode*()> dfs = [&]() -> TreeNode*
    {
        // 我们首先处理当前下标 idx 处的数值 (本函数的假设就是，每次调用它，剩余子串的开头都是一个数值)
        // 我们先分离出当前开头的数值
        // sign 代表当前开头数值是正还是负
        int val = 0, sign = 1;
        if(s[idx] == '-')
        {
            sign = -1;
            ++idx;
        }
        while(isdigit(s[idx]))
        {
            val = val*10+(s[idx++]-'0');
        }
        // 循环结束时，val 中保存了当前结点应有的值，idx 指向的要么是一个左括号，要么是一个右括号，要么是结束符 '\0'
        // 先构建当前结点
        TreeNode* cur = new TreeNode(sign*val);
        // 如果 s[idx] 是左括号，那么递归构建，并把结果结点赋给 cur 的左孩子
        if(s[idx] == '(')
        {
            ++idx;
            cur->left = dfs();
            ++idx;
        }
        // 否则，是右括号或者是字符串的结束，说明当前结点的处理已经完成，我们可以返回 cur 了
        else 
        {
            return cur;
        }
        // cout << idx << endl;
        // 赋值完成后，idx 又有同样的可能，我们进行讨论处理
        if(s[idx] == '(')
        {
            ++idx;
            cur->right = dfs();
            ++idx;
        }
        return cur;
    };
    // 直接调用 dfs 即可
    return dfs();
}