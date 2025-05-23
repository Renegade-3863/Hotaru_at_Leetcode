#include "Solution.h"

int Leetcode501_600::Soltuion::findIntegers(int n)
{
    // 比较典型的数位 DP 类问题，但也不简单，为数不多的难点不在 DP 递推设计上的 DP 类问题
    // 我们简单考虑一下如何设计递推关系
    // 假设定义下面的 dfs 子问题：
    // dfs(i, high) 代表：
    // 二进制表示长度为 i，并且最高位 (high == true, 为 1; high == false, 为 0)，的所有不含连续 1 的非负整数个数
    // 那么我们可以这样进行递推：
    // dfs(i, false) = dfs(i-1, true)+dfs(i-1, false)，也就是说，我们可以考虑从二进制表示法少一位，同时最高位是 1，或者不是 1 点两种情况
    // 最高位填一个 0 来满足要求
    // dfs(i, true) = dfs(i-1, false)，如果我们要求最高位留一个 1，那么我们就只能在少一位的情况下，保证最高位为 0
    // 那么，最后的结果就应该是 
    // dfs(b(n), true)+dfs(b(n), false)
    // b(n) 代表的是，n 表示需要的二进制位数
    // 注意：因为 n 可能并不是一个 11...1 形式的数，所以我们在计算时需要额外考虑那些超过了 n 的结果 (只在求解的 i 等于 b(n) 的时候需要注意)
    // 我们用一个全 1 的掩码即可方便地求解 b(n)
    int bn = 0, mask = 0xffffffff;
    // 通过 mask 掩码和 n 进行按位与，我们可以检查现在 mask 规定取的这些位中是否还有剩余的 1，如果有，说明现在这 b(n) 个位还不够表示 n
    while(mask & n)
    {
        ++bn;
        // mask 左移一位，最低位就会被自动补零，这样就完成了 1111 -> 1110 的转化
        mask = (mask<<1);
    }
    // 处理完成，我们可以按照 bn 的值开始进行 dfs 处理了
    // 使用一个记忆化表记录每种情况对应的结果
    vector<vector<int>> memo(33, vector<int>(2, -1));
    function<int(int, bool)> dfs = [&](int i, bool high) -> int
    {
        // 首先，我们规定一个边界情况，i == 1
        // 此时只有一位二进制位，我们根据 high 的 true 或 false 进行返回即可
        if(i == 1)
        {
            memo[i][high] = 1;
            return 1;
        }
        if(memo[i][high] != -1)
        {
            return memo[i][high];
        }
        // 其它情况下，我们考虑利用上面的关系进行递推即可
        if(high)
        {
            memo[i][high] = dfs(i-1, false);
            return memo[i][high];
        }
        memo[i][high] = dfs(i-1, false)+dfs(i-1, true);
        return memo[i][high];
    };
    dfs(32, true);
    dfs(32, false);
    // 回到题目，本题要求我们找出 "[0, n] 范围中，二进制数位上不包含连续 1 的数的个数"
    // 所以单纯计算出上面的这些子问题，并不能直接得到我们最终的答案
    // 所以，我们还需要一种机制，来累加出最后 "不大于 n 的非负数中，不包含连续 1 的数的个数"
    // 这可以通过检查 n 本身的二进制表示来完成
    // 我们以这样的假设来完成整体的检查：
    // 假设当前位 cur 前面的所有二进制位都按照 n 原本的值进行填充
    // 当前部分可以累加进答案的结果有多少
    // 很明显是 cur == 0 的部分可以累加进答案中
    // 而 cur == 1 的部分，因为在当前 cur 的情况下，我们没法明确知道 memo 中记录的对应当前位为 1 的所有结果是否都能累加进答案，所以我们不能在这一步进行累加
    // 不过很神奇的是，我们按照这样的步骤逐步累加 cur == 0 的结果，就恰好计入了所有 cur == 1 的结果 (这一步稍微有点难理解，需要自己进行一些思考)
    // 在这个累加的过程中，如果 n 的二进制表示本身就出现了连续的 1，那么我们可以直接累加 cur 对应为 0 的结果，退出检查循环了
    // 因为比 n 小的值，对应 cur 位一定不能是 1。而我们的总体循环其实是用来找 cur 为 1 的后续结果的
    // 我们前面已经检出了 n 的二进制表示的总长度
    // 这里根据这个总长度 bn 来对 n 进行检查即可
    // 从最高到最低位进行计算
    int ans = 0, pre = -1;
    for( ; bn > 0; --bn)
    {
        // 取出 n 的当前位
        int cur = (n>>(bn-1))&1;
        // 根据 cur 为 0 或 1，决定要怎么使用 memo 中的值
        if(cur)
        {
            // 如果 cur 为 1，那么我们可以累加 memo[cur][0];
            ans += memo[bn][0];
            // 遇到了连续的 1，那么我们就可以退出检查了，后续的 cur == 1 的情况都不用检查了
            if(pre == cur)
            {
                break;
            }
        }
        pre = cur;
        // 如果到最后都没有因为出现连续的 1 而退出循环，我们还需要加上 n 本身这个合法的结果
        if(bn == 1)
        {
            ++ans;
        }
    }
    return ans;
}