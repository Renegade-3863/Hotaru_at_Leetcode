#include "Solution.h"

int Leetcode101_200;:Solution::ladderLength(string beginWord, string endWord, vector<string>& wordList)
{
    // 经历了 126 题的洗礼，相信大家对这道原题都已经觉得小儿科了，可以直接套用上一题的 BFS + DFS 策略解决
    // 这里考虑一下，如果我们事先没有做过 126 题那种优化
    // 本题第一眼，其实还是会想到单纯的 BFS(毕竟要求计算的是最短距离，很难不第一时间想到 BFS)
    // 考虑直接对这些单词进行建图
    // 在建图的过程中计算出最短的单词距离即可
    // 记录一个全局的距离值
    // 预设为 1，如果存在这样的路径，这时初始的 steps 就代表了 beginWord 这一个单词
    int steps = 1;
    // 还是需要一个高效查询 wordList 中单词的哈希表
    // 我们进行一下转储
    unordered_set<string> memo(wordList.begin(), wordList.end());
    // 注意到我们这里实际上并不用记录层号本身，实际编程的时候发现层号用不上，只要记录是否前面访问过即可
    unordered_set<string> visited;
    // 如果 endWord 甚至不再 wordList 中，我们就可以直接返回了
    if(memo.find(endWord) == memo.end())
    {
        return 0;
    }
    // 用来进行 BFS 的队列
    queue<string> q;
    q.push(beginWord);
    // 记录 beginWord 所在的层为1号
    visited.insert(beginWord);
    bool valid = false;
    while(!q.empty() && !valid)
    {
        // 存储当前队列(层)的结点个数
        int n = q.size();
        // 往下走一步
        ++steps;
        for(int i = 0; i < n; ++i)
        {
            // 检查所有可能的下一跳字符串
            string cur = q.front();
            q.pop();
            for(int j = 0; j < cur.size(); ++j)
            {
                // 避免污染原字符串
                string tmp = cur;
                // 对于每个字符，尝试进行所有可能的变换
                for(char c = 'a'; c <= 'z'; ++c)
                {
                    // 只有不同的字符，我们才尝试进行变换
                    if(c != cur[j])
                    {
                        tmp[j] = c;
                        if(memo.find(tmp) != memo.end())
                        {
                            // 尝试添加到队列中
                            // 注意，这里的思路类似 126，要判断一下这个新单词和 cur 之间的层数关系
                            // 注意到 steps 代表的其实就是这个新单词所在的层号
                            // 实际上只需要记录某个单词前面是否访问过即可
                            if(visited.find(tmp) == visited.end())
                            {
                                q.push(tmp);
                                visited.insert(tmp);
                            }
                            // 如果这个新单词就是 endWord，我们就已经可以结束 BFS 循环了
                            if(tmp == endWord)
                            {
                                valid = true;
                            }
                        }
                    }
                }
            }
        }
    }
    // 循环结束，之间返回 steps 结果即可
    // 还需要根据 valid 的值来判断我们是否找到了合法的可达 endWord 的路径
    return valid ? steps : 0;
}