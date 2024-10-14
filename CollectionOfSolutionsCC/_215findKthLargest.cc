#include "Solution.h"

int Leetcode201_300::Solution::findKthLargest(vector<int>& nums, int k)
{
    // 本题如果不要求时间复杂度，那么其实 O(nlogn) 的小优先队列算法可以解决，不过题目要求平均时间复杂度为 O(n) 的算法来解决本题
    // 那么我们就可能需要求助于一个很常见的算法 trick：快速选择算法
    // 其实说白了，就是快速排序的 partition 部分的不断调用而已
    // 考虑这样的事实：
    // 如果我们想从一个区间 [i, j] 中找出第 k 大的元素
    // 那么根据 partition 函数的性质，每次结束一轮遍历，我们可以把不小于选出的 pivot 值的值都放到 pivot 以及它的左侧
    // 此时我们判断 pivot 值的位置，如果这个位置下标(从1开始)恰好等于 k，那么我们就找到了最终的结果，可以直接返回
    // 如果这个位置下标(从1开始)小于 k，那么说明我们要找的值应该在这个 pivot 下标的右侧，左侧的所有值我们就都可以简单丢弃了
    // 如果这个位置下标(从1开始)大于 k，那么说明我们要找的值应该在这个 pivot 下标的左侧，右侧的所有值我们就都可以简单丢弃了
    // 明确了这种类似二分的策略，我们就可以开始写代码了
    function<int(int, int, bool&)> partition = [&](int left, int right, bool& isSame)
    {
        // 先随机选出一个切分点
        // 这个切分点的下标位于 [left, right] 中
        int pivot = rand() % (right-left+1)+left;
        // 交换 pivot 和 right 上的数值
        swap(nums[pivot], nums[right]);
        // 执行 pratition 主体过程
        int i = left-1;
        for(int j = left; j < right; ++j)
        {
            // 要进行降序排列，所以要把符号反过来
            if(nums[j] >= nums[right])
            {
                if(nums[j] > nums[right])
                {
                    isSame = false;
                }
                swap(nums[++i], nums[j]);
            }
            // 如果是一个小于 nums[right] 的值，不需要移动，保持原位
        }
        // 把之前选出的 pivot 值放到正确的位置上
        swap(nums[++i], nums[right]);
        // 返回这个选出的 pivot 现在的正确下标
        return i;
    };
    // 持续对长度非1的区间 [left, right] 调用上面的 pratition 函数
    int left = 0, right = nums.size()-1;
    // 结束条件其实并不会真正触发，我们一定会在至多 left == right 的时候就满足 pivot == k-1，并返回结果
    while(left <= right)
    {
        // 进行一轮切分，并获取到可以确定的值的下标
        bool isSame = true;
        int pos = partition(left, right, isSame);
        // 处理 [left, right] 中的元素全等的情况
        if(isSame)
        {
            return nums[pos];
        }
        // 进行上面总结的分类讨论
        if(pos == k-1)
        {
            return nums[pos];
        }
        // 此时要找的元素应该在 pos 右侧，注意，此时我们还需要修改 k 的值，不然会出问题
        else if(pos < k-1)
        {
            // 因为前 pos+1 个都不可能是第 k 大的元素，所以我们只需要在右侧找第 (k-pos-1) 大的元素即可
            k -= pos+1;
            // 修改 left 
            left = pos+1;
        }
        else
        {
            // 此时不需要修改 k 值
            // 修改 right
            right = pos-1;
        }
    }
    // 并不会真正被执行到，但是 to make the compiler happy...
    // 或者，也许 k 大于 nums.size() 的时候的确会执行到这一行，不过那样我们其实可以在开头就判断。。。
    return -1;
}

// 上面的朴素两路切分策略可以很容易的被攻击失效：
// [1,2,3,4,5,1,1,1,1,...]
// 所以我们为了强化快排的效率，可以考虑改用三路快选
// 主要区别就在于，两路我们分的是 [不小于 pivot 的元素, 小于 pivot 的元素]
// 而三路我们分的是 [大于 pivot 的元素, 等于 pivot 的元素, 小于 pivot 的元素]
// 不同之处在于，这种方案下，我们很容易避免上面两路对于这种破坏性数据脆弱的性质
// 因为我们可以简单地判断 k 是否在 等于 pivot 的元素这一整个区间中，而如果不在，我们可以简单地丢弃这一整个区间，而不是像之前那样只丢弃一个值
// 具体的实现部分在代码中体现
int findKthLargest(vector<int>& nums, int k)
{
    // 返回值定义：找到的 [left, right] 区间中第 k 大(注意 k 是会随着函数执行改变的，不是恒定量)的值
    function<int(int, int)> partition = [&](int left, int right) -> int
    {
        if(left == right)
        {
            return nums[left];
        }
        // 为了应对 nt 破坏性数据，我们考虑把传统的两路快速选择优化为效率更高的三路选择方案，这样可以避免这种超多重复元素的情况下出现的效率退化问题
        // 规定：i 代表的是已经找出的所有小于找出的 pivot 值中最右侧的元素下标
        // j 代表的是已经找出的所有大于找出的 pivot 值中最左侧的元素下标
        // 我们之后用一个中间变量对整个区间进行遍历即可
        int i = left-1, j = right+1, t = left;
        // 随机选择一个 pivot 点
        int pivot = nums[rand() % (right-left+1)+left];
        while(t < j)
        {
            if(nums[t] > pivot)
            {
                swap(nums[++i], nums[t]);
                ++t;
            }
            else if(nums[t] < pivot)
            {
                swap(nums[--j], nums[t]);
                // 注意：此时我们不移动 t，因为不确定接下来移过来的这个值是不是一定是一个等于 pivot 的值，我们需要在后续循环中再重新做判断
            }
            // 相等，只移动 t
            else
            {
                ++t;
            }
        }
        // 循环结束时，i 指向了最靠右的比 nums[pivot] 大的元素下标
        // j 指向了最靠左的比 nums[pivot] 小的元素下标
        // 根据 k 和这个 pivot 所在的区间进行判断
        // pivot 的下标(从1开始)是：
        // [i-left+2, j-left]
        if(i-left+2 <= k && j-left >= k)
        {
            return pivot;
        }
        else if(i-left+2 > k)
        {
            return partition(left, i);
        }
        else 
        {
            k -= j-left;
            return partition(j, right);
        }
    };
    return partition(0, nums.size()-1);
}