#include "Solution.h"

int Leetcode501_600::Soltuion::singleNonDuplicate(vector<int>& nums)
{
    // 我们需要利用的是题目给出的 "数组有序" 这一条件
    // 如果不需要满足题目的 O(logn) 级别复杂度要求，那么我们可以用更简单的位运算算法
    // 不过这样就没有用到题目给出的 "数组有序" 条件
    // 提到有序，其实无非是在暗示二分法
    // 我们可以这样做：
    // 因为题目限定了，只有一个元素会出现一次，那么我们划定两个指针
    // 对 left 和 right 指针划定的区间，我们给出如下定义：
    // [left, right] 是可能包含只出现一次的元素的区间
    // 之后，我们每次检查区间中点处的元素
    // 如果 nums[mid] 和 nums[mid-1] 或者和 nums[mid+1] 相等，那么说明这个元素不是只出现一次的元素
    // 如何移动 left 和 right 指针？
    // 我们可以根据 mid 和左右侧的元素来判断
    // 由于包含只出现一次元素的那一侧一定有奇数个元素
    // 如果 mid 和 mid-1 两个元素相等
    // 那么我们检查 [left..mid-2] 这个区间中的元素是不是奇数个
    // 如果是，那么答案一定在左侧，我们把 right 放到 mid-2 处即可
    // 否则，那么答案一定在右侧，我们把 left 放到 mid+1 即可
    // 如果 mid 和 mid+1 两个元素相等
    // 那么我们检查 [left..mid-1] 这个区间中的元素是不是奇数个
    // 如果是，那么答案一定在左侧，我们把 right 放到 mid-1 处即可
    // 否则，那么答案一定在右侧，我们把 left 放到 mid+2 处即可
    int left = 0, right = nums.size()-1;
    while(left < right)
    {
        // 当 left == right 时，我们就找到了答案，结束循环即可
        int mid = ((right-left)>>1)+left;
        // 判断左右两侧的值，前提是合法
        if(mid-1 >= left && nums[mid-1] == nums[mid])
        {
            // 检查 [left, mid-2] 是不是奇数个元素
            // 注意，这个区间的长度不能是负数
            if(mid-2 >= left && (mid-left-1)%2)
            {
                // 是奇数个，那么把 right 挪过来
                right = mid-2;
            }
            else
            {
                // 是偶数个，那么把 left 放到 mid+1 处
                left = mid+1;
            }
        }
        else if(mid+1 <= right && nums[mid+1] == nums[mid])
        {
            // 判断 [mid+2, right] 是不是奇数个元素
            if(right >= mid+2 && (right-mid-3)%2)
            {
                // 是奇数个，那么把 left 挪过来
                left = mid+2;
            }
            else
            {
                right = mid-1;
            }
        }
        // 上面两种情况是仅有的 "nums[mid] 不是结果" 的情况，那么剩下的就是
        // "nums[mid] 是结果" 的情况
        else
        {
            // 这种情况下，我们就找到了结果，直接返回即可
            return nums[mid];
        }
    }
    // left/right 就指向了结果，返回即可
    return nums[left];
}