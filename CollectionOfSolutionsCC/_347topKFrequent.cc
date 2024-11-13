#include "Solution.h"

vector<int> Leetcode301_400::Solution::topKFrequent(vector<int>& nums, int k)
{
    // 很经典的一道快速选择类的题目，我们可以按照下面的方式来解决本题：
    // 第一步：预处理整个数组，提取出每种元素出现的次数
    // 这些数据可以保存在一个数组中，以便后续使用快速选择算法
    // 如何处理这个数组成为了一个小的细节问题
    // 我们可以使用类似映射的方式来进行数值的映射，因为很明显数值种类数会远小于 nums 的长度
    int maximum = *max_element(nums.begin(), nums.end()), minimum = *min_element(nums.begin(), nums.end());
    // 之后我们就可以根据 minimum 值进行预处理了
    // 注意：为了知道出现某种频率的某个数值是谁，我们在这个数组中保存的不能是一个单独的数，而应该额外再保存一个指向原数据种类的值
    // 举例：{3, 4} -> 4 这个元素出现了3次
    // 进行一下定义即可
    struct data 
    {
    public:
        data(int _val) : val(_val), freq(0) {}
        int freq;
        int val;
    };
    vector<data> board;
    // 初始化这个数组
    for(int i = minimum; i <= maximum; ++i)
    {
        board.emplace_back(i);
    }
    int n = nums.size();
    // 之后进行频次记录
    for(int i = 0; i < n; ++i)
    {
        // 注意映射关系
        // nums 中的数据映射到数组对应的下标上需要使用对于 minimum 的 offset
        ++(board[nums[i]-minimum].freq);
    }
    // 预处理完成，下面我们可以正式开始快速选择步骤
    // 定义一个用于快速选择的递归函数体 qSelect，以及一个用于存储最终结果的数组 res
    // 这个数组最后的大小一定是 k
    vector<int> res;
    // 定义为找出下标 [l, r] 部分中频次前 k 大的元素
    function<void(int, int, int)> qSelect = [&](int l, int r, int k)
    {
        // 整体流程类似快排的分区步骤
        // 我们为了使整体流程更稳定，避免很多重复元素的破坏性数据造成的影响，选用三路快选的优化措施
        // 首先选出一个值作为分区值 pivot
        // 假设我们就选 board[l]
        int pivot = board[l].freq;
        // 之后按照三路快排的方法，我们进行分区处理，大的在前，小的在后，中间是所有 freq 值为 k 的元素
        // 记：[l, i] 中的元素为确认大于 pivot 的值，(i, t) 中的元素为确认等于 pivot 的值，而 [j, r] 之间的元素为确认小于 pivot 的值
        // [t, j) 中的元素为还未进行处理的值
        int i = l-1, j = r+1;
        int t = l;
        // 循环结束条件是：t == j，即已经不存在还未进行处理的值
        while(t < j)
        {
            // 检查 board[t].freq
            // 1. board[t].freq < pivot
            // 那么我们需要把这个元素和 board[j-1] 交换，并更新 j 的值
            if(board[t].freq < pivot)
            {
                // 注意，此时我们无法确认交换过来的值是否等于 pivot，所以不能移动 t
                swap(board[--j], board[t]);
            }
            // 2. board[t].freq == pivot
            // 那么我们只需要移动 t，不需要其它任何处理
            else if(board[t].freq == pivot)
            {
                ++t;
            }
            // 3. board[t].freq > pivot
            // 那么我们只需要把这个元素和 board[i+1] 交换，并更新 i 的值
            // 因为此时我们能确定交换过来的值是等于 pivot 的，所以我们可以直接移动 t
            else
            {
                swap(board[++i], board[t++]);
            }
        }
        // 上面的循环结束后，我们可以确定的值：
        // i：最后一个小于 pivot 值的元素下标
        // j：第一个大于 pivot 值的元素下标
        // 此时我们只需要判断：k 是否在 [i+1, j-1] 这个区间中
        // 如果恰好在这个区间中，那么我们只需要截取这个数组中的前 k 个元素尾接到 res 中即可
        // 如果在区间左边，那么我们递归对左区间进行三路分区
        // 如果在区间右边，那么我们可以先把左边这些全部尾接到答案中，之后对右边的区间递归进行三路分区
        if(l+k-1 >= i+1 && l+k-1 <= j-1)
        {
            for(int t = l; t <= l+k-1; ++t)
            {
                res.push_back(board[t].val);
            }
            // 不用进一步递归深入了，直接返回即可
            return;
        }
        else if(l+k-1 < i+1)
        {
            qSelect(l, i, k);
        }
        else
        {
            for(int t = l; t <= j-1; ++t)
            {
                res.push_back(board[t].val);
            }
            qSelect(j, r, k-(j-l));
        }
    };
    // 我们只需要对 board 数组调用这个函数即可
    qSelect(0, board.size()-1, k);
    return res;
}