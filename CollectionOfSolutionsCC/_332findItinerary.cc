#include "Solution.h"

vector<string> Leetcode301_400::Solution::findItinerary(vector<vector<string>>& tickets)
{
    // 经典的欧拉回路问题，我们需要找出一张图中可以遍历完所有边而路径本身不重复经过同一条边的可行解
    // 这种题目最简单易懂的方法是，我们暴力回溯，直到找出一个可以遍历所有边而不重复的路径
    // 这样的暴力方法需要我们先预处理出一个站-票图的临界表
    // 第一步：预处理邻接表
    // int n = tickets.size();
    // 用哈希表来存储邻接表，因为我们的键是字符串
    // 值存储对应要用有序哈希表进行存储，因为我们要找的是字典序最小的答案
    unordered_map<string, map<string, int>> adjList;
    // 记录票数
    int cnt = 0;
    for(const auto& ticket : tickets)
    {
        // 记录到哈希表中
        ++adjList[ticket[0]][ticket[1]];
        ++cnt;
    }
    // 后面的操作我们就只用这个 adjList 即可，tickets 数组就用不到了
    // 定义一个回溯的函数体和一个路径数组 path 
    // 一个变量记录我们是否已经找到了最终结果
    bool found = false;
    vector<string> path;
    // 记录已经用过的票(边)数
    int num = 0;
    function<void(string)> backtrack = [&](string cur)
    {
        // cur 代表的是我们这个时候所在的站点
        // 回溯结束条件是，我们刚好用完了所有票 (边)
        if(num == cnt)
        {
            found = true;
            return;
        }
        // 一般情况：我们遍历当前站出发的所有票，如果这张票之前没用过，我们就进行尝试
        // 对于每个相邻站点，检查其剩余票数
        for(const auto& nxt : adjList[cur])
        {
            if(adjList[cur][nxt.first] > 0)
            {
                ++num;
                path.push_back(nxt.first);
                --adjList[cur][nxt.first];
                backtrack(nxt.first);
                // 如果找到了一条可行路径，我们就不用回溯了，直接截断返回即可，如果要找出所有可行路径，那么删掉这部分即可
                if(found)
                {
                    return;
                }
                ++adjList[cur][nxt.first];
                path.pop_back();
                --num;
            }
        }
    };
    // 调用函数并返回结果即可
    path.push_back("JFK");
    backtrack("JFK");
    return path;
}