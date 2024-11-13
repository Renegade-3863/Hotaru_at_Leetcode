#include "Solution.h"

int Leetcode301_400::Solution::superPow(int a, vector<int>& b)
{
    // 很经典的递归类问题，我们从下面的角度切入思考：
    // 假设我们要求的是 a^(b1b2b3...bk)
    // 那么我们可以分别算：a^(b100000)，a^(b20000)，a^(b3000)...
    // 之后把这些数据乘起来再对 1337 取模
    // 根据我们在数论课上学过的内容：
    // (a*b*c*d*...) mod M == ((a mod M) * (b mod M) * (c mod M) ... ) mod M
    // 所以我们为了避免最终的计算结果溢出，我们完全可以先对每一个结果取模，再计算最后的结果
    // 之后，我们考虑一个细节问题：
    // 如何计算 a^(300)？
    // 我们会算 a^3，但是后面还有两个零
    // 可以这样做，我们把这个 100 提取出来，只算 a^3，之后再算这个值的100次方
    // 实际上，我们可以考虑这样优化我们的运算过程：
    // 例如我们要算 23^(2394)
    // 那么可以转化成 23^((239)*10+4) = (23^(239))^10 * 23^4
    // 左边 23^(239) 这个问题就是一个更小的子问题，我们可以递归求解答案
    // 定义递归函数体，求解 a^({subB})
    function<int(int, vector<int>&)> dfs = [&](int a, vector<int>& subB) -> int
    {
        // 递归结束点：subB.size() == 1
        // 此时我们可以直接计算结果并取模返回结果
        int res = 1;
        if(subB.size() == 1)
        {
            while(subB[0]--)
            {
                res = (res * (a % 1337)) % 1337;
            }
            return res % 1337;
        }
        // 我们分离出最后一位的数字，计算 a^(subB[subB.size()-1])
        int last = subB[subB.size()-1];
        while(last--)
        {
            res = (res * (a % 1337)) % 1337;
        }
        // 之后递归计算前面的部分
        subB.pop_back();
        int pre = dfs(a, subB);
        int begin = pre;
        // 计算 pre^10
        for(int i = 0; i < 9; ++i)
        {
            pre = (pre * begin) % 1337;
        }
        return pre * res % 1337;
    };
    return dfs(a, b);
}