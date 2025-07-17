class Solution
{
public:
    vector<int> searchRange(vector<int>& nums, int target)
    {
        // 不是一道很难的二分查找类题目
        // 给定的 nums 数组是已经按非递减顺序排好序的
        // 那么我们可以这样进行处理：
        // 定义一个 target 第一次出现位置的范围 [l, r]
        // 之后按区间中点 nums[mid] 和 target 之间的关系来划分区间范围
        if(nums.size() == 0)
        {
            return {-1, -1};
        }
        int l = 0, r = nums.size()-1;
        vector<int> res(2, -1);
        // 如果 l == r 了，那么我们就可以直接确定 nums[l] 为结果值
        while(l < r)
        {
            int mid = ((r-l)>>1)+l;
            if(nums[mid] < target)
            {
                // 那么 [l, mid] 之间的所有元素都不可能是 target，我们可以直接省略它们
                l = mid+1;
            } 
            if(nums[mid] >= target)
            {
                // 如果出现了这种情况，因为我们此时要找的是 "第一次出现的位置"，所以我们可以忽略 (mid, r] 中的所有元素
                r = mid;
            }
        }
        // 检查结束，l 此时就指向 nums 中第一次出现的元素位置（如果存在）
        // 而如果不存在，那么我们可以在这里就直接返回 [-1, -1]
        if(nums[l] != target)
        {
            return res;
        }
        res[0] = res[1] = l;
        // 否则，我们可以继续进行最后一个位置的查找
        // 这里可以优化一下范围，我们可以把查找范围限定到 [l, n-1]，这里 l 是我们刚刚找到的 target 第一次出现的位置
        r = nums.size()-1;
        while(l <= r)
        {
            int mid = ((r-l)>>1)+l;
            if(nums[mid] > target)
            {
                r = mid-1;
            }
            if(nums[mid] == target)
            {
                res[1] = mid;
                l = mid+1;
            } 
        }
        return res;
    }
}