#include "Solution.h"

int Leetcode401_500::Soltuion::findComplement(int num)
{
    // 2 进制补码问题，位运算即可
    // 题目限定了 num 为正数，所以我们不用考虑最高位的问题
    int sup = 0;
    // 我们需要先定位出 num 中从左到右第一个 1 的位置
    int i = 30;
    while((num>>i) % 2 == 0)
    {
        --i;
    }
    // cout << "i: " << i << endl;
    for(; i >= 0; --i)
    {
        sup = sup << 1;
        sup = sup | ((num>>i) % 2 == 0);
        // cout << sup << endl;
    }
    return sup;
}