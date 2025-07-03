#define METHOD 0

#if METHOD == 0
class Solution
{
public:
    vector<int> twoSum(vector<int>& numbers, int target)
    {
        int n = numbers.size(), left = 0;
        int right = n-1;
        while(left < right)
        {
            int sum = numbers[left]+numbers[right];
            if(sum > target)
            {
                --right;
            }
            else if(sum == target)
            {
                return {left+1, right+1};
            }
            else
            {
                ++left;
            }
        }
        // 不存在，默认返回 {-1, -1}
        return {-1, -1};
    }
};

#else if METHOD == 1
class Solution
{
public:
    vector<int> twoSum(vector<int>& numbers, int target)
    {
        int n = numbers.size();
        // 使用二分查找来处理，这样复杂度更高，不过也是一种方法
        for(int i = 0; i < n-1; ++i)
        {
            int l = i+1, r = n-1;
            while(l <= r)
            {
                int mid = ((r-l)>>1)+l;
                int sum = numbers[i]+numbers[mid];
                // 和大于 target，说明我们当前的 target 以及右侧的所有值都不可能是结果，可以跳过
                if(sum > target)
                {
                    r = mid-1;
                }   
                else if(sum == target)
                {
                    return {i+1, mid+1};
                }
                else
                {
                    l = mid+1;
                }
            }
        }
        // 没找到，默认返回 {-1, -1}
        return {-1, -1};
    }
};

#else