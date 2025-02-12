#include "Solution.h"

int Leetcode601_700::Soltuion::triangleNumber(vector<int>& nums)
{
    // 乍一看不好识别想考什么，我们先简单思考一下暴力求解的方法：
    // 首先，如果给定我们三条边，如何判断它们能否构成一个有效的三角形？
    // 最一般的判断逻辑是：任意两条边之和要大于第三边
    // 所以我们可以暴力枚举，每次举出三条边，算三次两边之和是否大于第三边？
    // 似乎不必这样
    // 我们可以对 nums 数组进行排序
    // 之后每次取出三个元素，并且只检查前两个值的和是否大于第三个值
    // 我们给出下面的证明：
    // 假设三个元素为 a，b，c (其中 a <= b <= c)
    // 那么如果有 a+b > c
    // 同时因为 b+c > c >= a 
    // 所以 b+c > a 成立
    // 以及 a+c > c >= b
    // 所以 a+c > b 成立
    // 所以此时，实际上我们只需要验证 a+b > c 是否成立即可证明 a，b 和 c 是否是一个合法的三角形的三边
    // 最后，本题不要求去重，我们先按这个要求来写，后面给一份去重的代码
    // 首先对 nums 中的元素进行排序
    // 按升序排列即可
    sort(nums.begin(), nums.end());
    int n = nums.size();
    // 之后，枚举第一个元素
    // for(int first = 0; first < n-2; ++first)
    // {
        // 先不考虑去重
        // 然后，我们会有种冲动：想拿双指针遍历后面的区间
        // 因为我们发现，这不就是 "三数之和" 的变种吗！
        // 那么此时我们直接尝试用双指针枚举 second 和 thrid 的值
        // int second = first+1, third = n-1;
        // 但是，写一些细节，会发现问题：
        // 如果按照上面讲的 nums[first]+nums[second] 和 nums[third] 的关系进行判断的话
        // 会发现：
        // 如果 nums[first]+nums[second] <= nums[third]
        // 我们会发现我们没法明确要移动 second 和 third 中的哪一个
        // 因为：如果移动 second，那么没法保证 third 如果往左移动 (假设移动到 third')，当前的 second 和 first 不能满足 nums[first]+nums[second] > nums[third']
        // 而如果移动 third，也是如此
        // 所以我们会发现这种遍历方法 "不太行"
        // 不行就换路！
    // }
    // 简单分析一下为什么上面的遍历方法不行
    // 本质在于我们没法把 second 和 third 两个东西作为双指针进行遍历
    // 那么我们能不能把 first 和 second 两个东西作为双指针呢？
    // 也就是说：
    // 如果 nums[first]+nums[second] <= nums[third]
    // 我们是否能够明确，对于当前的 third，first 没法和任何一个更小的 second 处的值组合，达到超过 third 的目标呢？
    // 显然可以！
    // 反向遍历 third 居然行得通！
    // 既然明确了这一点，我们就可以开始写反向的代码了
    // 枚举第三条边，从长到短
    int res = 0;
    for(int third = n-1; third >= 2; --third)
    {
        // 不要求去重，我们不用检查 third 和 third+1 的值关系
        int first = 0, second = third-1;
        while(first < second)
        {
            // 只所以不检查 first > second 的情况，是因为这样找出的答案相当于把 
            // 之前找出的 [first, second, third] 三元组中 first 和 second 互换，这不是重复的元组，而是同一个元组，是不合法的
            // 所以我们只遍历 first < second 的情况
            // 如果 nums[first]+nums[second] <= nums[third]
            // 那么我们没法继续留用 first，因为它不可能和任何不小于 nums[second] 的值求和大于 nums[third]
            if(nums[first]+nums[second] <= nums[third])
            {
                ++first;
            }
            else
            {
                // 否则，nums[first]+nums[second] > nums[third]
                // 那么很明显 {first, second, third} 就是一个合法解
                // 可是此时应该移动哪个指针？
                // 按原则来说，循环想结束，应该移动的指针是 second
                // 不过我们应该怎样更新答案 res？
                // 如果我们只对 res 加 1，而把 second 减 1，那么似乎更新的结果就是错误的
                // 因为对于每一个在 [first, second-1] 中的元素 k，nums[k]+nums[second] 都应该是大于 nums[third] 的
                // 所以我们要累加到 res 的值实际上就是 (second-1)-first+1，也就是 second-first
                res += second-first;
                --second;
            }
        }
    }
    // 检查完成，返回结果 res 即可
    return res;
}