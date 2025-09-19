#include <iostream>

class Solution {
public:
    int maxProfit(vector<int>& prices)
    {
        // 这道题用不到动态规划
        // 因为我们只能挑一天卖出股票，所以我们只需要计算哪一天卖出获得的利润最高即可
        // 我们可以用差分的方法来处理这个问题
        // 定义一个“最小值”，用来记录当前遍历到的所有天中，股票价格最低的那一天的价格
        // 之后，如果当前遍历到的这一天的股票价格高于这个前面价格最低的日期，我们就尝试更新最大的利润
        // 同时也要更新这个“最小值”
        // 这样，最后就可以知道我们的最大利润值
        // 注意，“最小值” 不能低于 0
        // 初始化 “最小值” 为 prices[0] 的值
        int res = 0, minimum = prices[0], n = prices.size();
        for(int i = 1; i < n; ++i)
        {
            if(prices[i] > minimum)
            {
                // 尝试对 res 进行更新
                res = max(res, prices[i]-minimum);
            }
            else if(prices[i] < minimum)
            {
                // 更新 minimum 的值，但不对 res 做任何更新
                minimum = prices[i];
            }
        }
        return res;
    }
};