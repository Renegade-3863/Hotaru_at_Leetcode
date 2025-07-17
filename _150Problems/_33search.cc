class Solution
{
public:
    int search(vector<int>& nums, int target)
    {
        // 经典的二分查找类问题
        // 我们这样进行分析
        // 划定一个可能包含有 target 的区间 [l, r]
        // 那么这个区间只可能有两种形状：
        // 1. [l, r] 中包含拐点
        // 2. [l, r] 中不包含拐点
        // 而我们有一种区分两种形状的很简单的办法：比较 nums[l] 与 nums[r]
        // 如果 nums[l] < nums[r]，那么就是情况1
        // 否则就是情况2
        // 对于情况1. 我们用正常的二分查找就可以了
        // 对于情况2. 我们需要细化分析
        // 如果 [l, r] 中包含拐点
        // 那么 mid 左右两侧必然是一边单调递增，另一边非单调递增
        // 要判断哪一边是单调递增的，我们可以通过比较 nums[l] 和 nums[mid]

        // 如果 nums[mid] >= nums[l]，那么 nums[mid] 左侧一定是单调递增的
        // 此时如果 nums[mid] > target && nums[l] > target
        // 那么说明 target 一定在 mid 右侧
        // l = mid+1
        // 而如果 nums[mid] > target && nums[l] < target
        // 那么说明 target 一定在 mid 左侧
        // r = mid-1
        // 而如果 nums[mid] < target
        // 此时 target 就一定在 mid 的右侧
        // l = mid+1
        // 如果 nums[mid] == target
        // 直接返回结果即可

        // 如果 nums[mid] < nums[l]，那么 nums[mid] 右侧一定是单调递增的
        // 此时如果 nums[mid] < target && nums[l] > target
        // 那么说明 target 一定在 nums[mid] 的右侧
        // 而如果 nums[mid] < target && nums[l] < target
        // 那么说明 target 一定在 nums[mid] 的左侧
        // 如果 nums[mid] > target
        // 那么 target 一定在 nums[mid] 左侧

        int l = 0, r = nums.size()-1;
        while(l < r)
        {
            int mid = ((r-l)>>1)+l;
            if(nums[l] < nums[r])
            {
                // 中间无拐点，那么直接使用正常的二分查找定位即可
                while(l < r)
                {
                    int mid = ((r-l)>>1)+l;
                    if(nums[mid] < target)
                    {
                        l = mid+1;
                    }
                    else if(nums[mid] == target)
                    {
                        return mid;
                    }
                    else
                    {
                        r = mid-1;
                    }
                }
                return nums[l] == target ? l : -1;
            }
            else
            {
                if(nums[mid] >= nums[l])
                {
                    if(nums[mid] > target && nums[l] <= target)
                    {
                        r = mid-1;
                    }
                    else if(nums[mid] == target)
                    {
                        return mid;
                    }
                    else
                    {
                        l = mid+1;
                    }
                }
                else
                {
                    // nums[mid] < nums[l]
                    if(nums[mid] < target && nums[l] > target)
                    {
                        l = mid+1;
                    }
                    else if(nums[mid] == target)
                    {
                        return mid;
                    }
                    else
                    {
                        r = mid-1;
                    }
                }
            }
        }
        return nums[l] == target ? l : -1;
    }  
}