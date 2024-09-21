#include "Solution.h"

bool Leetcode1_100::Solution::searchMatrix(vector<vector<int>>& matrix, int target)
{
    // 本题比较朴素的方法是对行使用二分查找，定位出可能有 target 存在的那一行，之后在行内再次执行二分查找
    // 设每一行的行首元素为 left, 行尾元素为 right
    // 那么 left, right, target 三者可能有 3 种关系：
    // 1. left < right < target
    // 2. left < target < right
    // 3. target < left < right
    // 注意，因为有限定 left <= right，所以这里只考虑这三种情况
    // 如果 target 和其中 left 或 right 相等，都可以直接返回结果了
    // 对于1. 
    // 此时我们可以简单地明确一点：target 一定不在当前行，也一定不在这一行以上的所有行
    // 对于2.
    // 此时我们也可以简单地明确：target 一定只可能出现在当前行
    // 对于3.
    // 此时我们也可以简单地明确：target 一定不在当前行，也一定不在这一行以下的所有行
    // 这就明确了我们对行二分的思路
    // 行内二分的算法是最简单的二分查找，直接写就行
#if 0
    int m = matrix.size(), n = matrix[0].size();
    // 定义行二分的区间边界
    int up = 0, down = m-1;
    // 循环退出条件为边界内不再存在未明确是否可能包含 target 的行
    // row 用来记录 target 可能存在的那一行
    int row = -1;
    while(up <= down)
    {
        // 取中点
        int mid = ((down-up)>>1)+up;
        // 先搞定出现了相等的情况
        if(matrix[mid][0] == target || matrix[mid][n-1] == target)
        {
            return true;
        }
        // 现在 matrix[mid][0] 和 matrix[mid][n-1] 一定都不等于 target
        // 情况1.
        if(matrix[mid][0] < target && matrix[mid][n-1] < target)
        {
            up = mid+1;
        }
        // 情况2.
        else if(matrix[mid][0] < target && target < matrix[mid][n-1])
        {
            row = mid;
            break;
        }
        // 剩下的一定是 matrix[mid][0] > target && matrix[mid][n-1] > target
        else
        {
            down = mid-1;
        }
    }
    // 循环结束后，如果 res 仍然为 -1，说明 target 不存在，可以直接返回 false
    if(row == -1)
    {
        return false;
    }
    // 否则，就对这个可能存在 target 的唯一的行进行二分查找
    int left = 0, right = n-1;
    while(left <= right)
    {
        int mid = ((right-left)>>1)+left;
        // target 只可能在 mid 左边
        if(matrix[row][mid] > target)
        {
            right = mid-1;
        }
        // target 就是 mid 处的值
        else if(matrix[row][mid] == target)
        {
            return true;
        }
        else
        {
            left = mid+1;
        }
    }
    // 如果整个循环内没有返回，那么直接返回 false，target 值一定不存在于 matrix 中
    return false;
#endif
    // 上面的方法，不难看出时间复杂度是 O(logm+logn)
    // 本题能够进行行二分的大前提在于题中给出的这个条件：
    // 每行的第一个整数大于前一行的最后一个整数
    // 这个条件保证了我们在上面情况1中能确信 mid 行上面的所有行都一定不包含 target 
    // 如果没有这个条件，那么我们就无法确定这一点了，例如可能会有下面这种情况：
    // [[1, 3, 5, 7, 17], [8, 10, 12, 14, 16], [9, 11, 13, 15, 25]]
    // 上面这个三行五列的数组，同样满足每行中的元素从左到右按非严格递增顺序排列
    // 此时，比如我们想找 17 这个 target 值
    // 而我们一定会先检查 [8, 10, 12, 14, 16] 这个数组，此时发现 8 < 16 < 17
    // 根据上面的算法，我们直接丢弃了 [1, 3, 5, 7, 17] 这个数组，而它很显然持有着我们要的 17 这个元素
    // 所以这个条件如果缺失了，我们的行二分做法就会直接暴毙
    // 而且不光情况1和3的判断条件会失效，此时情况2的条件下，我们也无法确信 target 一定就在当前行了
    // 还是上面的例子，比如我们想找9这个 target
    // 此时第一次查找检查 [8, 10, 12, 14, 16]
    // 8 < 9 < 16
    // 而此时由于没有前面的行中最大值小于8，后面的行最小值大于16这个限制，9反而出现在了下一行中
    // 这个条件就是本题的变种：搜索二维矩阵 II了
}