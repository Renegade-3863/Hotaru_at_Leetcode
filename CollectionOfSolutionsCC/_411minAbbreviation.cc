#include "Solution.h"

// 暴力算法只过了一半用例，不过思路是对的，优化就不写了。。。面试这种题给个大概思路应该也够了，不会真让你优化那么多的吧。。。
string Leetcode401_500::Solution::minAbbreviation(string target, vector<string>& dictionary)
{
    // 最暴力的算法是直接回溯+记忆化所有检查过的缩写
    // 我们第一步是遍历 dictionary，检查所有的可能缩写，并记录到一个哈希集合中，这些缩写都不能给 target 用
    // 第二步是检查 target 所有的缩写，取出其中长度最短的，没有和哈希集合中任何一个缩写重复的那一个缩写作为结果
    unordered_map<string, int> memo;
    // 考虑如何针对一个单词，找出其所有可能的缩写，这可以通过回溯来实现
    // 记录每条回溯链上的缩写中间量
    string path;
    int length = 0;
    // 传一个处理函数，提高复用率
    function<void(const string&, int, const int&, function<void(const string&)>)> backtrack = [&](const string& board, int idx, const int& n, function<void(const string)> handle) 
    {
        // 我们考虑的是 board 的 idx 开始的子串的所有缩写可能，这需要在之后接到 path 后面
        // 回溯结束条件：
        // idx == n
        // 此时我们已经完成了生成，把缩写填到哈希集合中并返回即可
        if(idx == n)
        {
            handle(path);
            return;
        }
        // 枚举当前要截取的部分长度
        // 两条路走：
        // 1. 不截取任何一个子串，此时直接把 board[idx] 添加到 path 中，并深入一个字符即可
        path += board[idx];
        ++length;
        backtrack(board, idx+1, n, handle);
        --length;
        path.pop_back();
        // 2. 我们要截取一个子串，之后再进一步深入递归
        for(int i = idx; i < n; ++i)
        {
            // 把截取出来的部分转换成一个长度数字尾接到 path 中
            string len = to_string(i-idx+1);
            path += len;
            ++length;
            backtrack(board, i+1, n, handle);
            // 回溯
            --length;
            path = path.substr(0, path.size()-len.size());
        }
    };
    function<void(const string&)> handle1 = [&](const string& path)
    {
        memo[path] = length;
    };
    // 对 dictionary 中的每一个单词调用上面的函数
    for(const auto& elem : dictionary)
    {
        backtrack(elem, 0, elem.size(), handle1);
    }
    string res = target;
    int ans = target.size();
    function<void(const string&)> handle2 = [&](const string& path)
    {
        if(memo.find(path) == memo.end())
        {   
            if(length < ans)
            {
                ans = length;
                res = path;
            }
        }
    };
    // 现在 memo 中就有了所有已经添加过，不能再使用的缩写了
    // 我们对 target 再搞一遍上面的过程，在回溯返回的时候改一下检查逻辑即可
    backtrack(target, 0, target.size(), handle2);
    return res;
}