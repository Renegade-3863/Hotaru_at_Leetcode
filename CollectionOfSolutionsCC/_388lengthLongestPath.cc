#include "Solution.h"

// 比较暴力简单的做法，虽然 MLE 了。。。
int Leetcode301_400::Solution::lengthLongestPath(string input)
{
    // 细节模拟类的 DFS 问题
    // 我们遵循下面的逻辑即可
    // 每次解析出一个组分，检查这个组分的性质：
    // 1. 有扩展名
    // 那么这个组分就代表了一个文件，而不是文件夹
    // 遇到文件的时候，我们需要更新全局的最深文件绝对路径长度
    // 这里就有一个问题：如何知道我们的绝对路径？
    // 这可以通过一种类似回溯的方法来记录当前检查到的路径字符串
    // 不过原本题目给出的字符串格式并不适合应用回溯算法，我们需要对这些文件/文件夹进行按层分类，这就需要用到哈希表了
    // 2. 无扩展名
    // 那么这个组分就代表了一个文件夹
    // 我们此时不用更新全局的答案
    // 回溯模版向来都是很简单的，所以我们本题的关键就是如何把这个字符串按层数进行分别存储
    unordered_map<int, vector<string>> levels;
    levels[0].push_back("/");
    // 第一步，对原字符串进行分层解析
    // 难点在于：我们如何解析出两个文件/文件夹之间的有向关系？
    // 可以这样处理：
    // 我们记录每一层最后一个解析出来的字符串的名称
    // 之后每解析出一个新的字符串，根据这个新字符串所在的层级，我们可以检出层级比它小1的层上最后一个字符串，那么这个文件/文件夹就是从属于这一个字符串代表的文件夹的
    // 很巧妙的一种思路，也符合题目给出的这种类树型结构
    unordered_map<string, vector<string>> mappings;
    int level = 1;
    // 记录文件/文件夹的字符串
    string subStr;
    int n = input.size();
    for(int i = 0; i < n; ++i)
    {
        // 每个字符无非就是三种可能
        // 1. 一个 enter
        // 2. 一个 tab
        // 3. 一个正常字符/点号
        // 这里我们把正常字符和点号视同即可
        // 情况1.
        if(input[i] == '\n')
        {
            // 此时，我们可以记录 subStr 到哈希表的对应层级，并根据上一层的最后一个字符串进行更新
            // 注意，由于给出的路径可能是相对陆军，即 "不是从根目录开始的路径"，我们规定根目录所在的层级就是 0
            // 这样就统一了整体的表示方法
            // 同时最根部的路径名就是 "/" 字符串
            // 根据 level 值记录对应的 subStr 到 levels 中
            levels[level].push_back(subStr);
            // 同时根据 level-1 层的最后一个字符串确定这个文件/文件夹属于那一个上层文件夹
            mappings[levels[level-1].back()].push_back(subStr);
            // 重置 subStr 和 level
            level = 1;
            subStr = "";
        }
        // 情况2.
        else if(input[i] == '\t')
        {
            ++level;
        }
        // 情况3. 记录到 subStr 中即可
        else
        {
            subStr.push_back(input[i]);
        }
    }
    // cout << "Finished" << endl;
    // 别忘了对最后一个文件/文件夹进行处理，它不是以 '\n' 或 '\t' 结尾的
    levels[level].push_back(subStr);
    mappings[levels[level-1].back()].push_back(subStr);
    // 至此，解析完成，后面的回溯操作我们只需要用到这个 字符串 -> 字符串数组 的哈希表
    string path;
    int res = 0;
    function<void(string)> backtrack = [&](string cur)
    {
        // 对于当前文件/文件夹
        // 如果 cur 是一个文件夹，那么更新全局的最大绝对路径长度
        // 另一个小细节：绝对路径的不同文件之间，需要添加一个 '/' 反斜线符号，所以我们需要在递归的时候进行添加
        if(cur.contains('.'))
        {
            // 文件夹不可能有进一步的嵌套，直接返回即可
            res = max(res, (int)path.size()-1);
            return;
        }
        // 否则，cur 这里对应的还是一个文件，它可能会有更深入的路径，我们使用循环进行递归
        for(const auto& nxt : mappings[cur])
        {
            // 对 path 添加每一个 nxt 字符串，更新对应的路径
            path += nxt;
            path += '/';
            backtrack(nxt);
            // 回溯
            path.pop_back();
            path = path.substr(0, path.size()-nxt.size());
        }
    };
    // 对所有第1层的字符串进行一轮回溯，即可找到最终的答案
    for(const auto& first : mappings["/"])
    {
        path = first;
        path.push_back('/');
        backtrack(first);
    }
    return res;
}

