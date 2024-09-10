#include "Solution.h"

string Leetcode1_100::Solution::convert(string s, int numRows)
{
    // 目的是把一串正常的线性字符串压缩成N字形的排列，本质上是一道模拟题目
    // 行数为0，那么无需任何变换，直接返回原字符串即可
    if(numRows == 1)
    {
        return s;
    }
    // 填写 numRows 行字符串，之后拼起来即可
    vector<string> strs(numRows);
    // flag 代表当前是需要向下移动光标，还是向上移动光标
    // 一开始是以向下移动开始，这是为了兼容 flag 变换的逻辑
    int flag = -1, n = s.size();
    int idx = 0;
    for(int i = 0; i < n; ++i)
    {
        // 如果当前 idx 是当前方向上最后一个合法的位置，就说明我们需要变向了
        if(idx == 0 || idx == numRows-1)
        {
            flag = -flag;
        }
        // 先填写后变向，这也是为了兼容整体的算法逻辑
        strs[idx] += s[i];
        idx += flag;
    }
    string res = "";
    for(int i = 0; i < numRows; ++i)
    {
        res += strs[i];
    }
    return res;
}