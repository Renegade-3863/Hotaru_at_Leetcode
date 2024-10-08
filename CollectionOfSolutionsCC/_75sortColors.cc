#include "Solution.h"

void Leetcode1_100::Solution::sortColors(vector<int>& nums)
{
    // 本题个人认为是快排的 partition 部分的阉割版
    // 传统快排以随机元素为 pivot 值，不断地进行数组切分
    // 本题，如果是熟悉快排的人，可以很快地反应出来
    // 这不就是个 pivot 值恒定为 1 和 0 的切分过程吗？？？
    // 那么其实方法就非常简单了
    // 我们先用一次遍历找到数组中任意一个 1 的位置(找最左侧的1就可以了)
    int idx = 0, n = nums.size();
    while(idx < n)
    {
        if(nums[idx] == 1)
        {
            break;
        }
        ++idx;
    }
    // 循环结束后，idx 指向的就是从左到右第一个 1 出现的下标
    // 注意一些特殊情况，题目并没有说明数组中是否一定存在1
    // 不存在1，那就拿最后一个元素进行切分即可，无论是0还是2都可以
    if(idx == n)
    {
        idx = n-1;
    }
    // 接下来就是完整的 partition 过程
    swap(nums[idx], nums[n-1]);
    int i = -1;
    for(int j = 0; j < n-1; ++j)
    {
        // 把所有不大于1的元素都放到 pivot 这个1的左边，所有大于1的元素(这里就是2)都放到 pivot 这个1的右边
        if(nums[j] <= 1)
        {
            swap(nums[++i], nums[j]);
        }
    }
    // 把这个 pivot 1 放到正确的位置上去
    swap(nums[++i], nums[n-1]);
    // 现在 i 这个下标右侧就全部都是 2 了
    // 不过现在我们会发现，左边的0和1的顺序关系不一定被完全满足
    // 所以还需要第二轮分区对左边进行修正
    idx = 0;
    // 由于 i 这个下标上的元素一定是0，所以我们只检查到 i 即可
    while(idx < i)
    {
        if(nums[idx] == 0)
        {
            break;
        }
        ++idx;
    }
    // 不存在0，那么其实就可以直接返回结果了
    if(idx == i)
    {
        return;
    }
    // 循环结束后，idx 指向的就是从左到右第一个 0 出现的下标
    // 接下来就是完整的 partition 过程
    swap(nums[idx], nums[i]);
    int j = -1;
    for(int k = 0; k < i; ++k)
    {
        if(nums[k] <= 0)
        {
            swap(nums[++j], nums[k]);
        }
    }
    swap(nums[++j], nums[i]);
    // 之后就结束了～
}

void sortColorsBetter(vector<int>& nums)
{
    // 鉴于上面自己完成的分区方案太过丑陋，而且代码的可扩展性很差，这里学习一下许多人给出的 "三路快排" 思想
    // 以及重构一下循环不变式的设定
    // 上面我的循环不变式实际上太拘泥于传统快排的那种 "随机选择 pivot 值" 的思想，因而导致了对于 "pivot 值不存在" 的情况的许多额外条件检查
    // 实际上，只要修改一下循环不变式的定义，就可以很好地规避这个问题：
    // 不再拘泥于确实地找到等于某个值的元素和结尾元素进行交换这一套路，转而利用特定的区间变量进行元素的交换
    // 本题一共有三种取值，因而可以使用两个边界值进行区分
    // 设定一个变量 zero，代表已经检查过的元素中最后一个零在交换到正确位置后的下标
    // 设定另一个变量 two，代表已经检查过的元素中最后一个二在交换到正确位置后的下标
    // 这样，我们就相当于已经把原区间拆分成了三个部分:
    // [0, zero] -> 全 0 的部分
    // (zero, i) -> 全 1 的部分
    // [two, n) -> 全 2 的部分
    // 我们只需要在遍历整个数组的过程中动态维护这三个变量信息即可完成任务
    // 注意 two 的初值设定，我们规定的是第一个 2 所在的位置下标
    int n = nums.size();
    int zero = -1, two = n, i = 0;
    // 遍历的终点就是 two 的值-1，因为它以及它后面的所有值都一定是 2
    while(i < two)
    {
        // 找到一个0，交换到 zero 位置，修订 zero 信息
        if(nums[i] == 0)
        {
            swap(nums[++zero], nums[i]);
            // 由于我们前面的交换策略保证了 (zero, i) 中的所有元素都是1，
            // 所以这里把 zero+1 位置的元素交换过来，交换过来的就一定是一个1，不可能是2
            // 相当于我们把 i 这个限制 1 的覆盖范围的边界又向右扩充了一格，故这里直接 ++i 即可
            ++i;
        }
        // 找到一个2，交换到 two 位置，修订 two 信息
        else if(nums[i] == 2)
        {
            // 这里之所以不对 i 进行修改，是因为
            // 我们交换过来的东西不一定是一个1，可能还是一个2
            // 在我们的循环不变式里面，只限定了 [zero, i) 这个范围内的全1性质，而对于 [1, two) 之间的元素，我们不知道它们都等于几
            // 所以这里把 nums[two-1] 交换过来，可能还是一个2，因此我们没法直接扩张 i 的值
            swap(nums[--two], nums[i]);
        }
        // 找到1的话不用进行修改，我们最后会把所有0放到这些1的左侧，所有2放到这些1的右侧
        else
        {
            // 朴素地找到一个1，我们也只需要朴素地向右挪动一下 i 指针，表示全1的区间又向右扩张了一格
            ++i;
        }
    }
    // 循环结束后，修改就完成了
}