#include "Solution.h"

// 按照桶排序的传统方案处理，几乎要超时了，只超过了 5% 
int Leetcode101_200::Solution::maximumGap(vector<int>& nums)
{
    int n = nums.size();
    if(n < 2)
    {
        return 0;
    }
    // 本题如果不要求线性时间复杂度，同时使用线性空间复杂度，那么可以很简单地通过 O(nlogn) 的时间复杂度进行排序，之后再通过 O(n) 的线性时间遍历得到结果
    // 不过这显然不满足时间复杂度
    // 回顾所有排序算法，满足线性时间的基本就只有计数排序和桶排序
    // 我们使用桶排序来实现
    // 规定桶的大小为 500
    // 其实这里这么大的桶，几乎就是 O(nlogn) 了，不过还是说服一下自己 O(500log500) 是常数吧。。。
    const int bucketSize = 500;
    // 获取整个数组中的最小值和最大值，时间为 O(n)
    int minimum = INT_MAX;
    int maximum = INT_MIN;
    for(int i = 0; i < n; ++i)
    {
        minimum = min(minimum, nums[i]);
        maximum = max(maximum, nums[i]);
    }
    // 根据最大最小值，分配对应数量的桶
    // 对于少于一个桶的部分，也要多分配一个桶
    int bucketCnt = (maximum-minimum+1)/bucketSize + ((maximum-minimum+1)%bucketSize > 0);
    // 举例：maximum: 3, minimum: 53 -> 51 个，需要 51 / 10 + 1 = 6个
    // [3, 12]
    // [13, 22]
    // [23, 32]
    // [33, 42]
    // [43, 52]
    // [53, 53]
    // 写一个对每个桶内部进行快速排序的快排回调函数
    function<void(vector<int>&, int, int)> quickSort = [&](vector<int>& subNums, int i, int j) {
        if(i >= j)
        {
            return;
        }
        // 生成一个 [i, j] 之间的随机下标
        int random = rand() % (j-i+1) + i;
        // 进行切割操作
        swap(subNums[random], subNums[j]);
        int left = i-1;
        for(int right = i; right < j; ++right)
        {
            if(subNums[right] <= subNums[j])
            {
                swap(subNums[++left], subNums[right]);
            }
            // 否则直接跳过，什么也不做
        }
        swap(subNums[++left], subNums[j]);
        if(left == j && nums[i] == nums[j])
        {
            return;
        }
        quickSort(subNums, i, left-1);
        quickSort(subNums, left+1, j);
    };
    vector<vector<int>> buckets(bucketCnt, vector<int>());
    // 对每个桶进行填充
    for(int i = 0; i < n; ++i)
    {
        buckets[(nums[i]-minimum)/bucketSize].push_back(nums[i]);
    }
    // 填充完毕后，对每个桶实现快速排序
    for(int i = 0; i < bucketCnt; ++i)
    {
        quickSort(buckets[i], 0, buckets[i].size()-1);
    }
    // 按顺序把内容打印回原数组，顺便记录最大的间距
    int idx = 0, res = 0;
    for(int i = 0; i < bucketCnt; ++i)
    {
        for(int j = 0; j < buckets[i].size(); ++j)
        {
            nums[idx] = buckets[i][j];
            if(idx > 0)
            {
                res = max(res, nums[idx]-nums[idx-1]);
            }
            ++idx;
        }
    }
    return res;
}

// 题解给了一个基于基本桶排序的改进优化方案，不过那个方案比较 problem specific，我们不用过分关注那个方案
// 再尝试一下基数排序
// 回忆：基数排序以计数排序这个稳定排序算法作为底层排序方案，按数位为基础对一组数进行排序
int maximumGap(vector<int>& nums)
{
    // 基数排序需要按数位进行遍历排序，因而我们仍然需要超出整个数组中数值最大的那个元素，因为它代表了整个数组最大的数位个数
    int n = nums.size();
    if(n < 2)
    {
        return 0;
    }
    int exp = 1;
    // 找出 nums 中最小的元素
    int minimum = *min_element(nums.begin(), nums.end());
    // 注意一点，基数排序不适用于含有负数的数组，对于含有负数的数组，我们需要对整个数组先进行 "归正化"
    // 即先把所有元素转换成最小值为 0 的同 offset 数组，然后再对这个数组进行排序，最后把这个 offset 再添回去回复原值
    // 虽然本题规定了 nums 中的元素不会有负数，不过我们还是加上归正化操作，这样更加 robust
    // 归正化处理
    if(minimum < 0)
    {
        for(int i = 0; i < n; ++i)
        {
            nums[i] -= minimum;
        }
    }
    // 找出 nums 中最大的元素
    int maximum = *max_element(nums.begin(), nums.end());
    // 按位进行计数排序
    // buf 存储按每一位排好序之后的结果数组
    vector<int> buf(n);
    while(maximum >= exp)
    {
        // 存储每一个数字的出现次数
        vector<int> cnt(10);
        for(int i = 0; i < n; ++i)
        {
            ++cnt[nums[i]/exp%10];
        }
        // 记录当前位上不小于当前数字的值的总个数
        for(int i = 1; i < 10; ++i)
        {
            cnt[i] += cnt[i-1];
        }
        // 按照从后往前的顺序重新遍历整个数组并填数，注意这是为了保证计数排序的稳定性！！！
        for(int i = n-1; i >= 0; --i)
        {
            buf[cnt[nums[i]/exp%10]-1] = nums[i];
            --cnt[nums[i]/exp%10];
        }
        // 把按当前位存好的数据复制回原数组
        copy(buf.begin(), buf.end(), nums.begin());
        // 继续按下一位进行计数排序
        exp *= 10;
    }
    int res = 0;
    // 归正化恢复
    for(int i = 0; i < n; ++i)
    {
        nums[i] += minimum;
    }
    // 计算结果
    for(int i = 1; i < n; ++i)
    {
        res = max(res, nums[i]-nums[i-1]);
    }
    return res;
}