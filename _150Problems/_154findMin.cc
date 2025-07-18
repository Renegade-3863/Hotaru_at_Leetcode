class Solution
{
public:
    int findMin(vector<int>& nums)
    {
        // 一道想到了很简单，没想到就挺难的题
        // 多了一个条件：数组中的元素可能相等
        // 那么相比于 153 题，就是多了一条情况需要考虑
        // nums[mid] == nums[r]
        // 此时，我们没法简单断定转折点的位置
        // 解决办法也很单纯：
        // 一条信息不够，我们引入一下 l 的信息不就行了
        // 再分情况讨论：
        // 如果 nums[mid] == nums[r] 时：
        // 1. nums[mid] < nums[l]，那么说明转折点（也就是最小值点）一定在 [l, mid] 中
        // 我们可以丢弃 (mid, r] 中的元素
        // 2. nums[mid] > nums[l]，那么说明转折点就是 l，直接返回 nums[l] 即可
        // 这里需要一点思考，画画图就明白了
        // 3. nums[mid] == nums[l]，此时两头都相等，我们依然没法判断转折点的位置
        // 这里就是所说的 "想明白了很简单，不明白就挺难" 的地方
        // 我们可以丢弃 l 或者 r 中的任何一个
        // 这是一种从 logn 到 n 的 "妥协"
        // 最坏情况下，整个数组中的元素都相等，我们的这种算法就需要 O(n) 的复杂度
        // 不过这种情况还是比较少见的（）
        int l = 0, r = nums.size()-1;
        while(l < r)
        {
            int mid = ((r-l)>>1)+l;
            if(nums[mid] > nums[r])
            {
                l = mid+1;
            }
            else if(nums[mid] == nums[r])
            {
                if(nums[mid] < nums[l])
                {
                    r = mid;
                }
                else if(nums[mid] == nums[l])
                {
                    --r;
                }
                else
                {
                    return nums[l];
                }
            }
            else
            {
                r = mid;
            }
        }
        return nums[l];
    }
};