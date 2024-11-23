#include "Solution.h"

int Leetcode401_500::Solution::countSegments(string s)
{
    // 模拟题，按空格对字符串进行解析分组即可
    // 最终的答案
    int cnt = 0;
    bool hasChar = false;
    for(const auto& c : s)
    {
        if(c == ' ')
        {
            if(hasChar)
            {
                ++cnt;
                hasChar = false;
            }
        }
        else
        {
            hasChar = true;
        }
    }
    // 细节问题，因为我们递增 cnt 是根据空格来触发的，所以如果最后一个字符串不是以空格结尾，那么我们还需要把它手动算上，否则会出错
    if(hasChar)
    {
        ++cnt;
    }
    return cnt;
}