#include "solution.h"

// 第一版：纯 DFS 解法
vector<int> Leetcode201_300::Solution::diffWaysToCompute(string expression)
{
    // 一道很明显的 DFS 题目，考虑如何执行递归，何时结束递归
    // 考虑下面的递归方法：
    // 我们枚举当前层所有的二分表达式的方法，规定二分的其中一个子表达式为递归子问题，另一个为线性计算，不再递归地添加运算优先级
    // 例如：
    // (expr1)opnd(expr2)
    // 代表我们先计算左侧括号里面的表达式，产生它所有可能的运算结果集合
    // 对于生成的集合中的所有不同的可能结果，分别进行 opnd 的运算，直到找出所有可行的结果
    // 我们剩下需要考虑的就只剩下递归结束条件了
    // 一个最简单的表达式就是一个单独的数值，此时我们不需要进行任何的计算，只需要返回存储了这一个值的集合即可
    // 注意，递归函数需要额外的边界值记录 expression 的左右边界
    // 所以，我们额外写一个递归回调函数
    function<vector<int>(int, int)> dfs = [&](int left, int right) -> vector<int> 
    {
        // 首先我们初始化一个结果数组，用于保存所有拆分方案的计算结果
        vector<int> res;
        // 逐个按运算符分割 expression 成两个子表达式，进行递归计算
        // 我们需要一种方案，来判断当前子表达式是不是一个纯数字
        // 可以先用一轮遍历进行检查
        bool isNumber = true;
        int number = 0;
        for(int i = left; i <= right; ++i)
        {
            if(!isdigit(expression[i]))
            {
                isNumber = false;
                break;
            }
            number = number*10+(expression[i]-'0');
        }
        if(isNumber)
        {
            res.push_back(number);
            return res;
        }
        for(int i = left; i <= right; ++i)
        {
            // 遇到运算符，是我们切分表达式的标准
            if(!isdigit(expression[i]))
            {
                // 使用数组保存两侧子表达式的所有可能结果
                // 计算运算符左侧的部分，长度为 i-left+1 
                // 以及运算符右侧的部分，长度为 right-(i+1)+1 = right-i
                vector<int> leftRes = dfs(left, i-1);
                vector<int> rightRes = dfs(i+1, right);
                // 得到两侧子表达式的可能结果后，我们只需要进行组合即可
                // 根据当前运算符，对两个子表达式的所有结果进行组合
                for(int j = 0; j < leftRes.size(); ++j)
                {
                    for(int k = 0; k < rightRes.size(); ++k)
                    {
                        switch(expression[i]) {
                            case '+':
                            res.push_back(leftRes[j]+rightRes[k]);
                            break;
                            case '-':
                            res.push_back(leftRes[j]-rightRes[k]);
                            break;
                            case '*':
                            res.push_back(leftRes[j]*rightRes[k]);
                            break;
                            case '/':
                            res.push_back(leftRes[j]/rightRes[k]);
                            break;
                        }
                    }
                }
            }
        }
        // 组合完成后，我们就可以返回结果数组了
        return res;
    };
    // 对回调函数进行调用即可
    int n = expression.size();
    return dfs(0, n-1);
}

// 第二版：DFS + 记忆化加速
vector<int> diffWaysToCompute(string expression)
{
    // 从上面的搜索过程，我们不难发现会做出多次重复的子表达式计算，所以我们可以引入记忆化数组来存储运算结果
    // 考虑：需要记忆的数组具体维度是多少？
    // 简单画一画表达式的例子，可以看出，假设有 m 个运算符，那么应该存储 m+1 个分立的值，由这 m+1 个分立的值组合出不同的子表达式
    // 那么我们需要先进行一轮预处理，计算出 expression 中有多少个运算符
    int n = expression.size();
    // 注意：为了使用我们的记忆化数组，需要对递归函数的 left, right 参数进行适配，因为这里 left 和 right 在我们第一版的代码中代表的是 expression 中的下标，而不是操作符的有序序号
    // 此时我们可以在预处理的时候对表达式进行信息提取，取出所有运算数和运算符存为一个整数数组
    vector<int> optrs;
    int num = 0;
    for(int i = 0; i < n; ++i)
    {
        if(!isdigit(expression[i]))
        {
            optrs.push_back(num);
            optrs.push_back(expression[i]);
            num = 0;
        }
        else
        {
            num = num*10+(expression[i]-'0');
        }
    }
    optrs.push_back(num);
    // 初始化记忆化数组
    vector<vector<vector<int>>> memo(optrs.size(), vector<vector<int>>(optrs.size(), vector<int>()));
    // 这里，我们修订一下 dfs 函数的定义，left 和 right 代表的是 optrs 运算符数组中的对应下标
    function<vector<int>(int, int)> dfs = [&](int left, int right) -> vector<int> 
    {
        // 先检查记忆化数组，如果已经算过了，直接返回记忆的内容
        if(!memo[left][right].empty())
        {
            return memo[left][right];
        }
        // 另一个情况是，当前子表达式是一个单独的数字
        if(left == right)
        {
            // 返回运算数数组中记录的数据即可
            return {optrs[left]};
        }
        // 首先我们初始化一个结果数组，用于保存所有拆分方案的计算结果
        vector<int> res;
        // 逐个按运算符分割 expression 成两个子表达式，进行递归计算
        for(int i = left; i < right; i += 2)
        {
            // 计算左右两侧的子表达式
            vector<int> leftRes = dfs(left, i);
            vector<int> rightRes = dfs(i+2, right);
            // 依旧是二维遍历
            for(int j = 0; j < leftRes.size(); ++j)
            {
                for(int k = 0; k < rightRes.size(); ++k)
                {
                    switch(optrs[i+1]) 
                    {
                        case '+':
                        res.push_back(leftRes[j]+rightRes[k]);
                        break;
                        case '-':
                        res.push_back(leftRes[j]-rightRes[k]);
                        break;
                        case '*':
                        res.push_back(leftRes[j]*rightRes[k]);
                        break;
                        case '/':
                        res.push_back(leftRes[j]/rightRes[k]);
                        break;
                    }
                }
            }
        }
        // 组合完成后，我们就可以返回结果数组了
        // 进行记忆化
        memo[left][right] = res;
        return memo[left][right];
    };
    return dfs(0, optrs.size()-1);
}