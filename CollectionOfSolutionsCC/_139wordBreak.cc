#include "Solution.h"

// 第一版：错误的 pos 数组使用方法
// 错误的 BFS 方案导致了最终的超时
bool Leetcode101_200::Solution::wordBreak(string s, vector<string>& wordDict)
{
    // 学好 KMP 一定很方便，本题要求我们判断是否能用字典中出现的一个/多个单词拼接出 s 字符串
    // 因而会需要一种高效的算法判断出字典中的字符串能放到 s 中的哪个位置上
    // 对于这个算法，KMP 和字典树其实都是满足条件的，不过 KMP 比字典树看起来更加高大上，所以本题我们尝试使用 KMP 来求解
    // 先写好 KMP 的部分：
    vector<int> next;
    function<void(string)> findNext = [&](const string& word)
    {
        int n = word.size();
        // 最后这一位是用于找出当前单词在一个大字符串 s 中出现的所有位置的
        next.resize(n+1);
        // 第一位放一个-1，代表如果第一位都不能匹配，我们就无法在原串的当前这个起点匹配 word 单词
        next[0] = -1;
        // 进行递推，根据目前已知的信息
        int j = 0, k = -1;
        while(j < n)
        {
            // 如果当前的后缀不存在真前缀，或者说当前在判断的这个后缀存在真前缀
            if(k == -1 || word[j] == word[k])
            {
                ++j; ++k;
                if(j < n)
                {
                    if(word[j] == word[k])
                    {
                        next[j] = next[k];
                    }
                    else
                    {
                        next[j] = k;
                    }
                }
                else
                {
                    next[j] = k;
                }
            }
            else
            {
                k = next[k];
            }
        }
    };
    // 用一个哈希表记录每个下标处开始可以添加的所有可能单词的长度
    unordered_map<int, vector<int>> pos;
    // 注意，本题的 KMP，我们需要做一些魔改，要找出某个单词在 s 中所有可以出现的位置
    function<void(const string&, const string&)> KMP = [&](const string& word, const string& s)
    {
        // 先调用 findNext 子过程
        findNext(word);
        // 之后使用这个 next 数组对整个 s 字符串进行检查
        int i = 0, j = 0, m = s.size(), n = word.size();
        while(i < m)
        {
            if(j == -1 || s[i] == word[j])
            {
                ++i; ++j;
                // 匹配成功了一次，注意此时我们不能直接退出，因为我们要找出 word 所有出现的起始坐标
                if(j == n)
                {
                    // 记录这个起始位置可以添加一个长度为 n 的单词
                    pos[i-n].push_back(n);
                    // 重置 j
                    j = next[j];
                    // 跳过后面的操作
                    continue;
                }
            }
            // 否则，说明这两个位置上的字符不能匹配，回弹 j 指针
            else
            {
                j = next[j];
            }
        }
    };
    // 对每个单词调用一次 KMP 方案，我们就在 pos 中记录好了所有单词可能出现的下标
    // 可以利用这个信息再来求解本题
    for(int k = 0; k < wordDict.size(); ++k)
    {
        KMP(wordDict[k], s);
    }
    // 考虑如何利用这个 pos 数组
    // 我们可以这样做：
    // 顺序遍历 s 的每个下标
    // 动态维护一个最大可构造的子串长度，如果任意时刻，这个最大长度超过了 s 本身的长度，我们就相当于确认了存在一种方案构造这个字符串
    // 这个步骤就有点像 BFS 了
    // 因而我们尝试用队列来实现
    int m = s.size();
    int maxLen = 0;
    queue<int> q;
    if(pos.find(0) == pos.end())
    {
        return false;
    }
    // 第一个下标可以添加单词，我们把这个位置添加到队列中
    q.push(0);
    while(!q.empty())
    {
        // 每次弹出一个位置
        int cur = q.front();
        q.pop();
        // 遍历这个位置所有可行的下一个位置下标
        for(int i = 0; i < pos[cur].size(); ++i)
        {
            // 注意，只有恰好到达 s 原长了，我们才能断定这个构造可行
            if(cur+pos[cur][i] == m)
            {
                return true;
            }
            // 如果还不到 m 的结尾，就把这个位置添加到队列中，以备后续检查
            q.push(cur+pos[cur][i]);
        }
    }
    // 如果循环那没有返回 true，就说明不存在合法的构造，可以直接返回 false
    return false;
}

