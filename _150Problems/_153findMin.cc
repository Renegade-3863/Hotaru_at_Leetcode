class Solution
{
public:
    int findMin(vector<int>& nums)
    {
        // 简单分析一下问题本身
        // 显然是一个二分类的问题
        // 我们可以做出下面的假设：
        // 答案可能存在的范围为 [l, r]
        // 每次取中点处的值：nums[mid]，其中 mid = (l+r)/2
        // 如果 nums[mid] > nums[r]，那么说明旋转后的最小值一定在 (mid. r] 之中
        // 而如果 nums[mid] < nums[r]，那么说明旋转后的最小值一定在 [l, mid] 之间
        // 这两种情况下，我们都可以丢弃掉 [l, r] 的一半
        // 而如果 l == r 了，那么说明我们就已经定位到了最小的元素，直接返回即可
        int l = 0, r = nums.size()-1;
        while(l < r)
        {
            int mid = ((r-l)>>1)+l;
            if(nums[mid] > nums[r])
            {
                l = mid+1;
            }
            else
            {
                r = mid;
            }
        }
        return nums[l];
    }
};