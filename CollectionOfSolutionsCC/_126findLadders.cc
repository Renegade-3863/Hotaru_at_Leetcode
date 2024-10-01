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

vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList)
{
    // 隔了一天，拿好 ipad 和笔，再来尝试一次这道题，
    // 其实由于我们要找的是最短路径，最根本的策略还应该是 BFS
    // 我们第一版的主要问题在于，把每条可能的子路径都进行了存储，由于不是所有的子路径都能够达到最短这一特点，因而可以想象的是我们会存储很多冗余的路径，如何避免这一点？
    // 其实比起存储整条路径，我们完全可以存储每个结点的 "上一跳结点" 这一信息
    // 就是，在 BFS 遍历过程中，某个字符串的父结点是哪一个单词的信息
    // 这样做为什么可以代替直接记录路径？
    // 还是 BFS "不会回头" 的特性
    // 因为 BFS 中，我们是一层一层向外进行扩散的，所以一定不会出现同一个结点由某个父结点扩散而来，然而它却又是这个父结点的父结点的情况
    // 因而，我们可以存储，在 BFS 中，每个结点所有可能的父结点的信息
    // 用来存储 BFS 过程中每个结点的父结点信息
    unordered_map<string, set<string>> fathers;
    // 同时，注意到每个结点不能向层数比它小的结点，或者层数等于它的结点进行扩散(前提是从源结点到达这些结点的最少步数是小于等于当前结点的)
    // 我们要记录一个每一层结点 "步数" 信息
    unordered_map<string, int> levels;
    // 同时，为了搞笑判断某个字符串是否存在于 wordList 中，我们还需要一个哈希表用作告诉查找结构
    // 至于为什么用表不用集合，后面回溯过程会用到这个 bool 值
    unordered_set<string> memo;
    // 我们先填充这个哈希表
    int n = wordList.size();
    for(int i = 0; i < n; ++i)
    {
        memo.insert(wordList[i]);
        // 给每个结点的 "层数" 值赋一个极大值
        levels[wordList[i]] = 0x3f3f3f3f;
    }
    // 全局答案数组
    vector<vector<string>> res;
    if(memo.find(endWord) == memo.end())
    {
        return res;
    }
    // 记录好之后，就可以开始进行 BFS 遍历了
    // 基本的遍历策略和第一版是一样的，区别在于，第二版我们不再使用整个的字符串数组，而是采用父结点集的方式进行本地路径记录
    queue<string> q;
    q.push(beginWord);
    // 记录 beginWord 在第 0 层
    levels[beginWord] = 0;
    bool valid = false;
    while(!q.empty() && !valid)
    {
        // 可以按层进行遍历出队，也可以不用，这里用循环模拟按层遍历，方便理解
        // 获取当前层结点个数
        int m = q.size();
        // 遍历当前层所有结点
        for(int i = 0; i < m; ++i)
        {
            string cur = q.front();
            // 可以直接出队 
            q.pop();
            // 枚举所有可能的下一跳字符串
            // 尝试替换当前字符串的每一位字符
            for(int j = 0; j < cur.size(); ++j)
            {
                // 拿一份副本，防止污染 cur 原值
                string cp = cur;
                // 尝试换成每种可能的值(原值除外)
                for(int k = 0; k < 26; ++k)
                {
                    if(cur[j] != (char)('a'+k))
                    {
                        // 替换后，检查 wordList 中是否存在这个字符串
                        cp[j] = (char)('a'+k);
                        // 也可以在这里添加一个条件：fathers[cp].find(cur) == fathers.end()，同样可以避免 TLE
                        if(memo.find(cp) != memo.end() && levels[cp] > levels[cur] && fathers[cp].find(cur) == fathers.end())
                        {
                            // TLE 和全面通过唯一差的一句条件判断
                            // 至于为什么会 TLE，考虑下面的原因：
                            // 如果我们从好多个父结点多次访问到了同一个孩子结点，那么犹豫我们上面没有进行判重，理论上这里会重复把这个子结点添加到队列中
                            // 相当于我们平白多检查了同一个子结点很多次，想通过构造数据攻击使你的代码超时就非常简单了
                            // 所以这里我们添加一个条件，只有当这个结点之前没有遍历过的时候，才把它添加到队列中等待下次遍历
                            // 从这个角度来想，其实也可以在上面的 if 语句中进行重复判断
                            // if(levels[cp] == 0x3f3f3f3f)
                            // {
                                q.push(cp);
                            // }
                            // 存在并且层数是大于当前结点 cur 的，那么记录它的层数，并加入到队列中
                            levels[cp] = levels[cur]+1;
                            // 多记录一个这个结点的可能父结点
                            fathers[cp].insert(cur);
                            // memo.erase(cp);
                            if(cp == endWord)
                            {
                                valid = true;
                            }
                        }
                    }
                }
            }
        }
    }
    // 全局路径数组，记录回溯中当前遍历到的路径
    vector<string> path;
    // BFS 结束后，fathers 表中就存储了每个结点在最短路径上的所有可能父结点，我们只需要检查这个集合，就能还原出所有可能的最短路径
    function<void(string)> backtrack = [&](string curr)
    {
        // 递归结束条件：已经检查到了 beginWord，说明我们已经还原好了一跳最短路径，可以添加到答案数组中
        if(curr == beginWord)
        {
            // 注意我们找到的是一跳反向的路径(从 endWord -> beginWord)，所以要先 reverse 再添加
            reverse(path.begin(), path.end());
            res.push_back(path);
            // 一点小瑕疵，因为我们存储的是反向路径，所以为了和回溯步骤的逻辑统一，这里要再 reverse 回去
            reverse(path.begin(), path.end());
            return;
        }
        // 递归+回溯步骤
        // 检查这个结点所有可能的父结点，这可以通过 fathers 表来查得
        for(const auto& father : fathers[curr])
        {
            // 先添加当前遍历到父结点的值
            path.push_back(father);
            // 递归查找这个父结点的上一跳结点
            backtrack(father);
            path.pop_back();
        }
    };
    // 直接调用 backtrack 函数即可，注意要先把 endWord 放入 path 中，这是因为我们的 backtrack 只会添加 "下一跳结点" 到 path 中
    path.push_back(endWord);
    backtrack(endWord);
    // 返回结果即可
    return res;
}