// 空间优化
// 上面的第一版方法，我们对每一个层级都记录的一整个数组，实际上这不是必要的，我们只需要记录对应的层最后一个字符串即可
// 基于这一点可以优化掉一半的内存开销
// 可是优化后依然超内存。。。
int Leetcode301_400::Solution::lengthLongestPath(string input)
{
    // 细节模拟类的 DFS 问题
    // 我们遵循下面的逻辑即可
    // 每次解析出一个组分，检查这个组分的性质：
    // 1. 有扩展名
    // 那么这个组分就代表了一个文件，而不是文件夹
    // 遇到文件的时候，我们需要更新全局的最深文件绝对路径长度
    // 这里就有一个问题：如何知道我们的绝对路径？
    // 这可以通过一种类似回溯的方法来记录当前检查到的路径字符串
    // 不过原本题目给出的字符串格式并不适合应用回溯算法，我们需要对这些文件/文件夹进行按层分类，这就需要用到哈希表了
    // 2. 无扩展名
    // 那么这个组分就代表了一个文件夹
    // 我们此时不用更新全局的答案
    // 回溯模版向来都是很简单的，所以我们本题的关键就是如何把这个字符串按层数进行分别存储
    unordered_map<int, string> levels;
    levels[0] = "/";
    // 第一步，对原字符串进行分层解析
    // 难点在于：我们如何解析出两个文件/文件夹之间的有向关系？
    // 可以这样处理：
    // 我们记录每一层最后一个解析出来的字符串的名称
    // 之后每解析出一个新的字符串，根据这个新字符串所在的层级，我们可以检出层级比它小1的层上最后一个字符串，那么这个文件/文件夹就是从属于这一个字符串代表的文件夹的
    // 很巧妙的一种思路，也符合题目给出的这种类树型结构
    unordered_map<string, vector<string>> mappings;
    int level = 1;
    // 记录文件/文件夹的字符串
    string subStr;
    int n = input.size();
    for(int i = 0; i < n; ++i)
    {
        // 每个字符无非就是三种可能
        // 1. 一个 enter
        // 2. 一个 tab
        // 3. 一个正常字符/点号
        // 这里我们把正常字符和点号视同即可
        // 情况1.
        if(input[i] == '\n')
        {
            // 此时，我们可以记录 subStr 到哈希表的对应层级，并根据上一层的最后一个字符串进行更新
            // 注意，由于给出的路径可能是相对陆军，即 "不是从根目录开始的路径"，我们规定根目录所在的层级就是 0
            // 这样就统一了整体的表示方法
            // 同时最根部的路径名就是 "/" 字符串
            // 根据 level 值记录对应的 subStr 到 levels 中
            levels[level] = subStr;
            // 同时根据 level-1 层的最后一个字符串确定这个文件/文件夹属于那一个上层文件夹
            mappings[levels[level-1]].push_back(subStr);
            // 重置 subStr 和 level
            level = 1;
            subStr = "";
        }
        // 情况2.
        else if(input[i] == '\t')
        {
            ++level;
        }
        // 情况3. 记录到 subStr 中即可
        else
        {
            subStr.push_back(input[i]);
        }
    }
    // cout << "Finished" << endl;
    // 别忘了对最后一个文件/文件夹进行处理，它不是以 '\n' 或 '\t' 结尾的
    levels[level] = subStr;
    mappings[levels[level-1]].push_back(subStr);
    // 至此，解析完成，后面的回溯操作我们只需要用到这个 字符串 -> 字符串数组 的哈希表
    string path;
    int res = 0;
    function<void(string)> backtrack = [&](string cur)
    {
        // 对于当前文件/文件夹
        // 如果 cur 是一个文件夹，那么更新全局的最大绝对路径长度
        // 另一个小细节：绝对路径的不同文件之间，需要添加一个 '/' 反斜线符号，所以我们需要在递归的时候进行添加
        if(cur.contains('.'))
        {
            // 文件夹不可能有进一步的嵌套，直接返回即可
            res = max(res, (int)path.size()-1);
            return;
        }
        // 否则，cur 这里对应的还是一个文件，它可能会有更深入的路径，我们使用循环进行递归
        for(const auto& nxt : mappings[cur])
        {
            // 对 path 添加每一个 nxt 字符串，更新对应的路径
            path += nxt;
            path += '/';
            backtrack(nxt);
            // 回溯
            path.pop_back();
            path = path.substr(0, path.size()-nxt.size());
        }
    };
    // 对所有第1层的字符串进行一轮回溯，即可找到最终的答案
    for(const auto& first : mappings["/"])
    {
        path = first;
        path.push_back('/');
        backtrack(first);
    }
    return res;
}

