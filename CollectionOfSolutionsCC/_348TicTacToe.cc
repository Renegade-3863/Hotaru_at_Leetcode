#include "Solution.h"

Leetcode301_400::Solution::TicTacToe::TicTacToe(int n) : size(n)
{
    // 很基本的模拟类问题，类似八皇后，但简单得多
    // 为了判断每一步结束后是否有人胜出，我们只需要保存四个数组
    // 每一行上两种棋子的个数
    // 每一列上两种棋子的个数
    // 每一条对角线上两种棋子的个数
    // 每一条反对角线上两种棋子的个数
    // 使用这四种数组，那么在初始化阶段我们就不需要任何操作
}

int Leetcode301_400::Solution::TicTacToe::move(int row, int col, int player)
{
    // 我们对每一个组分用一个数对来表达：这个行上玩家1的棋子个数、这个行上玩家2的棋子个数
    // 以此类推
    // 之后我们只需要判断更新过的对应组分中有没有达到满状态的即可
    // 更新行：
    if(this->rows.find(row) == this->rows.end())
    {
        this->rows[row] = vector<int>(2, 0);
    }
    // ++this->rows[row][player % 2];
    // 如果出现了满，就返回这个玩家即可
    if(++this->rows[row][player % 2] == this->size)
    {
        return player;
    }
    // 更新列：
    if(this->cols.find(col) == this->cols.end())
    {
        this->cols[col] = vector<int>(2, 0);
    }
    if(++this->cols[col][player % 2] == this->size)
    {
        return player;
    }
    // 更新对角线
    // 对角线和坐标之间的映射可以通过相等的差值来进行
    if(this->dias.find(row-col) == this->dias.end())
    {
        this->dias[row-col] = vector<int>(2, 0);
    }
    if(++this->dias[row-col][player % 2] == this->size)
    {
        return player;
    }
    // 更新反对角线
    // 反对角线和坐标之间的映射可以通过相等的和值来进行
    if(this->antiDias.find(row+col) == this->antiDias.end())
    {
        this->antiDias[row+col] = vector<int>(2, 0);
    }
    if(++this->antiDias[row+col][player % 2] == this->size)
    {
        return player;
    }
    // 否则，目前还没有人赢，返回 0 即可
    return 0;
}