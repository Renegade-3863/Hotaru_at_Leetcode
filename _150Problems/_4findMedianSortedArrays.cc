class Solution
{
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
    {
        // 定义一个找出 (nums1, nums2) 中第 k 小的元素的 helper function
        function<double(int, int, int, int, int)> findKthSortedArrays = [&](int l1, int r1, int l2, int r2, int k) -> double
        {
            // 首先，我们取 arr1 和 arr2 中每一个位于 k/2-1 位置上的元素（如果 len1 <= k/2 或 len2 <= k/2，那么就直接取对应的 len1/len2
            // 之所以要取 k/2-1 位置上的元素
            // 假设我们要取第 4 小的元素，那么两个数组中都应该取 4/2 -> 第 2 个位置，那么对应的下标就是 k/2-1 = 1
            // 而如果要取第 5 小的元素，那么两个数组中都应该取 5/2 -> 第 2 个位置，那么对应的下标也是 k/2-1 = 1
            // 假设最后选择的两个数组中的下标分别为 idx1 和 idx2
            // 那么如果 nums1[idx1] <= nums2[idx2]，那么说明 nums1[idx1] 以及它左边直到 nums1[l1] 为止的所有元素都不可能是排序后第 k 小的元素
            // 而如果 nums1[idx] > nums2[idx]，那么就反过来，nums2[idx2] 以及它左边直到 nums2[l2] 为止的所有元素都不可能是排序后第 k 小的元素
            // 通过这样的方法，我们就可以每次省下 k/2 个元素，从而提高整体的运行效率了
            // 整体的运行效率预估在 O(logk)/O(log(m+n))
            
            // 下面考虑具体实现：
            // 首先是结束条件，如果 l1 > r1 || l2 > r2
            // 那么我们可以直接返回另一个数组中相对下标为 k-1 的元素
            if(l1 > r1)
            {
                // 注意，这里假设第 k 大的值一定存在，也就是 k < m+n
                return nums2[l2+k-1];
            }
            if(l2 > r2)
            {
                return nums1[l1+k-1];
            }
            // 否则 l1 <= r1 && l2 <= r2
            // 那么我们继续检查 k 是否为 1 
            // 如果 k 为 1，那么我们直接检查 nums1 和 nums2 的首元即可
            if(k == 1)
            {
                return nums1[l1] <= nums2[l2] ? nums1[l1] : nums2[l2];
            }
            // 此时 l1 <= r1 && l2 <= r2 && k > 1
            // 属于正常的递归范畴
            // 在递归部分，计算出两个数组中 "应该" 取到的下标值
            // 如果超出了对应数组的范围，就取可取范围的最远结果
            int idx1 = l1+k/2-1 > r1 ? r1 : l1+k/2-1, idx2 = l2+k/2-1 > r2 ? r2 : l2+k/2-1;
            // cout << idx1 << " " << idx2 << endl;
            // 之后，取出对应下标上的元素进行比较，并舍弃掉较小的那一部分
            if(nums1[idx1] <= nums2[idx2])
            {
                // 此时我们舍弃掉 nums1 中的前 (idx1-l1+1) 个元素即可
                return findKthSortedArrays(idx1+1, r1, l2, r2, k-(idx1-l1+1));
            }
            // 此时我们舍弃掉 nums2 中的前 (idx2-l2+1) 个元素即可
            return findKthSortedArrays(l1, r1, idx2+1, r2, k-(idx2-l2+1));
        };
        // 定义完成，我们可以调用上面的函数
        // 我们的目标就可以简化成：
        // 求解 nums1 与 nums2 中第 (m+n+1)/2 大与第 (m+n+2)/2 大的元素
        // 比如 m = 4, n = 6，那么就是找第 (4+6+1)/2 = 5 大与第 (4+6+2)/2 = 6 大的元素
        // 二者求平均即为结果
        int m = nums1.size(), n = nums2.size();
        return (findKthSortedArrays(0, m-1, 0, n-1, (m+n+1)>>1) + findKthSortedArrays(0, m-1, 0, n-1, (m+n+2)>>1))*0.5;
    }
}