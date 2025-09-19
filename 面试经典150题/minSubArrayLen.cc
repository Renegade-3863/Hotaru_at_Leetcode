class Solution
{
public:
    int minSubArrayLen(int target, vector<int>& nums)
    {
        // 依然是滑动窗口类的问题
        // 我们思考这样的问题：
        // 固定一个右端点 right，是否可以找出一个最近的左端点，使得这个 [left, right] 框出的范围恰好可以满足要求
        // 本题限定了 nums 数组中的元素都是正整数，所以滑动窗口的二分性质是可以被满足的
        int n = nums.size(), left = 0;
        // 默认结果规定为数组长度 + 1
        int res = n+1;
        for(int right = 0; right < n; ++right)
        {
            // 从当前的缺失值（已有的区间和与 target 的差值）中减去 right 下标处的元素
            target -= nums[right];
            // 如果减少后，[left, right] 中的元素总和已经满足了要求，那么我们就可以开始右缩 left 指针
            // 直到 left 指针无法再右移为止
            while(target <= 0)
            {
                // 先更新最小长度
                res = min(res, right-left+1);
                // 之后更新 target 的值
                // 这里为什么可以直接更新 left 的值呢？
                // 因为整个数组中的元素都是正整数，所以我们可以保证：之后的 right 与现在的 left 构成的子数组
                // 其中的元素和一定都是大于等于现在的 left 与 right 构成的子数组
                // 所以对应的结果长度一定不会是比现在更优的，故我们可以直接跳过它们，不再进行考虑
                target += nums[left++];
                // 如果 target 更新后不满足要求，我们就不会再对 res 进行更新
            }
        }
        return res == n+1 ? 0 : res;
    }
}