class Solution
{
public:
    int findPeakElement(vector<int>& nums)
    {
        // 简单来说，因为题目并不要求找出全局的峰值，所以我们完全可以：
        // 保留一个 "峰值可能出现的范围" [l, r]
        // 每次取出区间中点 mid，判断 nums[mid] 是不是一个峰值
        // 如果满足：
        // nums[mid] > nums[mid-1] && nums[mid] > nums[mid+1]
        // 那么我们就找到了一个合法的结果
        // 而如果 nums[mid] <= nums[mid-1] || nums[mid] <= nums[mid+1]
        // 我们就丢弃掉任意一个比 nums[mid] 小的元素所在的那一边的元素即可
        // 这样是一定能保证找到一个合法解的
        int n = nums.size();
        int l = 0, r = n-1;
        while(l < r)
        {
            int mid= ((r-l)>>1)+l;
            int leftNum = mid == 0 ? INT_MIN : nums[mid-1], rightNum = mid == n-1 ? INT_MIN : nums[mid+1];
            if(nums[mid] > leftNum && nums[mid] > rightNum)
            {
                return mid;
            }
            else if(nums[mid] == INT_MIN)
            {
                // 如果 mid 处本身就是个 INT_MIN，那么只有两侧存在严格大于 INT_MIN 的值的时候，我们才往那个方向走
                // 否则直接返回 -1 作为结果（题目限定这种不存在峰值的情况不存在
                if(leftNum > INT_MIN)
                {
                    r = mid-1;
                }
                else if(rightNum > INT_MIN)
                {
                    l = mid+1;
                }
                else
                {
                    return -1;
                }
            }
            // 否则，nums[mid] <= leftNum || nums[mid] <= rightNum 
            else if(nums[mid] <= leftNum)
            {
                // 此时我们可以默认丢弃右侧这一边，无论右侧是否满足 nums[mid] <= rightNum
                r = mid-1; 
            }
            // 否则，nums[mid] <= rightNum
            else
            {
                // 此时我们默认丢弃左侧这一边
                l = mid+1;
            }
        }
        return l;
    }
};