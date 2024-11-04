#include "Solution.h"

void Leetcode301_400::Solution::wiggleSort2(vector<int>& nums)
{
    // 如果还想用 280 题的贪心策略来解决本题，会发现行不通了，不信邪的可以自己试试，循环不变式没法维护
    // 学习了一下三叶的方案，使用我们曾经用过的三数排序(波兰国旗方法)，我们可以通过一个中位数值，把整个 nums 数组分成 [小数，中位数，大数] 的顺序
    // 之后，我们指定两个指针：
    // 第一个指针指向分组后数组的中间位置元素
    // 第二个指针指向大数部分的最后一个元素
    // 按照 "左一右一" 的顺序一个一个地往最终的结果数组中放入元素
    // 直到用完整个数组中全部的元素即可
    // 正确性证明：
    // 我们每次放入的元素对都能满足 "第一个小于第二个" 的性质
    // 相邻添加的元素相等的情况是唯一会导致构造失败的情况
    // 而在这种情况下，整个数组一定是不存在对应结果的
    // 因为此时中位数的个数已经超过了数组的半数 (简单写写画画看一看就能看出来原因了)
    // 剩下的代码环节就不难了
    int n = nums.size();
    // 第一个问题：如何找出一组数的中位数？
    // 这一步可以通过快速选择来实现，可是，基于我们的经验，快速选择和快排的性质类似，都会遇到全等数组这样的破坏性数据
    // 所以我们依然可以考虑应用三路快选来加速这个查找过程
    function<int(int, int, int)> qSelect = [&](int left, int right, int k) -> int
    {
        // 我们定义这个子问题为：在 nums[left, right] 中找出第 k 大的元素
        // 对于当前子数组，我们选定一个 pivot 值，进行三路切分
        // 先随机取一个下标上的值作为切分值
        int pivot = nums[left];
        // 这里因为我们提前取出了 pivot 值，所以不需要使用传统两路快排中的交换操作，效率更高
        // 定义两个指针，两个指针，加上我们的遍历变量 t，可以将原子数组切分成四部分：[left, i] (i, t) [t, j) [j, right]
        // 定义为：[left, i] 是确保了小于 pivot 值的部分，[j, right] 是确保了大于 pivot 值的部分，(i, t) 是明确等于 pivot 的部分，[t, j) 是还未确认的部分
        // 我们使用一个遍历变量 t 对原数组进行遍历
        // 遍历的退出条件为：t == j
        // 即已经不存在未确认的部分了
        int i = left-1, j = right+1, t = left;
        while(t < j)
        {
            // 只需要按一般的分组逻辑进行分配即可
            if(nums[t] < pivot)
            {
                // 小于 pivot 的值，把这个和下标 i+1 位置处的元素进行交换
                // 注意，因为这里我们换过来的元素一定是等于 pivot 的，因而我们可以直接同步移动 t 循环变量
                swap(nums[t++], nums[++i]);
            }
            else if(nums[t] == pivot)
            {
                ++t;
            }
            else
            {
                // 大于 pivot 的值，此时我们需要把这个值和下标 j-1 处的元素进行交换
                // 而这里，我们交换过来的元素不一定是等于 pivot 的，因而我们不能同步移动 t 循环变量
                swap(nums[t], nums[--j]);
            }
        }
        // 上面的循环结束后，我们就拿到了两个值：i 和 j
        // 分别对应最后一个小于 pivot 的值的下标和第一个大于 pivot 的值的下标
        // 那么此时我们只需要检查 pivot 值所在的区间有没有覆盖 k 值即可决定下一步操作
        // 注意对应关系的细节问题，我们要找的是从 left 开始的第 k 个值
        // pivot 值覆盖的区间是 [i+1, j-1]
        // k 值映射是 left+k-1
        // k 值的映射在我们找到的区间中，那么说明我们已经找到了这个元素
        if(left+k-1 >= i+1 && left+k-1 <= j-1)
        {
            return pivot;
        }
        else if(left+k-1 < i+1)
        {
            // 此时说明第 k 大的值在左边的区间中，我们可以修改区间，递归查找
            return qSelect(left, i, k);
        }
        // 其它情况下，我们要找的第 k 大的元素就在右边的区间中，同样递归查找即可
        // 注意：我们此时要找的就不是第 k 大的元素，而是第 k-(j-left+1) 大的元素了，因为我们丢弃了左边更小的 j-left 个元素
        return qSelect(j, right, k-(j-left));
    };  
    // 找出中位数
    int median = qSelect(0, n-1, (n+1) >> 1);
    // 完成了上面的查找过程，我们之后要做的就是根据这个中位数对原数组再进行一轮三路分组
    function<void(int, int)> threePatrition = [&](int left, int right)
    {
        // 在这里我们直接使用上面找出的 median 值进行三路分组
        int i = left-1, j = right+1, k = left;
        while(k < j)
        {
            if(nums[k] < median)
            {
                swap(nums[k++], nums[++i]);
            }
            else if(nums[k] == median)
            {
                ++k;
            }
            else 
            {
                swap(nums[k], nums[--j]);
            }
        }
    };
    threePatrition(0, n-1);
    // 结束后，我们只需要按上面确定好的方案进行遍历填数即可
    int l = (n-1)>> 1, r = n-1;
    vector<int> res;
    for(int i = 0; i < n; ++i)
    {
        // 奇数：填写一个大数端数据
        if(i%2)
        {
            res.push_back(nums[r--]);
        }
        // 偶数：填写一个小数端数据
        else
        {
            res.push_back(nums[l--]);
        }
    }
    copy(res.begin(), res.end(), nums.begin());
    return;
}