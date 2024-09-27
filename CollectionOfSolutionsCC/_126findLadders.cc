#include "Solution.h"

// 傻瓜式 BFS，直接炸内存。。。
vector<vector<string>> Leetcode101_200::Solution::findLadders(string beginWord, string endWord, vector<string>& wordList)
{
    // 本题应该是序号上最小的一道图论的题目，难度不小
    // 题目要求我们找出的是最短的转换序列，所以不难想出应该使用的是 BFS 方案
    // 我们需要考虑的是如何建图，一旦图建好了，整个 BFS 遍历过程就是很好写的了
    // 可以尝试这样的策略，使用一个哈希表转储整个 wordList 数组，之后在对每个结点进行遍历的时候，每次只修改其单词中的一个字符，考察这个哈希表中是否存在对应的结点，如果存在，就按 BFS 的规则进行处理
    unordered_map<string, int> memo;
    // false 代表这个单词还没有被访问过
    for(int i = 0; i < wordList.size(); ++i)
    {
        memo[wordList[i]] = 0;
    }
    // 唯一的额外情况：beginWord == endWord
    // 此时我们直接返回一种结果即可
    if(beginWord == endWord)
    {
        return {{beginWord}};
    }
    // 转储完成，现在有了高效查询的数据结构，可以继续后面图有关的操作了
    // 注意一个细节问题，由于我们的 BFS 本身是不做任何条件限制的，换句话说，这个 BFS 是可以往回走的
    // 因而我们要避免这种情况出现，就应该把哈希集合换成哈希表，用来记录某个单词是否在 BFS 中被访问过了
    // 模拟实际的 BFS 过程
    // 用一个二维的字符串数组存储最终的结果
    // 存储当前递归到的所有路径信息
    vector<vector<string>> res;
    // 由于本题我们需要记录路径本身的信息，而且要求找出的是所有这样的最短路径，所以不难想到可能会需要更偏向回溯的方案，而不是简单的队列
    // 所以考虑使用递归的方案来执行 BFS
    queue<vector<string>> q;
    // valid 记录当前层我们是否找到了对应的终点，可以预见的是，如果当前层找到了对应的终点，那么我们就不用继续深入了，因为后面的层一定路径长度会更长
    bool valid = false;
    // 记录好当前检查过的唯一一条路径：[beginWord]
    q.push(vector<string>(1, beginWord));
    while(!q.empty() && !valid)
    {
        int n = q.size();
        // 一层一层地扩散
        // 遍历上一层所有路径，针对它们结尾的字符串尝试进行下一层的扩散
        for(int i = 0; i < n; ++i)
        {
            // 取出当前路径的末端结点
            string rec = q.front()[q.front().size()-1];
            // 尝试所有可能的下一步单词
            for(int j = 0; j < rec.size(); ++j)
            {
                rec = q.front()[q.front().size()-1];
                for(int k = 0; k < 26; ++k)
                {
                    // 尝试把每一位上的字符替换成另一个和原值不一样的字符
                    if(q.front()[q.front().size()-1][j] != 'a'+k)
                    {
                        // 替换字符
                        rec[j] = (char)('a'+k);
                        // 检查是否存在于 wordList 中，存在并且没有访问过，那么可以基于这个信息添加一个新的路径到 paths 中
                        if(memo.find(rec) != memo.end() && memo[rec] != -1)
                        {
                            // 添加新的路径
                            vector<string> newPath = q.front();
                            newPath.push_back(rec);
                            // 如果我们找到了这样的一条路径，就要把它添加到最后的答案数组中
                            if(rec == endWord)
                            {
                                valid = true;
                                res.push_back(newPath);
                            }
                            // 记录这个新访问的结点，防止重复访问，注意，我们不能把 endWord 记录成 true
                            else
                            {
                                memo[rec] += 1;
                            }
                            // 队列记录新的路径
                            q.push(newPath);
                        }
                    }
                }
            }
            // 当前路径检查完毕，弹出队头元素
            q.pop();
        }
        // 遍历哈希表，如果存在某个单词使用次数不为0，就把它置为 -1 (已经用过)
        for(auto& it: memo)
        {
            if(it.second > 0)
            {
                it.second = -1;
            }
        }
    }
    // 循环结束，我们只需要返回 res 即可
    return res;
}

