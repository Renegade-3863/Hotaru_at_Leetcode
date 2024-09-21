#include "Solution.h"

// 先不进行特殊剪枝，只进行简单回溯查找结果，写出初版代码
// 要用 C++ 自带的散列表记录结构体类型的键需要重构 find 函数等成员函数，感觉比较复杂。。。
bool Leetcode1_100::Solution::exist(vector<vector<char>>& board, string word)
{
    // hard-code 四个深搜方向，按顺序为上，右，下，左
    const int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    vector<vector<bool>> visited(board.size(), vector<bool>(board[0].size(), false));
    // 用于判断某个下标是否合法
    function<bool(int, int)> valid = [&](int i, int j)
    {
        return i >= 0 && i < board.size() && j >= 0 && j < board[0].size();
    };
    // 本题要求在一个二维的字符矩阵中找出一个给定单词是否出现过
    // 应该说也是比较经典的回溯类问题了
    // 我们可以看出来的遍历顺序基本就是，以每一个格子作为起始下标，执行回溯检查，中间执行剪枝操作
    // 回调函数功能：检查从 board[i][j] 开始的所有可能结果是否可以构成 word 从 start 开始的子串
    function<bool(int, int, int)> backtrack = [&](int i, int j, int start)
    {
        // 递归的基本条件：start == word.size() 也就是从当前位置开始，匹配一个空的子串，那么一定是可行的
        if(start == word.size()-1)
        {
            return board[i][j] == word[start];
        }
        bool res = false;
        // 如果当前位置的字符能够匹配，则向四周扩散，寻找可能性
        if(board[i][j] == word[start])
        {
            for(int k = 0; k < 4; ++k)
            {
                int nexti = i+dirs[k][0], nextj = j+dirs[k][1];
                if(valid(nexti, nextj) && !visited[nexti][nextj])
                {
                    visited[nexti][nextj] = true;
                    // 只要这个下一位开始的子串能够构成 word 中剩下的子字符串，那么整体上就是可行的
                    res = res || backtrack(nexti, nextj, start+1);
                    visited[nexti][nextj] = false;
                }
            }
            return res;
        }
        // 如果当前字符都不一样，后面的也就不用看了，直接返回 false 即可
        return false;
    };
    bool ret = false;
    for(int i = 0; i < board.size(); ++i)
    {
        // 当某一个起点已经找到了结果，我们就可以直接返回了
        for(int j = 0; j < board[0].size() && !ret; ++j)
        {
            visited[i][j] = true;
            ret = ret || backtrack(i, j, 0);
            visited[i][j] = false;
        }
    }
    return ret;
}