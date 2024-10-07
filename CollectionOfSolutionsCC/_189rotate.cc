#include "Solution.h"

void Leetcode101_200::Solution::rotate(vector<int>& nums, int k)
{
    int n = nums.size();
    // 本题很明显不能用暴力的模拟方案，那是非常复杂且笨重的方案
    // 考虑能不能用函数映射的数学方式来完成本题的转换
    // 注意到，如果 k 是一个大于 n(nums 长度) 的值，那么我们显然可以取 k 为 k % n
    // 因为，轮转 n 次，整个数组会回到原来的状态
    k %= n;
    // 对于每个位置 i，我们可以用数学方法明确它轮转后的位置为：(i+k) % n
    // 不过我们如果简单地通过遍历的方式进行数字修改，不难看出会导致数据覆盖进而丢失
    // 所以我们更换策略，通过一轮修改一串间隔为 k 的下标的方式来进行更新，这样，在更新的时候可以对新位置上的数据进行记忆，从而避免数据覆盖问题
    // 要达成这一点，我们需要记录一个缓存变量
    int memo = 0;
    int cnt = 0;
    // 注意到，对于每个变量，我们只需要对它进行一次后移，因而要避免重复对同一个数字进行后移，我们需要记录一个后移操作完成的元素个数
    // 通过检查我们是不是已经移动了 n 个元素来决定是否可以退出循环
    for(int i = 0; i < n; ++i)
    {
        if(cnt == n)
        {
            break;
        }
        int j = i;
        memo = nums[j];
        // 对数据流 i 进行修改
        do
        {
            int tmp = nums[(j+k)%n];
            nums[(j+k)%n] = memo;
            j = (j+k)%n;
            memo = tmp;
            // for(int t = 0; t < n; ++t)
            // {
            //     cout << nums[t] << " ";
            // }
            // cout << endl;
            ++cnt;
        } while(j != i); 
    }
    return;
}