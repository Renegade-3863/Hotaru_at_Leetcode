#include "Solution.h"

vector<string> Leetcode201_300::Solution::addOperators(string num, int target)
{
    // 题目要求我们找出当前数字串组合出 target 的所有可能运算式，很显然需要用回溯方法
    // 考虑回溯的基本过程
    // 我们可以定义一个过程变量 path，用来记录当前已经检出的表达式
    // void backtrack(idx, subTarget)
    // 上面的函数用于检出 num 从 idx 开始向后，可以找出的运算和为 target 的表达式
    // path 用于记录任意一条过程中的表达式
    string path = "";
    // tot 用于记录过程中的结果，即 path 同步的结果
    long long tot = 0;
    // res 用于记录所有合法的表达式
    vector<string> res;
    int n = num.size();
    // prev 用于记录截至上一个非乘号的运算数的运算结果，prevC 用于记录上一个非乘号的运算符
    // 之所以要这样记录，是因为我们需要把每一段完全由乘号连接起来的子表达式视作一个独立的数据，这个数据在新的乘号到来的时候需要被剔除更新
    function<void(int, long long, char)> backtrack = [&](int idx, long long prev, char prevC)
    {
        // 如何判断递归结束条件？
        // 似乎可以通过 idx 是否等于 num.size() 来进行判断
        if(idx == n)
        {
            // 此时，如果我们找到了一条计算出 target 的合法路径，添加到 res 数组中即可
            if(tot == target)
            {
                res.push_back(path);
            }
            return;
        }
        // 一般情况
        // 根据取到的 idx 参数，决定下一步要如何继续深入
        // 基本的步骤是，先取数，选符号进行计算，再递归深入
        int number = 0;
        for(int i = idx; i < n; ++i)
        {
            // 防止前导零
            if(i > idx && number == 0)
            {
                break;
            }
            // 第一步：截取一个数出来
            number = number*10+(num[i]-'0');
            string tmp = to_string(number);
            // 将这个数和 sum 进行某种计算
            // 检查是否是一个合理的下一步结果
            
            // '+'、'-' 号不需要任何更改，因为它们本身就是最低优先级的运算符

            // 先尝试 "+" 号
            // 先更新 path 和 tot
            tot += number;
            path += "+";
            path += tmp;
            // 递归深入
            backtrack(i+1, number, '+');
            // 回溯
            // 经考察，这里的数字不用删去，我们实际上只需要对符号和结果进行修改即可
            // 修改 tot 结果
            tot -= number;

            // 再尝试 "-" 号
            // 更新 tot
            tot -= number;
            // 修改符号
            path[path.size()-tmp.size()-1] = '-';
            // 递归深入
            backtrack(i+1, number, '-');
            // 回溯
            // 修改 tot 结果
            tot += number;

            // 对 '*' 号需要分情况讨论
            // 1. 如果前面也是个乘号，那么我们显然不需要任何其它处理，直接乘上去就可以了
            // 2. 如果前面是个 '+' 号或者 '-' 号，那么我们还需要把这个 prev 值先丢掉，再根据前面符号加上 prev*number 或者减去 prev*number

            // 最后尝试 "*" 号
            // 更新 tot
            int rec = tot;
            if(prevC == '+')
            {
                tot -= prev;
                tot += prev*number;
            }
            else if(prevC == '-')
            {
                tot += prev;
                tot -= prev*number;
            }
            else
            {
                tot *= number;
            }
            // 修改符号
            path[path.size()-tmp.size()-1] = '*';
            // 递归深入
            backtrack(i+1, prev*number, prevC);
            // 回溯
            // 修改 tot 结果
            tot = rec;
            // 结束时还需要把 path 进行复原
            path = path.substr(0, path.size()-tmp.size());
            // 移除符号
            path.pop_back();
        }
    };
    // 枚举第一个数，之后才能进入回溯
    for(int i = 0; i < n; ++i)
    {
        // 还需要注意，任何一个参与计算的数值都不能有前导零，这一点如果意识到了很好处理，但是关键是容易意识不到。。。
        if(i > 0 && tot == 0)
        {
            break;
        }
        tot = tot*10+(num[i]-'0');
        path = to_string(tot);
        // 用空格字符表示前面没有任何运算符，此时后面的运算符和前面有个 '+'、'-' 号的情况时一样的
        backtrack(i+1, tot, ' ');
    }
    return res; 
}

// 当然，本题还有一个更暴力的算法：回溯找出所有可能的表达式，之后利用运算式求值的算法对它求值，结果为 target 的添加到结果数组中
// 不过比较麻烦，就不写了。。。有兴趣的可以自己尝试，难度不大，缝合怪而已。。。