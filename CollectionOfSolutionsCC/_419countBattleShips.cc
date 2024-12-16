#include "Solution.h"

int Leetcode401_500::Solution::countBattleShips(vector<vector<char>>& board)
{
    // 中文版题目描述很不清晰，建议转换成英文看原版描述
    // 看明白了本质是一个脑筋急转弯题目，没什么价值，这里直接简单解释一下官方题解的内容好了。。。
    int row = board.size(), col = board[0].size();
    int ans = 0;
    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col; ++j)
        {
            if(board[i][j] == 'X')
            {
                // 两种 "当前格子不是战舰左上格子" 的情况
                if(i > 0 && board[i-1][j] == 'X')
                {
                    continue;
                }
                if(j > 0 && board[i][j-1] == 'X')
                {
                    continue;
                }
                ans++;
            }
        }
    }
    return ans;
}