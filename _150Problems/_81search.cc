class Solution
{
public:
    bool search(vector<int>& nums, int target)
    {
        // 我们把 33 题的代码拿过来改一改：
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
                        return true;
                    }
                    else
                    {
                        r = mid-1;
                    }
                }
                return nums[l] == target ? true : false;
            }
            else if(nums[l] > nums[r])
            {
                if(nums[mid] >= nums[l])
                {
                    if(nums[mid] > target && nums[l] <= target)
                    {
                        r = mid-1;
                    }
                    else if(nums[mid] == target)
                    {
                        return true;
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
                        return true;
                    }
                    else
                    {
                        r = mid-1;
                    }
                }
            }
            else
            {
                // 此时 nums[l] == nums[r]，那么我们可以把 r 减少 1，这样可以继续 while 循环
                --r;
            }
        }
        return nums[l] == target ? true : false;
    }
}