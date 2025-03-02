#include "Solution.h"

string Leetcode601_700::Soltuion::solveEquation(string equation)
{
    // 一道简单的模拟题，并没有什么算法可言
    // 基本的想法是，我们用两个值来记录等号左右两侧的 x 的总个数
    // 之后两侧进行化简处理
    // 最后注意一点，我们一定需要把 x 以及对应的系数放到一侧进行记录，同时把常数留到另一侧
    // 构成 ax = b 的格式
    // 便于最后得出 x = b/a 这一结果
    int leftCnt = 0, rightCnt = 0;
    int leftNum = 0, rightNum = 0;
    // 对 equation 进行解析，提取出 x 的系数
    int idx = 0, n = equation.size();
    // 用上 idx < n 是为了防止不含 = 号的错误数据导致程序陷入死循环
    // 引入 par 参数，记录当前可能作为 x 参数的任何数
    int par = 0;
    int sign = 1;
    while(equation[idx] != '=' && idx < n)
    {   
        // 1. 如果当前是一个 'x'
        // 那么我们检查 par 中是否已有系数，如果 par 为 0，那么我们对 leftCnt 累加 1
        // 否则，累加 par 的值
        // 无论累加多少，par 在这种情况下最后需要被重置为 0
        if(equation[idx] == 'x')
        {
            leftCnt += ((idx == 0 || !isdigit(equation[idx-1]) ? 1*sign : sign*par));
            par = 0;
        }
        // 2. 如果当前是一个数字，那么正常累加到 par 中
        else if(isdigit(equation[idx]))
        {
            par = par*10+(equation[idx]-'0');
        }
        // 3. 当前是一个符号，我们分类讨论
        else 
        {
            // 首先，我们必须检查符号前面的最后一个字符是数字还是 'x'
            // 如果是 'x'
            // 那么我们什么也不用做
            // 如果是数字，那么我们需要把 par 累计到 leftNum 中
            if(idx > 0 && isdigit(equation[idx-1]))
            {
                leftNum += sign*par;
                // 使用完毕后，把 par 清零，sign 重置为 1
                par = 0;
                sign = 1;
            }
            switch(equation[idx])
            {
                // 如果是个加号
                case '+':
                    // 我们把 sign 置为 1
                    sign = 1;
                    break;
                case '-':
                    // 我们把 sign 置为 -1
                    sign = -1;
                    break;
                default:
                    break;
            }
        }
        ++idx;
    }
    // 注意，上面的循环退出的节点在 '=' 号处，所以最后一项如果是个数字，我们还必须把它累加到 leftCnt 中
    if(idx == n)
    {
        // 字符串不符合要求，返回空字符串作为结果
        return "";
    }
    if(isdigit(equation[idx-1]))
    {
        leftNum += sign*par;
    }
    // 解析后半部分，方法类似
    ++idx;
    par = 0; sign = 1;
    while(idx < n)
    {
        // 1. 如果当前是一个 'x'
        // 那么我们检查 par 中是否已有系数，如果 par 为 0，那么我们对 leftCnt 累加 1
        // 否则，累加 par 的值
        // 无论累加多少，par 在这种情况下最后需要被重置为 0
        if(equation[idx] == 'x')
        {
            rightCnt += (idx == 0 || !isdigit(equation[idx-1]) ? 1*sign : sign*par);
            par = 0;
            sign = 1;
        }
        // 2. 如果当前是一个数字，那么正常累加到 par 中
        else if(isdigit(equation[idx]))
        {
            par = par*10+(equation[idx]-'0');
        }
        // 3. 当前是一个符号，我们分类讨论
        else 
        {
            // 首先，我们必须检查符号前面的最后一个字符是数字还是 'x'
            // 如果是 'x'
            // 那么我们什么也不用做
            // 如果是数字，那么我们需要把 par 累计到 leftNum 中
            if(idx > 0 && isdigit(equation[idx-1]))
            {
                rightNum += sign*par;
                // 使用完毕后，把 par 清零
                par = 0;
            }
            switch(equation[idx])
            {
                // 如果是个加号
                case '+':
                    // 我们把 sign 置为 1
                    sign = 1;
                    break;
                case '-':
                    // 我们把 sign 置为 -1
                    sign = -1;
                    break;
                default:
                    break;
            }
        }
        ++idx;
    }
    // 还是别忘了最后一项
    if(isdigit(equation[n-1]))
    {
        rightNum += sign*par;
    }
    // 现在只需要把 leftCnt 和 rightCnt 相减，再把 rightNum 和 leftNum 相减
    // 最后结果取商即可
    // 如果 leftCnt == rightCnt，同时 rightNum != leftNum，那么返回 "No solution"
    // 而其它情况下，如果 leftCnt == rightCnt，那么返回 “Infinite solutions"
    if(leftCnt == rightCnt)
    {
        return leftNum != rightNum ? "No solution" : "Infinite solutions";
    }
    return (rightNum-leftNum)%(leftCnt-rightCnt) == 0 ? "x="+to_string((rightNum-leftNum)/(leftCnt-rightCnt)) : "No solution"; 
}