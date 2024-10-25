#include "Solution.h"

vector<string> Leetcode201_300::Solution::generatePalindromes(string s)
{
    // 本题也是要求 "找出所有情况"，那么不难想到又是回溯算法题目
    // 我们要做的是，先判断当前字符串是不是一个排列回文串，如果是，再根据判断过程中获得的数据进行回溯组合
    // 这里我们不用哈希表，而是使用数组来模拟一个本身就有序的字符数组
    vector<int> cnts(128, 0);
    int cntDiff = 0;
    int n = s.size();
    int pos = -1;
    for(int i = 0; i < n; ++i)
    {
        if(cnts[s[i]]%2==0)
        {
            ++cntDiff;
        }
        else
        {
            --cntDiff;
        }
        ++cnts[s[i]];
    }
    // 根据上面拿到的数据，这里可以直接丢弃不合法的字符串
    if(cntDiff > 1)
    {
        return {};
    }
    for(int i = 0; i < 128; ++i)
    {
        if(cnts[i] % 2)
        {
            pos = i;
        }
    }
    // 否则，我们可以根据哈希表中的数据进行回溯操作
    // 首先，如果出现了某个出现奇数次的元素，此时我们需要把这个多出来的元素放到答案字符串的中间，这是必须做的一步处理
    string path("");
    vector<string> res;
    if(cntDiff == 1)
    {
        path += (char)(pos);
        // 把这个字符的剩余出现次数减少1
        --cnts[pos];
    }
    // 依然是利用循环+递归的过程来执行回溯算法
    // 可以利用 cnts 数组作为递归路径记录
    function<void()> backtrack = [&]()
    {
        // 考虑回溯到结束条件
        // 应该是 cnts 中的所有字符都已经被添加到 path 中了
        // 我们可以通过 path 的长度是否等于 s 来进行判断
        if(path.size() == s.size())
        {
            res.push_back(path);
            return;
        }
        // 分析一下去重问题
        // 这种探查方案会出现重复吗？
        // 注意到这样的事实：
        // 我们执行的是对于每一对位置，都从左往右遍历每一种可行的字符进行添加，所以同一对位置上是一定不会出现重复的
        // 至于不同对的位置上的字符，因为 abba 和 baab 属于两种不同的回文字符串，我们可以发现不同位置上不可能会出现重复情况，所以不用考虑
        for(int i = 0; i < 128; ++i)
        {
            // 当当前这个字符的出现次数非零的时候，我们可以在首尾添加一对当前字符
            if(cnts[i] > 0)
            {
                path.insert(0, 1, (char)(i));
                path.push_back((char)(i));
                // 减少当前这个字符的剩余次数
                cnts[i] -= 2;
                // 进行递归
                backtrack();
                // 进行回溯
                path.pop_back();
                path.erase(0, 1);
                cnts[i] += 2;
            }
        }
    };
    // 对 backtrack 函数进行调用即可
    backtrack();
    return res;
}