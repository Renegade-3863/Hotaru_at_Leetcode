#include "Solution.h"

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
{
    // 归并排序的 "归"，简单我们当然可以从前往后进行合并，但这样只能新开一个数组，最后复制回原数组(nums1)
    // 有人会想正序原地进行归并，但是这样会导致数据覆盖从而出现数据丢失
    // 考虑这样的情况
    // 我们都知道归并操作原来的版本中，有三个指针 i, j, k
    // 其中 k 指针是用来指向合并后的新数组中当前填写的位置的
    // 而这时，我们如果存在 i 指针指向了 k 指针之前的下标的话，就会出现数据丢失
    // 举例：我们现在合并到 nums1[2] 这个位置(k == 2)，同时有 i == 2
    // j 为随意值
    // 此时我们发现 nums2[j] 是小于 nums1[2] 的，那么你要怎么做？
    // 使用 k 把nums2[j] 的值放到 nums[2] 上？
    // 那我们很显然就把 nums1[2] 这个位置上原本的值给弄丢了
    // 看来正向的归并不正确，那么反向是否可行？
    // 本题给我们提供的 nums1 数组长度是 m+n，也就是说 nums1 数组的长度是足够存下两个数组中所有的元素的
    // 从这个角度想，我们如果令 i 和 j 分别从最后一位开始向前移动，那么是不是就能避免上面这种 i 被 k 给
    // 越过的情况了？
    // 显然是的
    // 最极端的情况下，nums1 中后面 n 个位置全部都被 nums2 中的元素占据的，那么此时我们 nums1[m-1] 位置处的元素仍然是安全的，没有被覆盖
    // 而这个是最有可能导致 nums1 的元素被覆盖的情况了，这种情况下都不会出现问题，说明我们的策略就是正确的
    // 直接速通代码即可
    int i = m-1, j = n-1, k = m+n-1;
    while(i >= 0 && j >= 0)
    {
        if(nums1[i] > nums2[j])
        {
            nums1[k--] = nums1[i--];
        }
        else
        {
            nums1[k--] = nums2[j--];
        }
    }
    // 如果退出是因为我们把 nums2 中的元素用光了，那实际上前面 nums1 的元素都不用动了，可以直接返回
    if(i >= 0)
    {
        return;
    }
    // 否则才需要把前面剩下的内容用 nums2 中剩下的元素逐一替换
    while(j >= 0)
    {
        nums1[k--] = nums2[j--];
    }
    return;
}