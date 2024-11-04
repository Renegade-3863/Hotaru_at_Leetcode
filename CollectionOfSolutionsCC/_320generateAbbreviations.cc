#include "Solution.h"

vector<string> Leetcode301_400::Solution::generateAbbreviations(string word)
{
    // 一道对于加深对回溯算法理解非常好的题目，画一棵回溯树会更好理解本题想考察的内容
    int n = word.size();
    vector<string> res;
    string path = "";
    // 递归回溯函数
    function<void(int)> backtrack = [&](int idx)
    {
        if(idx == n)
        {
            res.push_back(path);
            return;
        }
        // 不要被题目描述误导了，我们只需要按字符为单位进行回溯即可
        // 根据回溯树，我们需要剪掉的枝条无非是那些出现了 b -> 右指向 b 的路径
        // 如果字符串是空的，或者路径串中上一个添加的不是一个数字，那么当前情况下我们可以添加一个任意字符
        if(path == "" || !isdigit(path.back()))
        {
            path.push_back(word[idx]);
            backtrack(idx+1);
            path.pop_back();
            // 要添加一个数字的话，这个数字可以是后面剩下子串的任意切片长度
            for(int i = idx; i < n; ++i)
            {
                string tmp = path;
                path += to_string(i-idx+1);
                backtrack(i+1);
                // 回溯
                path = tmp;
            }
        }
        else
        {
            // 如果上一个添加的是一个数字，那么我们只能是添加当前这一个字符进来
            path.push_back(word[idx]);
            backtrack(idx+1);
            path.pop_back();
        }
    };
    backtrack(0);
    return res;
}