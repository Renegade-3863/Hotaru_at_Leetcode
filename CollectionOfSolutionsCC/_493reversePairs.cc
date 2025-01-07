#include "Solution.h"

// 自己写的第一版代码，有一个很关键的错误，具体原因可以读一下代码，不想读的可以直接看第二版正确的代码
int Leetcode401_500::Soltuion::reversePairs(vector<int>& nums)
{
    // 逆序对类问题基本都是，经典的归并排序问题，不过本题也可以用诸如线段树等高级数据结构来实现，不过那样实现起来代码量太大，这里不再使用
    // 定义一个归并函数：merge，在这个函数中对两段有序元素进行检查
    // [l, mid] 和 [mid+1, r] 两段元素分别有序
    // 从定义上说，这个函数找的是：两端分别处在 [l, mid] 和 [mid+1, r] 中的所有元素对，这一定义可以满足任意大小的 [l, r] 范围
    // res 代表全局的答案个数，我们在 merge 函数中对它进行修改
    int res = 0;
    function<void(int, int, int)> merge = [&](int l, int mid, int r) -> void
    {
        // 在这个函数中，我们假设 nums[l..mid] 和 nums[mid+1..r] 分别有序
        // 之后要做的就是用双指针遍历这两段元素，检查两部分中所有的 "重要翻转对"
        // 同时也需要完成对 [l, r] 之间元素的排序 (因为两部分之间的元素并不完全是有序的)
        // 排序的部分本质上和归并排序并没有区别
        // 按照归并排序的规则，我们需要额外创建一个 temp 数组
        // 这个数组用于保存 [l, r] 中元素的有序结果
        vector<int> temp;
        int k = 0, i = l, j = mid+1;
        // 我们按顺序遍历两段元素
        // 退出条件是：任意一个指针到达了对应的终点
        while(i <= mid && j <= r)
        {
            // 获取两个序列的头部元素
            int val1 = nums[i], val2 = nums[j];
            // 如果 val1 > 2*val2 是成立的，那么我们对 res 进行修改
            // 注意，因为数组是有序的，所以很明显对于 val2 左侧的所有元素 (它们都小于 val2)
            // 都应该有 val1 > 2*val2 > valk (valk 是任意一个属于 [mid+1..j) 的元素)
            if(val1 > 2*val2)
            {
                // [i..mid] 中的所有元素都能和 val2 组成翻转对，我们进行记录
                res += (mid-i+1);
                // 由于 val1 > 2*val2，那么很明显有 val1 > val2，所以我们此时很明显需要把 val2 放到 temp 结尾处
                // 同时，别忘了后移 j 指针
                temp.push_back(nums[j++]);
            }
            // 否则，如果 val1 不大于 val2，那么我们规定此时是把 val1 放到 temp 结尾处
            else if(val1 <= val2)
            {
                // 别忘了后移 i 指针
                temp.push_back(nums[i++]);
            }
            // 最后一种情况：val1 > val2 && val1 <= 2*val2
            // 后期说明，这一段代码是整份答案错误的核心原因
            // 因为 i 右侧的元素都比它大，所以我们如果在这里就结束对 j 的检查，可能会忽略掉可能的，满足 nums[i] > nums[j] 的其它 i，所以这里不能丢掉 j
            // 但是，既然不能丢掉 j，而从归并排序本身的角度来分析，我们这里也不能把 i 接到 temp 结尾，否则 "有序" 的假设就不再成立了，所以我们就必须把 temp 的构建和前面的数据检查分离开来进行了
            // 此时我们依然需要把 val2 接到 temp 结尾处
            else
            {
                temp.push_back(nums[j++]);
            }
        }
        // 最后，如果两段中任意一段还没填写完成，那么就需要把那一段接到 temp 结尾
        while(i <= mid)
        {
            temp.push_back(nums[i++]);
        }
        while(j <= r)
        {
            temp.push_back(nums[j++]);
        }
        // 最后是把对应元素复制回 nums 数组中
        for(int k = 0; k < temp.size(); ++k)
        {
            nums[l+k] = temp[k];
        }
        // 处理完成，返回结果即可
    };
    // 按照归并排序的传统，我们还需要一个外层的调用函数，mergeSort
    function<void(int, int)> mergeSort = [&](int l, int r)
    {
        // 设定一个基本情况：l == r 时，区间中只有一个元素，那么我们不用处理了，直接返回即可
        if(l == r)
        {
            return;
        }
        // 最基本的逻辑是对 nums[l..r] 之间的元素进行归并排序，所以我们使用递归的方式进行处理
        // 取中点
        int mid = ((r-l)>>1)+l;
        // 对左半进行归并排序，中间计算对应的翻转对个数
        mergeSort(l, mid);
        // 对右半进行归并排序，中间计算对应的翻转对个数
        mergeSort(mid+1, r);
        // 最后是计算分隔在两端的翻转对个数
        merge(l, mid, r);
    };
    // 调用 mergeSort 函数，之后返回 res 即可
    mergeSort(0, nums.size()-1);
    return res;
}

