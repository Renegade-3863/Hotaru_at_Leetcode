#include "Solution.h"

vector<int> Leetcode701_800::Soltuion::selfDividingNumbers(int left, int right)
{
    // 数学废物只能想到暴力遍历 [left, right] 区间，请各路数学家们见谅（）
    vector<int> res;
    for(int num = left; num <= right; ++num)
    {
        // 对 num 进行处理
        // 分离出每一位，用 num 本身去除这些位，看余数是否为 0
        // cout << num << ": " << endl;
        int dig = num%10, op = 1, cur = 0;
        while(cur < num)
        {
            if(dig == 0)
            {
                break;
            }
            if(num%dig)
            {
                // 如果余数不是 0，那么这个 num 就不可行，我们直接跳过这个数即可
                break;
            }
            cur += dig*op;
            // op*10 <= INT_MAX
            if(op <= INT_MAX/10)
            {
                op *= 10;
            }
            dig = (num/op)%10;
        }
        if(cur == num)
        {
            // 如果除数等于了被除数，那么这个 num 就是可行解
            res.push_back(num);
        }
    }
    return res;
}