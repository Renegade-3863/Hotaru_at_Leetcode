#include "Solution.h"

bool isValidSudoku(vector<vector<char>>& board)
{
    // 本题要求判断一个数独是否是有效
    // 我们只需要按照规则进行检查就行
    // 用三个标记数组判断当前行、当前列、当前九宫格内是否出现过
    // 行数组
    vector<vector<bool>> rows(9, vector<bool>(9, false));
    // 列数组
    vector<vector<bool>> cols(9, vector<bool>(9, false));
    // 九宫格数组
    vector<vector<bool>> matrices(9, vector<bool>(9, false));
    // 按顺序遍历整个矩阵即可
    // 关键问题在于如何明确当前格子属于哪个九宫格
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            // 标记九个九宫格分别为 0 - 9
            // (0, 0) -> 0; (0, 3) -> 1; (0, 6) -> 2
            // 映射关系为：设行列为 i, j，有九宫格下标为：i-(i%3)+j/3 
            if(board[i][j] != '.')
            {
                if(rows[i][board[i][j]-1-'0'])
                {
                    return false;
                }
                rows[i][board[i][j]-1-'0'] = true;
                if(cols[j][board[i][j]-1-'0'])
                {
                    return false;
                }
                cols[j][board[i][j]-1-'0'] = true;
                if(matrices[i-(i%3)+j/3][board[i][j]-1-'0'])
                {
                    return false;
                }
                matrices[i-(i%3)+j/3][board[i][j]-1-'0'] = true;
            }
        }
    }
    // 所有格子都是合法的，那么就说明整个矩阵是一个合法的数独矩阵
    return true;
}   