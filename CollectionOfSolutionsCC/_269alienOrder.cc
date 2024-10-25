#include "Solution.h"

string Leetcode201_300::Solution::alienOrder(vector<string>& words)
{
    // 一道比较明显的拓扑排序类问题
    // 原题要我们求的所谓：字符之间的字典序大小关系问题
    // 本质上是在问：由这些字母之间的每对字符之间的大小关系串成的图中是否存在一个合法的，无环的拓扑顺序，使得我们可以完整地搞出来一个遍历新字母表的顺序
    // 那么我们的解法实际上就很简单了，可以通过先建图，后拓扑排序的方式来进行
    // 问题在于，如何建立一个表达每个字符之间可能的大小关系的图？
    // 我们给出下面的论断：
    // 只需要对这个有序的 words 字符串数组进行一轮遍历，检查每一对相邻 word 出现这种大小关系的 "原因" 即可获取关于这张图的全部有效信息
    // 为什么只需要检查相邻的 word？
    // 我们只需要证明一件事：不是直接相邻的两个单词之间无法提供除了紧邻的两个单词可以提供的信息以外的其它信息
    // 证明过程如下：
    // 假设有三个 word: word1, word2, word3
    // 大小关系为：word1 >= word2 >= word3
    // 那么我们先考察 word1 和 word2
    // 使得 word1 >= word2 的条件有两种：
    // 1. word1[i] >= word2[i]
    // 2. word1.size() >= word2.size()
    // 其它情况不用考虑，一定不会出现 word1 > word2 的情况
    // 此时再考察 word2 和 word3 的关系
    // 使得 word2 >= word3 的条件也有两种：
    // 1. word2[j] >= word3[j]
    // 2. word2.size() >= word3.size()
    // 那么对于 word1 和 word3，我们检查它们的关系能推断出什么信息
    // 此时有如下几种情况(可能并不是完全独立的情况，但是要完全独立分析太繁琐，意义不大，挑几种情况拿出来看一看就明白大概了)：
    // 1. i <= j
    //   可以自己画一下图来对问题进行分析
    //   不难发现，此时 word2 和 word3 第一个不同的字符在 word1 和 word2 第一个不同字符的后面
    //   因而此时如果我们比较 word1 和 word3，那么只能得出和 word1、word2 比较时一样的结论：word1[i] >= word3[i]
    //   所以我们此时没必要比较 word1 和 word3
    // 2. i > j
    //   再画一张图进行分析
    //   不难发现，此时 word1 和 word3 第一个不同的字符在 word2 和 word3 第一个不同字符的后面
    //   那么很显然此时我们即使比较了 word1 和 word3，也只能得到 word2[j] >= word3[j] 这个信息
    //   所以此时我们依然没必要比较 word1 和 word3
    // 3. word1.size() >= word2.size() 导致的 word1 >= word2
    // 那么此时我们其实可以把 word1 和 word2 等效起来，因为二者等长的部分是完全相同的
    // 所以比较 word1 和 word3 就等效于 word2 和 word3，我们同样不会得到任何其它有效的字符关系
    // 4. word2.size() >= word3.size() 导致的 word2 >= word3
    // 那么此时也可以把word2 和 word3 等效起来
    // 比较 word1 和 word2 是在拿 word1 和一个 word3 的延长字符串比较，那么我们也很显然没必要再检查 word1 和 word3
    // 3 和 4 可能有交集，但是我们会发现，即是二者同时发生，其实也根本没区别。。。
    // 综上，我们基本可以得出结论：只需要比较所有相邻的两个单词即可拿到全部的图信息
    // 之后，对这张图进行拓扑排序，看是否能够拿到一个完整的拓扑序列，我们就直接返回该序列即可
    // 注意一点：我们的拓扑序必须能够覆盖找出来的整张图，否则就说明，某两个或多个结点之间，出现了环，导致这个环上的所有结点都没法进入有效的拓扑序列中
    // 我们可以通过记录找出的图结点个数来进行判断
    // 一步一步来：
    // 第一步：提取图信息
    // 图信息用邻接表表示
    unordered_map<char, vector<char>> adjList;
    // 入度表是为了后续的拓扑排序使用
    unordered_map<char, int> indegrees;
    int n = words.size();
    // 首先，完整遍历一遍整个字符串数组中的每个单词，记录所有出现过的字符，记录好所有结点
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < words[i].size(); ++j)
        {
            if(adjList.find(words[i][j]) == adjList.end())
            {
                adjList[words[i][j]] = vector<char>();
            }
        }
    }
    for(int i = 1; i < n; ++i)
    {
        // 对每一对字符串进行检查
        // 最长只需要遍历二者中更小的那一个的长度
        int len = min(words[i-1].size(), words[i].size());
        // 用于判断这个字符串大小关系是否合法
        bool found = false;
        for(int j = 0; j < len; ++j)
        {
            if(words[i-1][j] != words[i][j])
            {
                found = true;
                // 向邻接表中添加这个字符关系
                // 定义有向图的指向代表的是字符的大于关系
                adjList[words[i-1][j]].push_back(words[i][j]);
                // 记录一个入度
                ++indegrees[words[i][j]];
                // 记录结束，当前字符串对的检查就完成了，可以退出循环
                break;
            }
        }
        // 检查循环结束后，是否找到了合法的大小关系，如果没有，是不是因为前面的 word 比后面的长或者二者相等
        // 这里检查：如果本身前面的循环中没有找到合法的大小关系，后面这里前面的 word 又比后面的短，那么很显然我们只能说这个大小关系不正常了。。。
        // 换句话说，这个序列压根就违背了字典序的规定
        if(!found && words[i-1].size() > words[i].size())
        {
            return "";
        }
    }
    // 检查完成，我们的邻接表和入度表就都已经处理完了
    // 下面可以开始根据入度表执行 BFS 格式的拓扑排序了
    // BFS 队列
    queue<char> q;
    for(auto& node: adjList)
    {
        if(indegrees[node.first] == 0)
        {
            q.push(node.first);
        }
    }
    string res = "";
    while(!q.empty())
    {
        // 取出一个入度为0的结点
        char cur = q.front();
        // 添加这个入度为0的结点到答案字符串中
        res.push_back(cur);
        // 弹出结点
        q.pop();
        // 之后对它的所有相邻结点进行入度减1的操作
        for(int i = 0; i < adjList[cur].size(); ++i)
        {
            if(--indegrees[adjList[cur][i]] == 0)
            {
                q.push(adjList[cur][i]);
            }
        }
    }
    // 检查拓扑排序是否完整覆盖了整张图
    // 如果提前退出了，那么就说明这张图有环，我们可以直接返回空字符串，否则，这个序列就是一个合法的拓扑序列，返回它即可
    return res.size() == adjList.size() ? res : "";
}