// 详细说明一下上面使用 BFS 超时的原因
// 本质在于 BFS 遍历的不是原数组，而是广搜队列
// 这可能会导致很多很多重复的检查：(也可以叫"回头")
// 考虑下面的例子：
// s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
//      aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab"
// wordDict ["a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"]
// 这个例子的问题在于，我们的 BFS 方案会多次回头
// 我们在下标 0 位置添加了 1，2，3，4，5，6，7，8，9，10 这几个下标
// 后面在弹出1的时候，我们又添加了 2，3，4，5，6，7，8，9，10，11
// 很容易发现，这个时候队列中有两份：2，3，4，5，6，7，8，9，10
// 再往后，这种重复会越发严重，因而，我们不能使用这种傻瓜式的 BFS 遍历，而应该按照下标来进行遍历
// 这样就可以避免上面的重复了，即我们只在循环中往前走


// 改进后的第二版代码，换成对下标进行遍历，而不是傻瓜式 BFS
bool wordBreak(string s, vector<string>& wordDict)
{
    // 学好 KMP 一定很方便，本题要求我们判断是否能用字典中出现的一个/多个单词拼接出 s 字符串
    // 因而会需要一种高效的算法判断出字典中的字符串能放到 s 中的哪个位置上
    // 对于这个算法，KMP 和字典树其实都是满足条件的，不过 KMP 比字典树看起来更加高大上，所以本题我们尝试使用 KMP 来求解
    // 先写好 KMP 的部分：
    vector<int> next;
    function<void(string)> findNext = [&](const string& word)
    {
        int n = word.size();
        // 最后这一位是用于找出当前单词在一个大字符串 s 中出现的所有位置的
        next.resize(n+1);
        // 第一位放一个-1，代表如果第一位都不能匹配，我们就无法在原串的当前这个起点匹配 word 单词
        next[0] = -1;
        // 进行递推，根据目前已知的信息
        int j = 0, k = -1;
        while(j < n)
        {
            // 如果当前的后缀不存在真前缀，或者说当前在判断的这个后缀存在真前缀
            if(k == -1 || word[j] == word[k])
            {
                ++j; ++k;
                if(j < n)
                {
                    if(word[j] == word[k])
                    {
                        next[j] = next[k];
                    }
                    else
                    {
                        next[j] = k;
                    }
                }
                else
                {
                    next[j] = k;
                }
            }
            else
            {
                k = next[k];
            }
        }
    };
    // 用一个哈希表记录每个下标处开始可以添加的所有可能单词的长度
    unordered_map<int, vector<int>> pos;
    // 注意，本题的 KMP，我们需要做一些魔改，要找出某个单词在 s 中所有可以出现的位置
    function<void(const string&, const string&)> KMP = [&](const string& word, const string& s)
    {
        // 先调用 findNext 子过程
        findNext(word);
        // 之后使用这个 next 数组对整个 s 字符串进行检查
        int i = 0, j = 0, m = s.size(), n = word.size();
        while(i < m)
        {
            if(j == -1 || s[i] == word[j])
            {
                ++i; ++j;
                // 匹配成功了一次，注意此时我们不能直接退出，因为我们要找出 word 所有出现的起始坐标
                if(j == n)
                {
                    // 记录这个起始位置可以添加一个长度为 n 的单词
                    pos[i-n].push_back(n);
                    // 重置 j
                    j = next[j];
                }
            }
            // 否则，说明这两个位置上的字符不能匹配，回弹 j 指针
            else
            {
                j = next[j];
            }
        }
    };
    // 对每个单词调用一次 KMP 方案，我们就在 pos 中记录好了所有单词可能出现的下标
    // 可以利用这个信息再来求解本题
    for(int k = 0; k < wordDict.size(); ++k)
    {
        KMP(wordDict[k], s);
    }
    // 考虑如何利用这个 pos 数组
    // 我们可以这样做：
    // 顺序遍历 s 的每个下标
    int m = s.size();
    int maxLen = 0;
    // 顺序遍历 s 的每个下标，动态维护所有可达的下标，如果遍历到一个位置，这个下标不可达，那么我们就简单地跳过它即可，因为经过了前面所有下标的检查，这个位置直到我们过来了，还是发现它无法到达
    // 最后只需要检出最后一个位置是否可达即可
    vector<bool> avail(m+1, false);
    if(pos.find(0) == pos.end())
    {
        return false;
    }
    avail[0] = true;
    for(int i = 0; i < m; ++i)
    {
        if(!avail[i])
        {
            continue;
        }
        for(const auto& j : pos[i])
        {
            avail[i+j] = true;
        }
    }
    return avail[m];
}