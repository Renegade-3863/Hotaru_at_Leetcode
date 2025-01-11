#include "Solution.h"

bool Leetcode501_600::Soltuion::checkPerfectNumber(int num)
{
    // 需要一个高效的算法来遍历一个数所有的因数
    // 考虑从 sqrt(num) 开始遍历，这样需要的遍历次数更少
    // sum 记录因数和
    int factor = sqrt(num), sum = 0;
    // 0 不用考虑，题目限定了 num 不会为 0
    while(factor > 0)
    {
        // 需要刨除 num 本身
        if(num % factor == 0 && factor != num)
        {
            sum += factor;
            sum += num/factor;
        }
        --factor;
    }
    return (sum>>1) == num;
}