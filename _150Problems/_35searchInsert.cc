class Solution
{
public:
    int searchInsert(vector<int>& nums, int target)
    {
        // 最简单的二分题目，不多写了
        int l = 0, r = nums.size()-1;
        while(l < r)
        {
            int mid = ((r-l)>>1)+l;
            if(nums[mid] > target)
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
            return nums[l] >= target ? l : l+1; 
        }
    }
};