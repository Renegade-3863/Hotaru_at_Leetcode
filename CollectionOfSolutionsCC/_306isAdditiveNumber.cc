#include "Solution.h"

bool Leetcode301_400::Solution::isAdditiveNumber(string num)
{
    // 针对题目给出的附加要求，这里先猜想是要用大数运算进行优化
    // 不过先用传统的整数加法写个大框出来好了。。。
    // 注意到：只要明确了开头的两个数字，之后的序列就可以通过这两个开头数字确认出来
    // 所以我们只需要枚举开头两个数，并检查这种方式确认出来的序列是否等于原序列即可
    // 设定一个确认函数
    // 三个参数分别为 [idx1, idx2-1], [idx2, idx3] -> 代表两个构成当前序列的数字
    // 返回两个用字符串表示的整数相加的和
    // 因为本题不涉及负数加法，所以我们只考虑非负数加法即可
    // 全局回溯变量，用于记录当前检查过了几个加数
    int count = 0;
    function<string(const string&, const string&)> addition = [&](const string& num1, const string& num2)
    {
        int m = num1.size(), n = num2.size();
        // 回忆：两个大数求和，结果的位数最大为 max(m, n)+1 位
        // 用一个数组记录所有中间值
        vector<int> res(max(m, n)+1, 0);
        // 按位模拟加法运算
        int i = m-1, j = n-1, k = res.size()-1;
        while(i >= 0 || j >= 0)
        {
            int adder1 = i >= 0 ? (num1[i--]-'0') : 0;
            int adder2 = j >= 0 ? (num2[j--]-'0') : 0;
            // 插入结果数组头部
            res[k--] = adder1+adder2;
        }
        // 结束后，再对 res 数组做一轮处理即可
        for(int i = res.size()-1; i >= 1; --i)
        {
            // 对于最前面的位，我们不需要额外处理了
            res[i-1] += res[i]/10;
            res[i] %= 10;
        }
        string ret = "";
        // 之后把 res 中的数字转拼成字符串返回结果即可
        // 不过拼接的时候需要对第一位额外进行一下判断
        for(int i = 0; i < res.size(); ++i)
        {
            if(i == 0 && res[i] == 0)
            {
                // 前导零不能记录下来
                continue;
            }
            ret += to_string(res[i]);
        }
        return ret;
    };
    function<bool(int, int, int)> isValid = [&](int idx1, int idx2, int idx3) -> bool
    {
        // 算了，还是写一下大数加法的函数吧，反正也不难
        // 递归的结束条件：idx3 == num.size()-1
        // 此时我们找到了一个合法的序列，返回 true 即可
        if(idx3 == num.size()-1)
        {
            return count >= 3 ? true : false;
        }
        // 否则，我们先把当前两个数求和，利用上面写好的大数加法函数
        string num1 = num.substr(idx1, idx2-idx1);
        string num2 = num.substr(idx2, idx3-idx2+1);
        // 求和
        string sum = addition(num1, num2);
        // 向后检查一个数，看是否是 sum 这个值
        string check = num.substr(idx3+1, sum.size());
        // 等于，那么我们可以继续深入
        bool ret = false;
        // 至于递归过程中数字的前导零，我们实际上在大数加法的函数内部就已经避免了这个问题，不了解的可以去看一下上面的函数操作
        if(check == sum)
        {
            // 递归 count 变量
            ++count;
            ret = isValid(idx2, idx3+1, idx3+sum.size());
            // 回溯 count 变量
            --count;
        }
        // 否则，直接返回不合法即可
        return ret;
    };
    // 我们需要在外边枚举所有可能的前两个数字对
    for(int i = 0; i < num.size()-1; ++i)
    {
        for(int j = i+1; j < num.size(); ++j)
        {
            string num1 = num.substr(0, i+1);
            string num2 = num.substr(i+1, j-i);
            // 注意，题目不允许含前导零的数字参与计算，所以这里我们需要避免枚举这样的初始数字
            // 解释一下：因为第一个数本身是固定从开头开始的，所以只要我们找到了一个开头是零，长度大于1的数，那么就可以断定后面不可能再有不含前导零的 num1 了，所以此时直接返回 false 即可
            if(num1.size() > 1 && num1[0] == '0')
            {
                return false;
            }
            // 而 num2，由于开头不固定，即使某一次出现了前导零，后面这个零也可以被并入 num1，所以我们只能退出当前内部循环
            if(num2.size() > 1 && num2[0] == '0')
            {
                break;
            }
            // 重置 count 变量
            count = 2;
            if(isValid(0, i+1, j))
            {
                return true;
            }
        }
    }
    return false;
}