#include "Solution.h"

// 下面这个解法只是一个非常 dummy 的代码尸山，如果有闲心，想用方法进行简化，这里表示非常赞同 (bushi)
bool Leetcode601_700::Soltuion::judgePoint24(vector<int>& cards)
{
    // 基本思想不难，就是维护 "手上现有的数值集合" 这一个状态
    // 从每一个状态出发，尝试最终构造出结果 24 即可
    // 定义下面的 dfs 函数：
    // bool dfs(vector<int>& status) 
    // 决定用当前 status 的数据能否通过使用 '+', '-', '*', '/' 来构造出最后的结果
    // 不用考虑括号，它影响的只是运算的顺序，而不是结果
    // 那么对于一个已有的 status，我们可以从中随机取出两个数值
    // 对它们尝试应用上述四种运算的其中一种
    // 直到 status 中只有一个元素，如果它是 24，那么我们直接返回 true 即可，此时不用任何处理就得到了结果
    function<bool(vector<double>&)> dfs = [&](vector<double>& status) -> bool
    {
        // 递归结束情况
        int n = status.size();
        if(n == 1)
        {
            // cout << status[0] << endl;
            // 一点来自 double 精度的小小震撼 (bushi)
            return abs(status[0]-24) < 0.0000001;
        }
        // 一般情况，考虑对 status 中的元素进行组合，保存到 nxtStatus 数组中传下去
        vector<double> nxtStatus;
        // 我们只考虑组合，所以 j 枚举起点从 i+1 开始即可
        for(int i = 0; i < n; ++i)
        {
            for(int j = i+1; j < n; ++j)
            {
                double res = 0.0;
                // 清空 nxtStatus，重新填数
                nxtStatus.clear();
                for(int x = 0; x < n; ++x)
                {
                    if(x != i && x != j)
                    {
                        nxtStatus.push_back(status[x]);
                    }
                }
                // 先考虑 '+' 号
                res = status[i]+status[j];
                // for(int k = 0; k < status.size(); ++k)
                // {
                //     cout << status[k] << " ";
                // }
                // cout << endl;
                // 添加到 nxtStatus 中
                nxtStatus.push_back(res);
                if(dfs(nxtStatus))
                {
                    return true;
                }
                // 弹出结果，换下一个运算符计算
                nxtStatus.pop_back();
                res = status[i]-status[j];
                nxtStatus.push_back(res);
                if(dfs(nxtStatus))
                {
                    return true;
                }
                nxtStatus.pop_back();
                res = status[j]-status[i];
                nxtStatus.push_back(res);
                if(dfs(nxtStatus))
                {
                    return true;
                }
                nxtStatus.pop_back();
                res = status[i]*status[j];
                nxtStatus.push_back(res);
                if(dfs(nxtStatus))
                {
                    return true;
                }
                nxtStatus.pop_back();
                // 注意避免除 0 的情况
                if(status[j] != 0)
                {
                    res = status[i]/status[j];
                    nxtStatus.push_back(res);
                    if(dfs(nxtStatus))
                    {
                        return true;
                    }
                    nxtStatus.pop_back();
                }
                if(status[i] != 0)
                {
                    res = status[j]/status[i];
                    nxtStatus.push_back(res);
                    if(dfs(nxtStatus))
                    {
                        return true;
                    }
                }
            }
        }
        // 都试过了，没有拿到可行结果，返回 false 即可
        return false;
    };
    vector<double> board;
    for(const auto& card : cards)
    {
        board.push_back(double(card));
    }
    return dfs(board);
}