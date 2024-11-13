#include "Solution.h"

struct myPair
{
public:
    myPair(string _dividend, string _divisor) : dividend(_dividend), divisor(_divisor) {}
    string dividend;
    string divisor;
};
struct hashFunc 
{
    size_t operator() (const myPair& p) const
    {
        return hash<string>()(p.dividend) ^ hash<string>()(p.divisor);
    }
};
struct equalFunc
{
    bool operator() (const myPair& a, const myPair& b) const
    {
        return a.dividend == b.dividend && a.divisor == b.divisor;
    }
};
vector<double> Leetcode301_400::Solution::calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries)
{
    // 很全面的一道带细节的图论题目
    // 我们需要经过建图 -> 遍历图 -> 输出结果的一整套流程，很考验设计能力和逻辑能力
    // 我们首先把所有 "已知条件" 保存到一张表里面
    // 这张表以邻接表的形式保存是最好的
    // 注意，我们保存的格式是：被除数 -> {除数，结果} 的形式，所以下面的哈希表保存的值需要是一个 pair 的数组
    unordered_map<string, vector<pair<string, double>>> adjList;
    // 我们利用 equations 数组和 values 数组先把 adjList 数组处理出来
    // 后面再考虑 queries 的问题
    int n = equations.size();
    // 理论上说，equations 和 values 数组大小应该是一样的，所以可以同步遍历
    for(int i = 0; i < n; ++i)
    {
        double anti = 1/values[i];
        adjList[equations[i][0]].push_back(make_pair<string&, double&>(equations[i][1], values[i]));
        adjList[equations[i][1]].push_back(make_pair<string&, double&>(equations[i][0], anti));
    }
    // 记录好结果后，我们要做的就是对这张图进行搜索了
    // 对于每个查询 query，我们需要先检查被除数和除数，如果被除数等于除数，那么很明显我们就可以直接得出结果 1.0
    vector<double> res;
    // 对 queries 数组进行遍历，有需要的进行深搜
    // 定义深搜函数，处理 dividend/divisor 的除法
    // 记忆化表
    unordered_map<myPair, double, hashFunc, equalFunc> memo;
    // 用于深搜时防止反向运动，导致程序崩溃
    unordered_set<string> visited;
    function<double(string, string)> dfs = [&](string dividend, string divisor) -> double
    {
        // 注意：题目说明可能会出现不合法的被除数/除数，所以我们提前检查被除数/除数是否都存在于邻接表中，如果任何一个不存在，我们都可以直接返回 -1.0
        if(adjList.find(dividend) == adjList.end() || adjList.find(divisor) == adjList.end())
        {
            memo[myPair(dividend, divisor)] = -1.0; 
            return -1.0;
        }
        // 基本情况：如果 dividend == divisor
        // 直接返回 1.0 即可
        if(dividend == divisor)
        {
            return 1.0;
        }
        if(memo.find(myPair(dividend, divisor)) != memo.end())
        {
            return memo[myPair(dividend, divisor)];
        }
        // 否则，需要遍历这个被除数的列表，找出下一轮的被除数，记录这一次操作累加到结果中的值
        for(const auto& nxt : adjList[dividend])
        {
            // 提取出值
            double val = nxt.second;
            // 根据 nxt.first 进一步递归
            // 计算出下一轮的结果
            // 根据返回值确定下一步操作
            if(visited.find(nxt.first) != visited.end())
            {
                continue;
            }
            visited.insert(nxt.first);
            double ret = dfs(nxt.first, divisor);
            visited.erase(nxt.first);
            // 如果返回值非 -1.0，那么说明我们的计算有结果，那么组合结果即可
            if(ret != -1.0)
            {
                memo[myPair(dividend, divisor)] = ret * val;
                return ret * val;
            }
            // 否则，跳过这一轮，检查下一个 "下一跳" 被除数
        }
        // 检查过了所有可能的下一跳，都没有找到合适的结果，说明我们这个表达式 "不可解"
        // 返回 -1.0 即可
        memo[myPair(dividend, divisor)] = -1.0;
        return -1.0;
    };
    // 可以预见，我们上面的运算过程会有很多重复的计算，所以我们可以直接引入记忆化信息表
    // 对每一个查询调用上面的运算函数即可
    for(const auto& query : queries)
    {
        // 每一轮检查都要清空 memo 记忆化数组，防止前面搜索出来的一些路径影响到本次计算
        memo.clear();
        visited.insert(query[0]);
        res.push_back(dfs(query[0], query[1]));
        visited.erase(query[0]);
    }
    return res;
}