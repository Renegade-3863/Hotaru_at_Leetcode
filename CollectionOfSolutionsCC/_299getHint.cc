#include "Solution.h"

string Leetcode201_300::Solution::getHint(string secret, string guess)
{
    // 字符串模拟题，按要求做就行，这种题不考验逻辑能力和智商，考验代码能力
    // 初步考察题目给出的案例，可以得出我们需要 "secret 中所有字符出现的次数" 这一信息
    // 我们先预处理获取一下这个信息
    unordered_map<char, int> cnts;
    int n = secret.size();
    for(int i = 0; i < n; ++i)
    {
        ++cnts[secret[i]];
    }
    // 循环结束，我们拿到了所有字符出现的次数
    // 下面开始正式的对 guess 的检查
    // 初始化两个变量，一个记录 Bulls 个数，一个记录 Cows 个数
    // 注意一点问题：我们必须分两轮对 bulls 和 cows 分别检查
    // 原因如下：
    // 考虑这样的例子：
    // secret == 1122, guess == 1222
    // 那么此时我们先碰到了 1 != 2 这对不等关系
    // 此时我们检查 cnts 表，发现还有两个 "可用" 的2
    // 而实际上，这两个2都是 bulls 匹配会用到的 2，也就是说，实际上这个时候可用的 2 应该为0
    // 我们必须避免这种错误情况的发生，办法是像下面这样，先检查完所有的 bulls，再检查 cows
    int bulls = 0, cows = 0;
    for(int i = 0; i < n; ++i)
    {
        // guess[i] 和 secret[i] 无非有两种关系
        // 1. guess[i] == secret[i]
        if(guess[i] == secret[i])
        {
            // 此时我们可以简单地给 Bulls 个数+1
            ++bulls;
            --cnts[guess[i]];
        }
    }
    for(int i = 0; i < n; ++i)
    {
        // 2. guess[i] != secret[i]
        if(guess[i] != secret[i])
        {
            if(cnts.find(guess[i]) != cnts.end() && cnts[guess[i]] > 0)
            {
                ++cows;
                --cnts[guess[i]];
            }
        }
    }
    // 检查完成，我们只需要根据得到的 bulls 和 cows 变量构造答案字符串即可
    return to_string(bulls)+"A"+to_string(cows)+"B";
}