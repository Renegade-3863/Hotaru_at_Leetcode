#include "Solution.h"

int Leetcode401_500::Soltuion::magicalString(int n)
{
    // 一道基本的字符串模拟类问题
    // 我们按照定义一步一步从 "1" 这个最初的 "神奇字符串" 来递推出后面的答案即可
    // 我们先设定最初的 "神奇字符串"，经过观察，这个 "122" 可以确定是
    string maString = "122";
    // 之后是一步一步地往后递推，"1" 这个字符串对应的是第一个神奇字符串，也就是 n == 1
    // res 代表的是 "当前的神奇字符串中包含的 '1' 的个数"
    // cur 代表的是当前是第几个 "神奇字符串"
    // idx 代表的是这一轮要往 maString 中添加几个对应值，这个值是 maString[idx]
    int cur = 3, res = 1, idx = 2;
    while(cur < n)
    {
        // 直到 cur == n，代表我们已经找到了第 n 个神奇字符串，此时 res 中记录的值就是我们需要的答案
        // 思考：已知前一个 "神奇字符串"，如何推断出下一个？
        // 我们可以根据 maString 的结尾元素来对应地修改 val 的值
        // 根据 cnt 以及当前 maString 结尾的进行元素添加
        char c = maString.back() == '1' ? '2' : '1';
        int cnt = maString[idx]-'0';
        for(int i = 0; i < cnt && cur < n; ++i)
        {
            maString.push_back(c);
            // 如果添加的是 '1'，那么我们记录到 res 中
            if(c == '1')
            {
                ++res;
            }
            if(++cur == n)
            {
                break;
            }
        }
        // 把 idx 后移一位，我们用下一个数字来进行分组添加
        ++idx;
    }
    // 返回结果即可
    return res;
}