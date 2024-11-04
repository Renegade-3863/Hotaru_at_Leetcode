#include "Solution.h"

int Leetcode301_400::Solution::countSmaller(vector<int>& nums)
{
    // 对于本题，利用有序数组+二分查找方法函数的策略可以很好的解决，但是这样使用了太多语言本身的库函数
    // 不利于我们理解算法本身
    // 考虑使用更加巧妙的归并排序过程算法
    // 归并排序有这样一种性质：
    // 在对大的数组进行排序前，我们会先对两个半边数组进行排序
    // 而排序完成后的左右两部分的元素，在前半和后半的元素之间的先后次序是不会受到影响的
    // 考虑到经过了部分归并排序的数组元素可能会失去对应的位置信息
    // 那么我们可以针对每一个数组元素保存一个存储了对应元素和具体的 "原下标" 的 pair 变量
    // 之后针对每个元素的 "原位置" 信息，对相应的数据进行更新
    vector<pair<int, int>> vals;
    int n = nums.size();
    for(int i = 0; i < n; ++i)
    {
        vals.push_back(make_pair<int&, int&>(nums[i], i));
    }
    // 之后对这个 vals 数对数组进行实际的归并排序，因为对于这个归并，我们能实际的知道每个元素原来在数组中的位置下标
    // 归并前，存储一个全局的结果变量 res
    vector<int> res(n, 0);
    // 设定一个归并函数体和一个 merge 合并函数体
    function<void(int, int)> mergeSort = [&](int left, int right)
    {
        // 递归结束条件
        // 区间长度为1，不需要合并操作，也不需要深入递归，更不需要记录任何满足题意的结果，直接返回即可
        if(left == right)
        {
            return;
        }
        // 取出区间中点
        int mid = ((right-left)>>1)+left;  
        // 之后先对两半分别进行归并排序，注意，我们的归并排序已经在过程中记录了对应子区间中各自位置上元素右侧小于它们的元素个数了
        mergeSort(left, mid);
        mergeSort(mid+1, right);
        // 之后，考虑当前这两半已经排好序的元素，我们需要对其进行合并操作
        int i = left, j = mid+1;
        vector<pair<int, int>> tmp;
        while(i <= mid && j <= right)
        {
            // 提问：这里为什么不使用 > 关系，而是使用 <= 关系？
            // 首先，如果 vals[i].first > vals[j].first，那么很明显我们没办法明确知道当前这个 i 到底大于几个元素，因为只知道 j 以及它左边
            // 直到 mid+1 的元素是小于 vals[i].first 的，可是如果此时我们就更新了 res[vals[i].second] 的结果，那么很明显是有问题的
            // 因为如果后面下一个 j 位置处的元素也是小于 i 位置处元素的，那么我们会重复更新 i 处位置的结果，显然这样是错的
            // 再说明一下按 <= 更新的正确性
            // 由于归并排序，我们只会移动两个指针中指向元素更小的那一侧，所以当下面的情况出现时，有如下隐含条件
            // vals[i].first 是大于所有 vals[k].first, k < j 的，否则在前面，i 就已经被更新掉了，不会比较到这对 i 和 j
            // 那么相当于我们此时就找到了对于 vals[i].first 这个元素来说所有在右半边比它小的元素总个数了，就是 j-mid-1 个
            if(vals[i].first <= vals[j].first)
            {
                res[vals[i].second] += j-mid-1;
                tmp.push_back(vals[i++]);
            }
            // 那么又有人会提出：在这里，每找到一个逆序对，就给对应位置的结果次数+1不行吗？
            // 虽然比较难想，但是还是必须说明，这样的更新策略是错误的
            // 原因如下：
            // 我们在这种时候，根据归并排序的规则，会更新更小的那一侧的元素指针，而不是更大的那一侧的元素指针，因而对于更大的那一侧的元素，它再右边的元素就不再能跟 "看到" 这个已经被跳过的较小元素了
            // 所以此时更大的那一个元素右侧的更大元素就会丢失掉当前这个较小元素的计数，从而导致出错
            else
            {
                tmp.push_back(vals[j++]);
            }
        }
        while(i <= mid)
        {
            // 这里的更新策略很好理解
            res[vals[i].second] += right-mid;
            tmp.push_back(vals[i++]);
        }
        while(j <= right)
        {
            tmp.push_back(vals[j++]);
        }
        for(int i = left, j = 0; i <= right; ++i, ++j)
        {
            vals[i] = tmp[j];
        }
    };
    // 调用即可
    mergeSort(0, nums.size()-1);
    return res;
}

// 后续更新有关线段树/树状数组的相关解法