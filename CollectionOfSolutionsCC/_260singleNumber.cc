#include "Solution.h"

vector<int> singleNumber3(vector<int>& nums)
{
    // 本题依旧是一道异或运算的经典题目
    // 考虑 nums 数组中所有元素的二进制表示形式：
    // 由于 nums 中只有两个元素出现过1次，其它元素都出现了2次，那么如果我们对这一整个数组做一轮异或运算，那么很明显，对于异或结果，会有下面的结果
    // 如果结果的二进制表示中，某一位上的数值如果是1，那么代表我们这两个出现过一次的元素在当前位上的值一定是互异的
    // 因为任何其它出现过两次的元素，它们异或的结果上，这一位一定是零 (因为 1^1 = 0, 0^0 = 0)
    // 那么最后结果上，这一位出现了1，那么只能是这两个出现了一次的元素，当前位上出现了一次1
    // 那么我们可以根据这样的位对 nums 进行分组，一组是当前位上是 0 的，另一组是当前位上是 1 的
    // 经过这样的分组，我们就不难发现：两个只出现了一次的元素分别被分配到了两个不同的分组中！
    // 那么我们相当于就把这个问题转换回了 "只出现一次的数字 I" 这个问题
    // 方法明确了，我们只需要写代码了
    vector<int> gp1;
    vector<int> gp2;
    int n = nums.size();
    // 先计算出整个数组的异或和
    int xOrSum = 0;
    for(int i = 0; i < n; ++i)
    {
        xOrSum ^= nums[i];
    }
    // 之后我们可以取出 xOrSum 中出现过的最靠右的那一位1的位置(注意：这个1一定是会出现的，不然这两个出现一次的元素就相等了。。。)
    int seq = 1;
    while((seq & xOrSum) == 0)
    {
        seq <<= 1;
    }
    // 之后我们就可以按这一位进行分组了
    for(int i = 0; i < n; ++i)
    {
        if(nums[i] & seq)
        {
            gp1.push_back(nums[i]);
        }
        else
        {
            gp2.push_back(nums[i]);
        }
    }
    // 分别对两个集合进行异或即可得到两个结果
    vector<int> res(2, 0);
    for(int i = 0; i < gp1.size(); ++i)
    {
        res[0] ^= gp1[i];
    }
    for(int i = 0; i < gp2.size(); ++i)
    {
        res[1] ^= gp2[i];
    }
    return res;
}