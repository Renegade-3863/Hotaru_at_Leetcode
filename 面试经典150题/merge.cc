#include <iostream>

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
    {
        // 合并步骤，首先是定义两个遍历指针
        // 题目告诉我们，nums1 的初始长度就是 m+n
        // 所以这里可以逆向来进行遍历，这样可以避免额外复制数组的开销
        int i = m-1, j = n-1;
        // 从两个数组各自的最后一个元素开始向前比较遍历
        int k = m+n-1;
        // 当 k 指针移动到 nums1 的开头时，我们就可以判定，合并已经完成了
        // 同时，如果 i 或者 j 中的某一个指针也到了开头，我们也要退出循环
        while(k > 0 && i >= 0 && j >= 0)
        {
            // 比较 nums1[i] 与 nums2[j]，把更大的那一个放到 nums1[k] 处
            // 如果二者相等，优先放 nums2[j]，这样可以避免无意义的数据挪动
            if(nums2[j] >= nums1[i])
            {
                nums1[k--] = nums2[j--];
            }
            else
            {
                nums1[k--] = nums1[i--];
            }
        }
        // 在返回之前，我们还需要把为完成合并的部分合并进来
        while(i >= 0)
        {
            nums1[k--] = nums1[i--];
        }
        while(j >= 0)
        {
            nums1[k--] = nums2[j--];
        }
        return;
    }   
};