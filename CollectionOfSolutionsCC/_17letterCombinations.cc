#include "Solution.h"

vector<string> Leetcode1_100::Solution::letterCombinations(string digits)
{
    // 存储数字和可选字符的字符串的无序表
    unordered_map<char, string> board = {
        {'1', ""},
        {'2', "abc"},
        {'3', "def"},
        {'4', "ghi"},
        {'5', "jkl"},
        {'6', "mno"},
        {'7', "pqrs"},
        {'8', "tuv"},
        {'9', "wxyz"},
        {'0', ""}
    };
    // 本题的目标是，给定一个(对应用户的)输入数字序列，要求根据这个字符序列检出所有用户可能想要的输入字符序列
    // 可以说是经典的回溯类问题了
    // 不难知道输入的字符序列长度一定和给定的原数字序列 digits 长度相同
    int n = digits.size();
    // 存储用户任何一种可能的输入序列
    string cur = "";
    // 其实基本所有的回溯类问题都可以用一个类似多叉树的结构图很好的表示出来，求解相关问题的时候可以通过这种类似的结构图进行理解
    // 对于每一层，根据当前位置的数字，轮流尝试所有可能添加到当前位的字符
    /**
     * @param res 全局的结果数组，存储所有可能的结果值
     * @param cur 本地已经找到的、exclusive 的可能数据串，只有长度和 digits 数组相同时才是有效的
     * @param idx 当前检查到的数字的下标
     */
    function<void(vector<string>&, string, int)> backtrack = [&](vector<string>& res, string cur, int idx)
    {
        // 回溯的回调函数，用于进行回溯过程
        // 回溯结束条件：如果 cur 的长度已经和 digits 相同，说明我们已经找到了一个合法的(注意，本题的性质使得不会出现重复检出的字符串)
        if(cur.size() == digits.size())
        {
            res.emplace_back(cur);
            return;
        }
        // 回溯递归步骤：用一个 for 循环按序检查当前数字可能对应的所有字符，逐个尝试填入后回溯即可
        string tmp = board[digits[idx]];
        for(int i = 0; i < tmp.size(); ++i)
        {
            backtrack(res, cur+tmp[i], idx+1);
        }
    };
    vector<string> res;
    backtrack(res, cur, 0);
    return res;
}