// 第二版：对 merge 函数做了修正
int reversePairs(vector<int>& nums)
{
    // 逆序对类问题基本都是，经典的归并排序问题，不过本题也可以用诸如线段树等高级数据结构来实现，不过那样实现起来代码量太大，这里不再使用
    // 定义一个归并函数：merge，在这个函数中对两段有序元素进行检查
    // [l, mid] 和 [mid+1, r] 两段元素分别有序
    // 从定义上说，这个函数找的是：两端分别处在 [l, mid] 和 [mid+1, r] 中的所有元素对，这一定义可以满足任意大小的 [l, r] 范围
    // res 代表全局的答案个数，我们在 merge 函数中对它进行修改
    int res = 0;
    function<void(int, int, int)> merge = [&](int l, int mid, int r) -> void
    {
        // 在这个函数中，我们假设 nums[l..mid] 和 nums[mid+1..r] 分别有序
        // 之后要做的就是用双指针遍历这两段元素，检查两部分中所有的 "重要翻转对"
        // 同时也需要完成对 [l, r] 之间元素的排序 (因为两部分之间的元素并不完全是有序的)
        int i = l, j = mid+1;
        // 我们按顺序遍历两段元素
        // 退出条件是：任意一个指针到达了对应的终点
        while(i <= mid && j <= r)
        {
            // 获取两个序列的头部元素
            // 避免数值过大造成溢出，使用 long long 对数据进行存储
            long long val1 = nums[i], val2 = nums[j];
            // 如果 val1 > 2*val2 是成立的，那么我们对 res 进行修改
            // 注意，因为数组是有序的，所以很明显对于 val2 左侧的所有元素 (它们都小于 val2)
            // 都应该有 val1 > 2*val2 > valk (valk 是任意一个属于 [mid+1..j) 的元素)
            if((long long)val1 > (long long)2*val2)
            {
                // [i..mid] 中的所有元素都能和 val2 组成翻转对，我们进行记录
                res += (mid-i+1);
                // 由于 val1 > 2*val2，那么很明显有 val1 > val2，所以我们此时很明显需要把 val2 放到 temp 结尾处
                // 同时，别忘了后移 j 指针
                // 此时 nums[j] 这个元素所有可能的配对都已经判断完成了
                ++j;
            }
            // 否则，说明 nums[i] 这个元素所有可能的配对都已经判断完成了，我们也需要右移 i 指针
            else 
            {
                ++i;
            }
        }
        // 根据第一版代码中描述的理由，我们这里才开始实际对两部分数据进行合并
        // 重置 i 和 j
        // 排序的部分本质上和归并排序并没有区别
        // 按照归并排序的规则，我们需要额外创建一个 temp 数组
        // 这个数组用于保存 [l, r] 中元素的有序结果
        vector<int> temp(r-l+1, 0);
        i = l; 
        j = mid+1;
        int k = 0;
        while(i <= mid && j <= r)
        {
            if(nums[i] <= nums[j])
            {
                temp[k++] = nums[i++];
            }
            else
            {
                temp[k++] = nums[j++];
            }
        }
        // 最后，如果两段中任意一段还没填写完成，那么就需要把那一段接到 temp 结尾
        while(i <= mid)
        {
            temp[k++] = nums[i++];
        }
        while(j <= r)
        {
            temp[k++] = nums[j++];
        }
        // 最后是把对应元素复制回 nums 数组中
        for(int k = 0; k < temp.size(); ++k)
        {
            nums[l+k] = temp[k];
        }
        // 处理完成，返回结果即可
    };
    // 按照归并排序的传统，我们还需要一个外层的调用函数，mergeSort
    function<void(int, int)> mergeSort = [&](int l, int r)
    {
        // 设定一个基本情况：l == r 时，区间中只有一个元素，那么我们不用处理了，直接返回即可
        if(l == r)
        {
            return;
        }
        // 最基本的逻辑是对 nums[l..r] 之间的元素进行归并排序，所以我们使用递归的方式进行处理
        // 取中点
        int mid = ((r-l)>>1)+l;
        // 对左半进行归并排序，中间计算对应的翻转对个数
        mergeSort(l, mid);
        // 对右半进行归并排序，中间计算对应的翻转对个数
        mergeSort(mid+1, r);
        // 最后是计算分隔在两端的翻转对个数
        merge(l, mid, r);
    };
    // 调用 mergeSort 函数，之后返回 res 即可
    mergeSort(0, nums.size()-1);
    return res;
}