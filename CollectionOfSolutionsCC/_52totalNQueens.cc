#include "Solution.h"

// 这题和 51题：N 皇后几乎完全一致，不需要多少修改，所以直接自己 copy 自己了...

int Leetcode1_100::Solution::totalNQueens(int n) {
    // 非常经典的回溯类问题
    // 难点在于记录题中要求的当前行、当前列、当前对角线的皇后存在问题
    // 这一点可以使用三个数组进行分别记录来实现
    // 至于行数组，我们后面的回溯过程是根据行来进行遍历，故递归上层所在的行一定是已经使用过了，因而不再需要额外记录一个数组
    vector<bool> cols(n, false);
    vector<bool> dia(2*n-1, false);
    vector<bool> anti_dia(2*n-1, false);
    // 问题在于，如何通过一个格子的坐标来判定它是在哪个对角线/反对角线上
    // 切入点可以是数学角度
    // 观察到，这个正方形的棋盘的每条对角线其实都可以抽象成一个二维笛卡尔坐标系中的一条直线
    // 这条直线的斜率为 1 或 -1
    // 对于主对角线
    // 直线应该是 y = -x + k (其中左上角为 (0, 0) 下标)
    // 这里的 k 可以映射成坐标的关系式
    // k = j-i (可正可负)
    // 对于副对角线
    // 直线应该是 y = x + k (其中左上角为 (0, 0) 下标)
    // 这里的 k 可以映射成坐标的关系式
    // k = -(i+j) (恒为负)
    // 再把这些直线按顺序赋予序号jike
    // 主对角线：3+(j-i) 为数组的下标 (注意不要 hard-code，这里的 3 是因为题中原有的例子是 n = 4 的，实际上应该是 n-1)
    // 副对角线：i+j 为数组的下标
    // 完成了最难的这一步映射，我们就可以简单地开始回溯了
    function<void(int&, vector<string>&, int)> backtrack = [&](int& res, vector<string>& cur, int x)
    {
        // 上一题要求记录所有结果，本题需要记录个数，只需要修改记录的数据即可
        if(x == n)
        {
            ++res;
            return;
        }
        // 检查当前行的所有列
        for(int y = 0; y < n; ++y)
        {
            // 首先检查 (x, y) 位置是否可以添加一个皇后
            if(cur[x][y] == '.' && !cols[y] && !dia[n-1+(y-x)] && !anti_dia[x+y])
            {
                cur[x][y] = 'Q';
                cols[y] = true;
                dia[n-1+(y-x)] = true;
                anti_dia[x+y] = true;
                backtrack(res, cur, x+1);
                // 回溯
                anti_dia[x+y] = false;
                dia[n-1+(y-x)] = false;
                cols[y] = false;
                cur[x][y] = '.';
            }
        }
    };
    int res = 0;
    vector<string> cur (n, "");
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            cur[i] += '.';
        }
    }
    backtrack(res, cur, 0);
    return res;
}