// 进一步空间优化
// 注意到题目给出的目录结构本身就符合回溯方法的顺序，所以我们甚至可以省略掉保存图本身信息的这个哈希表，直接在前面遍历整个字符串的时候进行最长绝对路径的计算
int Leetcode301_400::Solution::lengthLongestPath(string input)
{
         // 细节模拟类的 DFS 问题
        // 我们遵循下面的逻辑即可
        // 每次解析出一个组分，检查这个组分的性质：
        // 1. 有扩展名
        // 那么这个组分就代表了一个文件，而不是文件夹
        // 遇到文件的时候，我们需要更新全局的最深文件绝对路径长度
        // 这里就有一个问题：如何知道我们的绝对路径？
        // 这可以通过一种类似回溯的方法来记录当前检查到的路径字符串
        // 不过原本题目给出的字符串格式并不适合应用回溯算法，我们需要对这些文件/文件夹进行按层分类，这就需要用到哈希表了
        // 2. 无扩展名
        // 那么这个组分就代表了一个文件夹
        // 我们此时不用更新全局的答案
        // 回溯模版向来都是很简单的，所以我们本题的关键就是如何把这个字符串按层数进行分别存储
        unordered_map<int, string> levels;
        levels[0] = "/";
        // 第一步，对原字符串进行分层解析
        // 难点在于：我们如何解析出两个文件/文件夹之间的有向关系？
        // 可以这样处理：
        // 我们记录每一层最后一个解析出来的字符串的名称
        // 之后每解析出一个新的字符串，根据这个新字符串所在的层级，我们可以检出层级比它小1的层上最后一个字符串，那么这个文件/文件夹就是从属于这一个字符串代表的文件夹的
        // 很巧妙的一种思路，也符合题目给出的这种类树型结构
        unordered_map<string, vector<string>> mappings;
        int level = 1;
        // 记录文件/文件夹的字符串
        string subStr;
        int n = input.size();
        int res = 0;
        for (int i = 0; i < n; ++i) {
            // 每个字符无非就是三种可能
            // 1. 一个 enter
            // 2. 一个 tab
            // 3. 一个正常字符/点号
            // 这里我们把正常字符和点号视同即可
            // 情况1.
            if (input[i] == '\n') {
                // 此时，我们可以记录 subStr
                // 到哈希表的对应层级，并根据上一层的最后一个字符串进行更新
                // 注意，由于给出的路径可能是相对陆军，即
                // "不是从根目录开始的路径"，我们规定根目录所在的层级就是 0
                // 这样就统一了整体的表示方法
                // 同时最根部的路径名就是 "/" 字符串
                // 根据 level 值记录对应的 subStr 到 levels 中
                levels[level] = subStr;
                if (subStr.contains('.')) {
                    // 同时根据 level-1
                    // 层的最后一个字符串确定这个文件/文件夹属于哪一个上层文件夹
                    string path;
                    for (int l = 1; l < level; ++l) {
                        // 拼接这个最大路径
                        path += levels[l];
                        path.push_back('/');
                    }
                    path += levels[level];
                    // 更新最大长度
                    res = max(res, (int)path.size());
                }
                mappings[levels[level - 1]].push_back(subStr);
                // 重置 subStr 和 level
                level = 1;
                subStr = "";
            }
            // 情况2.
            else if (input[i] == '\t') {
                ++level;
            }
            // 情况3. 记录到 subStr 中即可
            else {
                subStr.push_back(input[i]);
            }
        }
        // 别忘了对最后一个文件/文件夹进行处理，它不是以 '\n' 或 '\t' 结尾的
        levels[level] = subStr;
        mappings[levels[level - 1]].push_back(subStr);
        if (subStr.contains('.')) {
            string path;
            for (int l = 1; l < level; ++l) {
                path += levels[l];
                path.push_back('/');
            }
            path += levels[level];
            res = max(res, (int)path.size());
        }
        return res;
}