class Solution
{
public:
    vector<int> sortArray(vector<int>& nums)
    {
        // 简单复习一下快速排序
        // 经典的快速排序是两路的，我们可以简单实现一下
        function<void(int, int)> quickSort = [&](int l, int r) -> void
        {
            // 定义一个递归的结束条件
            if(l >= r)
            {
                return;
            }
            // 快排的基本思想是，从要排序的区间中，选出一个值作为 pivot 值
            // 之后把区间中比 pivot 值大的元素，都放到数组右侧
            // 比 pivot 值小的元素，都放到数组左侧
            // 我们可以用双指针来实现这一点
            // j 代表的是从左往右，已知的最后一个不大于 pivot 值的元素的下标（初始的时候赋值为 -1）
            int j = l-1;
            // 取一个 [l, r] 中间的随机数作为 pivot 值
            int pivot = rand() % (r-l+1) + l;
            // 把 pivot 放到 nums[r] 处，用于比较
            swap(nums[pivot], nums[r]);
            for(int i = l; i < r; ++i)
            {
                // 如果当前元素是不大于 pivot 值的，那么我们把它放到 nums[++j] 上
                if(nums[i] <= nums[r])
                {
                    // 注意，这里换过来的数一定要么是 nums[i] 自己，要么是一个大于 nums[pivot] 的值
                    swap(nums[i], nums[++j]);
                }
            }
            // 把 nums[pivot] 放到正确的位置上去
            swap(nums[++j], nums[r]);
            // cout << nums[pivot] << endl;

            // 现在，j 就是一个分界线，左侧的都是不大于 nums[j] 的元素，右侧的都是大于 nums[pivot] 的元素
            // 我们进行递归排序即可
            quickSort(l, j-1);
            quickSort(j+1, r);
        };
        quickSort(0, nums.size()-1);
        return nums;
    }
};

// 附赠一份三路快排（bushi）
class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        // 传统的两路快排会直接被 O(n^2) 的特殊案例冲爆
        // 所以我们需要考虑更优的三路快排
        // 简单来说，就是把原来的 [小于等于] [大于] 的拆分策略
        // 优化成 [小于] [等于] [大于] 的三路拆分
        // 这样就可以避免大量重复元素造成的 O(n^2) 性能下降了
        function<void(int, int)> threeWayQuickSort = [&](int l, int r) -> void 
        {
            if(l >= r)
            {
                return;
            }
            // 首先还是要选择一个数作为 pivot 值
            // 我们还是用 rand 函数来处理
            int pivot = rand() % (r-l+1)+l;
            // 交换 nums[r] 和 nums[pivot]
            swap(nums[pivot], nums[r]);
            // 之后，用两个标记指针和一个遍历指针来处理三路拆分
            // 我们维护一个循环不变式：
            // nums[l..j] 中的元素，都是严格小于 nums[r] 的
            // nums[k..r-1] 中的元素，都是严格大于 nums[r] 的
            // nums[r] 不参与这个循环，我们在循环里不对它进行处理
            // 而 nums[j+1..i-1] 中的元素，都是严格等于 nums[r] 的
            int j = l-1, k = r, i = l;
            // 因为一些原因，这里不能用 for 循环，后面会说明原因
            while(i < k)
            {
                // 检查 nums[i] 与 nums[r] 的大小关系
                // 1. nums[i] < nums[r]
                // 这时可以安全地把 nums[i] 与 nums[++j] 进行交换，交换过来的一定是一个等于 nums[r] 的元素，所以我们也可以自然地后移一次 i 指针
                if(nums[i] < nums[r])
                {
                    swap(nums[i], nums[++j]);
                    ++i;
                }
                // 2. nums[i] == nums[r]
                // 这时我们不用做任何事，直接后移 i 指针即可
                else if(nums[i] == nums[r])
                {
                    ++i;
                }
                // 3. nums[i] > nums[r]
                // 此时我们可以把 nums[i] 与 nums[--k] 交换
                // 但是注意：这一步交换过来的，我们并不确定是不是一定是一个等于 nums[r] 的值，所以不能直接移动 i 值
                // 这也是使用 while 循环而不是 for 循环的原因
                else
                {
                    swap(nums[i], nums[--k]);
                }
            }
            // 最后，把 nums[r] 换到正确的位置上
            // 这里依然确保换到 r 处的是一个大于 pivot 值的元素
            swap(nums[r], nums[i]);
            // 处理完了一轮三路拆分
            // 我们还需要排序的部分就是：
            // 左侧：[l, j]
            // 右侧：[k+1, r]
            // 其余部分均为等于 pivot 值的部分，不需要继续递归
            threeWayQuickSort(l, j);
            threeWayQuickSort(k+1, r);
        };
        threeWayQuickSort(0, nums.size()-1);
        return nums;
    }
};

// 再附赠一份堆排序（bushi）
// 根据下标 i，确认它的左孩子的下标
// 假设 i == 0，那么它的左侧孩子就应该是 1，右侧孩子就应该是 2
int leftChild(int i)
{
    return 2*i+1;
}
// 根据下标 i，确认它的右孩子的下标
int rightChild(int i)
{
    return 2*i+2;
}
// 我们还需要一个函数来维护某个元素 i 的大顶堆性质（也就是 i 比它左右孩子的值都要大
void max_heapify(vector<int>& nums, int idx, int heapSize)
{
    // 对 nums[idx] 进行维护
    // 我们用一个类似递归的方法来对数组的性质进行维护
    int l = leftChild(idx), r = rightChild(idx), ma = idx;
    if(l < heapSize && nums[l] > nums[ma])
    {
        ma = l;
    }
    if(r < heapSize && nums[r] > nums[ma])
    {
        ma = r;
    }
    if(ma != idx)
    {
        swap(nums[ma], nums[idx]);
        // 递归维护对应 ma 处的那个新值即可
        max_heapify(nums, ma, heapSize);
    }
}

// 之后就是基于已有的数组简历大顶堆的 helper function
void buildMaxHeap(vector<int>& nums, const int heapSize)
{
    // 根据一些堆的性质
    // 假设一共有 heapSize 个元素
    // 那么我们实际上只需要维护其中 heapSize/2 个元素的大顶堆性质即可
    // 对于一个总长度为 heapSize 的数组，它会有 heapSize/2 个非叶子结点
    // 而另外 heapSize 个是叶子结点
    // 所以我们只需要维护 [0, heapSize/2-1] 个元素即可
    for(int i = heapSize/2-1; i >= 0; --i)
    {
        max_heapify(nums, i, heapSize);
    }
}

class Solution
{
public:
    vector<int> sortArray(vector<int>& nums)
    {
        // 先简单回顾一下堆排序的基本逻辑
        // 本质上用的是一个大顶堆
        int n = nums.size();
        // 先构建大顶堆
        buildMaxHeap(nums, n);
        int heapSize = n;
        for(int i = 0; i < n-1; ++i)
        {
            swap(nums[0], nums[heapSize-1]);
            max_heapify(nums, 0, --heapSize);
        }
        return nums;
    }
};

// 再附赠一份基数排序版本（bushi）
class Solution
{
public: 
    vector<int> sortArray(vector<int>& nums)
    {
        // 基数排序的基本方法是：
        // 从低位到高位，按位一个个去
        
    }
};