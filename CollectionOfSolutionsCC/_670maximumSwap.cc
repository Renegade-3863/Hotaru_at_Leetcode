#include "Solution.h"

int Leetcode601_700::Soltuion::maximumSwap(int num)
{
    // 本质上和 "下一个更大排列" 是差不多的题目
    // 我们可以把 num 转存成一个数组来尝试寻找最大的交换方法
    // 要拿到最大的一步交换结果
    // 方法论很明显是贪心
    // 我们很明显需要把右侧的一个尽可能大的数，交换到左侧一个最靠左的比这个右侧大数小的数的位置上去
    // 具体化实现细节的话：
    // 我们可以维护一个尽量靠右的 "已知最大值" maximum
    // 之后按照这个方案从右往左对 num 进行遍历
    // 如果发现 maximum 可以被更新
    // 那么我们可以首先更新 maximum
    // 而如果发现遍历到的新值是小于 maximum 的，我们便可以更新最后的结果 res
    // 遍历完成后，返回 res 即可
    if(num == 0)
    {
        return 0;
    }
    int res = num, tmp = num;
    vector<int> refactor;
    while(tmp)
    {
        refactor.insert(refactor.begin(), tmp%10);
        tmp /= 10;
        // cout << tmp << endl;
    }
    // 转换完成，之后就是按照上面的逻辑进行遍历了
    int n = refactor.size(), maximum = refactor[n-1];
    // for(int i = 0; i < n; ++i)
    // {
        // cout << refactor[i] << " ";
    // }
    // cout << endl;
    int exp = 10; 
    int maxExp = 1;
    for(int i = n-2; i >= 0; --i)
    {
        // 1. refactor[i] > maximum，那么更新 maximum 即可，不更新 res
        if(refactor[i] > maximum)
        {
            maximum = refactor[i];
            maxExp = exp;
        }
        // 补充一条，如果 refactor[i] == maximum，我们需要保留的是更靠右的那个同样大的值，所以这种情况下直接跳过这个值即可
        else if(refactor[i] == maximum)
        {
            // do nothing，but need to update exp
            ;
        }
        // 2. refactor[i] < maximum，那么我们可以更新 res，尝试把这个右侧最大的 maximum 数值调换到这个已知最靠右的更小值位置上
        else
        {
            res = num-exp*refactor[i]+exp*maximum-maxExp*maximum+maxExp*refactor[i];
        }
        exp *= 10;
    }
    return res;
}