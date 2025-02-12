#include "Solution.h"

bool Leetcode601_700::Soltuion::canPlaceFlowers(vector<int>& flowerbed, int n)
{
    // 简单题，但是贪心
    // 我们思考一下如何处理
    // 其实比较直观的想法是：
    // 直接从左往右遍历，遇到一个可以填入的空位，就填入，直到遍历完整个花坛为止
    // 我们从这个角度入手进行证明
    // 假设两朵花 (下标分别为 l 和 r) 之间，只有空地，没有别的花 (这个条件是一定会出现的，最小的子情况，其它情况下，就是全空的花坛，那样的话，我们直接贪心种植显然是正确的)
    // 那么两朵花之间只会有两种情况：
    // 1. 偶数个空位
    // 给出一般性的证明：
    // 我们可以断言：
    // 每填入一朵新的花，假设这朵花下标为 i
    // 那么我们很明显没法在 [l, i+1] 这个范围内再填入更多花了
    // 那么维持这个过程，直到：
    // 填到最后一个 i，而 i+1, i+2 均为空地，并且 i+3 是 r
    // 那么此时我们就完成了贪心填入
    // 此时很明显，我们换填法只能是把刚刚填入的这一串花整体往右平移一位，但是这样的话，填入的花朵总数是一样的
    // 所以贪心是最优的
    // 2. 奇数个空位
    // 同样的，不过这时按上面的填法，最后只会是 i+1 是空地，i+2 为 r
    // 贪心也是最优的
    // 上面说明的情况可以扩散到整个数组中的每一个 [1..1] 子部分中
    // 这样我们的解法就很明显是局部最优构造出了全局的最优
    // 再思考另外两种情况：
    // 左边界是 0，右侧有一个 1，这种情况只会出现在数组最左侧
    // 这时贪心显然是正确的，我们不在多余证明
    // 右边界是 0，左侧有一个 1，这种情况只会出现在数组最右侧
    // 证明方法其实和上面类似，这里不再多写
    // 我们进行模拟即可
    // 设定三个标识位，分别标识：
    // 前一位是否为空地
    // 当前位是否为空地
    // 后一位是否为空地
    bool preSpace = false, curSpace = false, postSpace = false;
    // 对整个数组进行遍历
    int m = flowerbed.size();
    for(int i = 0; i < m; ++i)
    {
        // 如果 i == 0 或者 flowerbed[i-1] 是 0，那么 preSpace = true
        if(i == 0 || flowerbed[i-1] == 0)
        {
            preSpace = true;
        }
        // 如果 flowerbed[i] == 0，那么 curSpace 为 true
        if(flowerbed[i] == 0)
        {
            curSpace = true;
        }
        // 如果 i == m-1 或者 flowerbed[i+1] 是 0，那么postSpace = true
        if(i == m-1 || flowerbed[i+1] == 0)
        {
            postSpace = true;
        }
        // 只有三者均为 true，我们才能减少 n 一次
        if(preSpace && curSpace && postSpace)
        {
            // 别忘了修改 flowerbed
            flowerbed[i] = 1;
            --n;
        }
        // 重置三个标记
        preSpace = false;
        curSpace = false;
        postSpace = false;
    } 
    return n <= 0;
}