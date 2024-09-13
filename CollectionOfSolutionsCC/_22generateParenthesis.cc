#include "Solution.h"

vector<string> Leetcode1_100::Solution::generateParenthesis(int n)
{
    // 本题要求找出所有可能的有效括号组合，给定的 n 值是整个字符串数组中需要有的括号对数
    // 一般这种要求找出所有可能结果的，都不得不使用回溯暴搜的方法
    // 我们需要考虑的是如何进行可能结果的构造，以及如何结束回溯的递归步骤
    /**
     * @param res 全局的答案数组，存储所有已经找到的合法的，括号对数正确的结果
     * @param cur 当前的括号串，存储已经填入的字符串
     * @param left 记录当前 cur 中已经添加了的左括号个数
     * @param right 记录当前 cur 中已经添加了的右括号个数
     */
    function<void(vector<string>&, string, int, int)> backtrack = [&](vector<string>& res, string cur, int left, int right)
    {
        // 如何进行回溯？
        // 比较显然的结束条件是
        // 添加的右括号个数已经达到了 n，因为我们只有在可行的时候才会添加右括号，因而我们一定是在添加完了所有右括号的同时完成了 n 对括号的构建
        if(right == n)
        {
            res.push_back(cur);
            return;
        }
        // 递归步骤，进行括号字符的填入
        // 可以和一般回溯的逻辑进行统一，对于每一个下标位，我们可以选择填入左括号或者是右括号，只不过我们此时需要确认这种添加是合法的
        // 因为只有一种括号，所以我们只需要记录，如果当前要添加的是右括号，是不是左边还有空闲的左括号，如果当前要添加的是左括号
        // 是不是左括号的总个数还是小于 n 的
        if(left < n)
        {
            backtrack(res, cur+'(', left+1, right);
        }
        if(right < left)
        {
            backtrack(res, cur+')', left, right+1);
        }
    };
    // 设置好参数后直接调用函数即可
    vector<string> res;
    string cur;
    backtrack(res, cur, 0, 0);
    return res;
}