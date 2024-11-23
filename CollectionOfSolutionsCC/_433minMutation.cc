#include "Solution.h"

bool oneDiff(const string& str1, const string& str2)
{
    // 检查两个字符串之间是否只想差了一个字母
    if(str1.size() != str2.size())
    {
        return false;
    }
    int n = str1.size();
    // 记录同位置上，不同字母的个数
    int cnt = 0;
    for(int i = 0; i < n; ++i)
    {
        if(str1[i] != str2[i])
        {
            if(++cnt > 1)
            {
                break;
            }
        }
    }
    // 如果 cnt != 1，那么就可以返回 false
    return cnt == 1;
}

int Leetcode401_500::Solution::minMutation(string startGene, string endGene, vector<string>& bank)
{
    // 经典的 BFS 广搜类问题
    // 我们考虑先建图再搜索的方法
    // 用邻接表的方式来建立这张图，有边存在的规则是
    // Gene1 和 Gene2 之间只差一个字符
    // 之后我们需要做的就是一轮对于无向图的 BFS 遍历，直到找到 startGene 到 endGene 之间的最短修改路径为止
    // 第一步：建图：
    unordered_map<string, unordered_set<string>> adjList;
    // 先检索一遍 bank 数组，如果没发现 endGene，那么我们直接返回 -1 即可
    // 同时，也可以检查出 startGene 是否存在于 bank 中
    bool startExist = false, endExist = false;
    for(const auto& word : bank)
    {
        if(word == startGene)
        {
            startExist = true;
        }
        if(word == endGene)
        {
            endExist = true;
        }
    }
    if(!endExist)
    {
        return -1;
    }
    // 为了后面的逻辑统一性，我们把 startGene 也添加到 bank 中来
    if(!startExist)
    {
        bank.push_back(startGene);
    }
    int n = bank.size();
    for(int i = 0; i < n; ++i)
    {
        // 对于每个单词，我们只需要检查它后面的所有单词即可，在设置边关系的时候是双向的
        for(int j = i+1; j < n; ++j)
        {
            // 这里写一个调用函数，用来检查两个单词之间是否只差了1个字母
            if(oneDiff(bank[i], bank[j]))
            {
                // 如果只差了1个字母，那么二者之间就可以互相记录边关系
                adjList[bank[i]].insert(bank[j]);
                adjList[bank[j]].insert(bank[i]);
            }
        }
    }
    // 邻接表处理完成，我们接下来就可以进行实际的 BFS 遍历了
    // 首先，我们把 startGene 记录到遍历队列中
    queue<string> q;
    q.push(startGene);
    // 用于记录 BFS 访问过的结点，防止回头陷入死循环
    unordered_set<string> visited;
    visited.insert(startGene);
    int steps = 0;
    while(!q.empty())
    {
        int n = q.size();
        // 按层进行检查，因为我们要找的是 "步数"
        // 每一层都要多走一步
        ++steps;
        for(int i = 0; i < n; ++i)
        {
            // 第一步：取出队头的字符串
            string cur = q.front();
            q.pop();
            // 检查当前字符串的所有邻居结点
            for(const auto& adj : adjList[cur])
            {
                // 如果这个邻居就是 endGene 本身，那么我们就可以直接返回 steps 了
                if(adj == endGene)
                {
                    return steps;
                }
                if(visited.find(adj) == visited.end())
                {
                    // 邻居没访问过，那么我们可以保存它以便下一轮检查
                    q.push(adj);
                    // 标记这个字符串为 "已添加"，这样可以防止重复添加
                    visited.insert(adj);
                }
            }
        }
    }
    // 如果整张图都遍历完了，没有返回，就说明没有合法的路径，更别提最短路径了
    // 我们返回 -1 即可
    return -1;
}
