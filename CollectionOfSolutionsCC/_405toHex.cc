#include "Solution.h"

string Leetcode401_500::Solution::toHex(int num)
{
    // 特殊情况：num == 0
    // 此时下面的循环不会进行，我们需要单独返回一个 0
    if(num == 0)
    {
        return "0";
    }
    // 一种应该在计组原理中会学到的转换算法
    // 先不考虑负数，我们假定 num 总是正数，此时的算法较为统一
    // 不断地对 num 除 16，每次根据除出来的余数决定当前的下一个字符要接哪一个
    // 直到 num 被除成零为止
    // 最后把得到的字符串反转，就是我们最后的答案
    // 如何处理负数？
    // 理解一下补码的基本逻辑，类似一个环
    // 我们把无符号类型的二进制数表示范围折半，大的那一半映射到负数范围，就是补码，所以，我们只需要给所有负数加上一个 2^32，那么再按正数计算法计算对应的表示形式就是结果了
    unsigned int rec = num;
    string res;
    while(rec)
    {
        int remain = rec % 16;
        if(remain < 10)
        {
            res.push_back('0'+remain);
        }
        else 
        {
            res.push_back(remain-10+'a');
        }
        rec /= 16;
    }
    reverse(res.begin(), res.end());
    return res;
}