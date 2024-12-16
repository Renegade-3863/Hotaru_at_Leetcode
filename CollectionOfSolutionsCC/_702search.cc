#include "Solution.h"

/**
 * // This is the ArrayReader's API interface.
 * // You should not implement it, or speculate about its implementation
 * class ArrayReader {
 *   public:
 *     int get(int index);
 * };
 */

int Leetcode701_800::Soltuion::search(const ArrayReader& reader, int target)
{
    // 封装得贼精致的简单二分题
    // 唯一需要一些思考的是，如何确认数组长度
    // 我们可以通过二乘+二分的方式来确定这个信息
    // 具体地，先使用一个 right 指针指向 1 这个位置 (即我们假设这个数组长度是 2)
    // 不断对 right 指针乘2，直到 reader.get(right) 返回 2^31-1 (即 right 已经超出了数组最大下标)
    // 那么数组的实际长度就在 [right>>1, right] 这个范围中
    // 我们剩下要做的就非常简单了，对这个范围二分，就能定位出 secret 数组的实际长度 len
    // 最后就是简单地定位 target 地二分算法了
    // 思路明确了，代码就行云流水了
    int check = 1;
    while(reader.get(check) != INT_MAX)
    {
        check <<= 1;
    } 
    // 循环结束时，reader.get(check>>1) < INT_MAX && reader.get(check) == INT_MAX
    int l = check>>1, r = check-1;
    int right = l;
    while(l < r)
    {
        int mid = ((r-l)>>1)+l;
        if(reader.get(mid) != INT_MAX)
        {
            right = mid;
            l = mid+1;
        }
        else
        {
            r = mid-1;
        }
    }
    // 循环结束后，right 就是 secret.size()-1
    // 正常二分找 target 了
    int left = 0;
    while(left <= right)
    {
        int mid = ((right-left)>>1)+left;
        int cur = reader.get(mid);
        // target 只可能在 mid 左边
        if(cur > target)
        {
            right = mid-1;
        }
        else if(cur == target)
        {
            return mid;
        }
        else
        {
            left = mid+1;
        }
    }
    // 不存在，返回 -1
    return -1;
}