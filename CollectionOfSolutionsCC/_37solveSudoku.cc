#include "Solution.h"

void Leetcode1_100::Solution::solveSudoku(vector<vector<char>>& board)
{
    // 给定一个有效的数独表格，要求我们找出一个合法的解
    // 基本思路很简单，就是回溯，不过本题填数的时候需要注意一些细节
    // 先考虑一下回溯的过程，我们要做的是，对于每个格子，如果它原本是空的，那么我们就需要检查所有可能可以填入的值
    // 每填完一个可行的值，就要继续向后递归地填写
    // 问题在于，题目要我们找的是可行的解，要求这个解最后被填写在 board 中，那么我们如果在递归过程中就填写了 board 
    // 那如何保证后面再回溯到本格的时候，还能确定这个格子是需要进行填写的呢？
    // 因而我们就需要额外使用一个信息表(数组)来决定当前检查到的格子是否是一开始为空的
    // 进一步考虑，所有原始不为空的格子，我们其实都是不用进行任何检查的
    // 可以直接跳过检查
    // 因而我们的信息表可以只记录那些原来为空的格子信息
    // 递归的时候对这个表中的信息按下标逐个遍历即可
    vector<pair<int, int>> spaces;
    // 同时，为了检查一个格子是否可以填入某个值，我们还需要三个额外的数组用来记录一个格子所在的行、列、九宫格中已经存在的所有值
    vector<vector<bool>> rows(9, vector<bool>(9, false));
    vector<vector<bool>> cols(9, vector<bool>(9, false));
    vector<vector<bool>> matrices(9, vector<bool>(9, false));

    // 规定了 board 的维度是 9 x 9
    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            if(board[i][j] == '.')
            {
                // 向 spaces 数组中记录这个初始为空的格子信息
                // 一个很细节的问题，这里 make_pair 进行实例化的时候，不能使用 <int, int> 这样的方式，由于 C++11 后的 make_pair 函数使用了万能引用
                // 因而如果我们使用这种显式的类型推导，<T1&&, T2&&> 会把 T1 替换成 int，T2 也替换成 int，因而我们会发现，实例化后，这个函数要求的参数就是
                // (int&&, int&&)，也就是两个整形右值
                // 而此时我们传入的参数是 i, j，显然是两个左值，右值引用没法直接绑定到左值上，因而就会报错，所以，要么这里用两个引用类型做推导
                // int& && = int&
                // 编译器就知道我们要传入的是一个左值
                // 要么外面用 <int, int>，里面用 std::move 函数把传入的左值强转成右值
                // 不过基于 move 的语义，这里不推荐使用第二种方法，因为我们后面很可能还会用到这两个 int 类型值，转成右值后，
                // 这两个变量本身相当于已经在离开 make_pair 函数后被销毁了，这并不是我们想要的
                // 当然，如果你觉得这个用法太复杂难懂，直接用 emplace_back 肯定是没问题的，不过只要你传参用的是 make_pair，就必须要注意这个问题
                spaces.push_back(make_pair<int&, int&>(i, j));
            }
            // 否则，如果这个格子中已经有数字了，更新三个表格对应的信息
            else
            {
                rows[i][board[i][j]-1-'0'] = true;
                cols[j][board[i][j]-1-'0'] = true;
                matrices[i-i%3+j/3][board[i][j]-1-'0'] = true;
            }
        }
    }
    // 写好递归的函数体
    function<void(vector<vector<char>>&, vector<vector<bool>>&, vector<vector<bool>>&, vector<vector<bool>>&, int, bool&)> backtrack 
    = [&](vector<vector<char>>& board, vector<vector<bool>>& rows, vector<vector<bool>>& cols, vector<vector<bool>>& matrices, int idx, bool& valid)
    {
        // 退出条件为：已经检查了 spaces 中所有的空白格子
        if(idx == spaces.size())
        {
            valid = true;
            return;
        }
        // 获取当前空白格子的下标信息
        auto [x, y] = spaces[idx];
        // 尝试9个数字
        for(int i = 1; i <= 9 && !valid; ++i)
        {
            // 如果这个值可以填入，就填入并递归
            if(!rows[x][i-1] && !cols[y][i-1] && !matrices[x-x%3+y/3][i-1])
            {
                rows[x][i-1] = true;
                cols[y][i-1] = true;
                matrices[x-x%3+y/3][i-1] = true;
                board[x][y] = (char)(i+'0');
                backtrack(board, rows, cols, matrices, idx+1, valid);
                // 注意这里不能把 board 也重置，不然在我们找到了合法答案并返回的时候，这里会把我们找到的合法值给清除
                // 或者可以这样做，就是在递归退出的这里立即检查 valid 字段，而不是执行到下一个 for 循环才进行检查
                if(valid)
                {
                    break;
                }
                board[x][y] = '.';
                rows[x][i-1] = false;
                cols[y][i-1] = false;
                matrices[x-x%3+y/3][i-1] = false;
            }
        }
    };
    bool valid = false;
    // 执行回溯函数体即可
    backtrack(board, rows, cols, matrices, 0, valid);
}