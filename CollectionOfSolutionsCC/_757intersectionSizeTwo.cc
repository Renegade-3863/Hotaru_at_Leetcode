#include "Solution.h"

// 备注：这是一个错误的答案，如果想看一下错误思路的，可以阅读一下（）
int Leetcode701_800::Soltuion::intersectionSizeTwo(vector<vector<int>>& intervals)
{
    // 基本可以确定是一道贪心的题目
    // 贪心类问题的逻辑不那么明显，需要我们很多的思考（而不是 coding）
    // 简单写几个案例，我们会发现一些特点，以及一些排序的思路（贪心类，十道题，基本有十道都需要排序）
    // 例如：[1, 3], [1, 4], [2, 5], [3, 5] 这个例子
    // 取值逻辑的话，比较直觉的想法是：遇到一个区间，先取较大的边界值，这些值更容易同时满足后续区间的要求
    // 但是，思考一个反例：
    // [1, 4], [1, 3], [2, 5], [3, 5]
    // 这时我们如果依然优先取 4 这个值，那么很明显就没法同时满足后面这个 [1, 3] 区间了
    // 至此，排序思路初见雏形：
    // 我们对所有区间，按照左边界从小到大排序，之后按照右边界也从小到大排序
    // 这样，就可以避免遇到上面这种 outsider 了
    // 回到 [1, 3], [1, 4], [2, 5], [3, 5] 这个例子
    // 对于 [1, 3] 这个区间，我们现在的答案集合（假设叫 S）中还没有任何备选答案
    // 那么我们就选这个区间所有元素中最大的那两个值：2 和 3
    // 此时 S = {2, 3}
    // 之后检查 [1, 4]，发现我们刚刚放到 S 中的两个元素恰好可以同时满足区间 [1, 4] 的要求
    // 之后检查 [2, 5]，我们又发现刚刚放到 S 中的这两个元素恰好可以同时满足 [2, 5] 的要求
    // 最后看 [3, 5]，我们此时发现只有 4 这个元素可以部分满足 [3, 5] 的要求
    // 那么我们再给它补一个右边界值 5
    // 达成最终结果 {2, 3, 5}
    // 虽然和官方案例给出的结果 {2, 3, 4} 不同，但是依然是满足题意的
    // 先写一下试试，贪心的证明之后再说（正常写法不是这样的，应该先论证正确性，这里先叠个甲）
    // 用两个变量，a 和 b，分别记录上面提到的 S 的最后两个值（最大值和次大值）
    // 因为 S 中前面部分的元素我们实际上不会用到
    // 初始化为 -1，一定不会被任何区间包含的值
    int a = -1, b = -1;
    sort(intervals.begin(), intervals.end(), [&](const vector<int>& va, const vector<int>& vb) -> bool {
        if(va[0] != vb[0])
        {
            // 优先使用左边界进行排序
            // 左边界小的优先
            return va[0] < vb[0];
        }
        // 其次使用右边界进行排序
        // 右边界小的优先
        return va[1] < vb[1];
    });
    // 排序完成，之后就是上面提到的贪心逻辑了
    // ret 代表 S 的大小，也是最后的返回值
    int ret = 0;
    for(const auto& interval : intervals)
    {
        // 对于每一个新的 interval，检查 interval[0] 以及 interval[1] 和 a 以及 b 的关系
        // 注意：此时一定有 interval[0] < interval[1]
        // 1. a <= b < interval[0] < ineterval[1]
        // 此时前面添加过的元素都没法应用给 interval，我们只能同时更新 a 和 b
        // 把 a 更新为 interval[1]-1，b 更新为 interval[1]
        if(b < interval[0])
        {
            a = interval[1]-1;
            b = interval[1];
            // 新增加了两个值，更新 ret 即可
            ret += 2;
        }
        // 2. a < interval[0] <= b <= interval[1]
        // 此时 b 是可以应用给 interval 的，我们只需要再往 S 中添加一个元素：interval[1] 即可
        else if(a < interval[0])
        {
            a = b;
            b = interval[1];
            ++ret;
        }
        // 来自后期的嘲讽：这个人条件 3 在这里扯淡，自己还没发现（）
        // 3. interval[0] <= a <= b <= interval[1]
        // 此时 a 和 b 都可以应用给 interval，我们不需要添加任何值
        // else
        // {
        //     // 那么实际上也就什么都不用做，直接跳过即可
        // }
        // 注意：基于我们更新 a 和 b 的逻辑，以及排序时 interval[1] 更小的在前的原则
        // 这里是不可能出现 b > interval[1] 的情况的
        // 所以后续都不用讨论了
        // 来自后期的嘲讽：这里 a 和 b 完全有可能越过 interval[1]
        // 这是因为我们更新是用的 interval[1]，排序却是优先按照的 interval[0]
    }
    // 遍历完成，返回 ret 即可
    return ret;
}

// 上面的第一版被这个简单样例干掉了：
// [[2,10],[3,7],[3,15],[4,11],[6,12],[6,16],[7,8],[7,11],[7,15],[11,12]]
/*
    分析一下出错的原因：
    在第一次遇到 [2, 10] 的时候，我们就分配了 a = 9, b = 10
    但是第二个区间 [3, 7] 实际上并不能被 {9, 10} 所满足
    也就是说，我们应该先遍历 [3, 7]，再遍历 [2, 10]
    这样取到的右边界才能保证同样受用于 [2, 10] (取到 6 和 7)
    那么是不是应该按照左边界降序排列呢？
    但是注意：如果降序排列，依照贪心的思想，我们就应该取 interval[0] 和 interval[0]+1，而不是 interval[1]-1 和 interval[1] 了
*/
int intersectionSizeTwo(vector<vector<int>>& intervals)
{
    int a = INT_MAX, b = INT_MAX;
    sort(intervals.begin(), intervals.end(), [&](const vector<int>& va, const vector<int>& vb) -> bool {
        if(va[0] != vb[0])
        {
            return va[0] > vb[0];
        }
        return va[1] < vb[1];
    });
    int ret = 0;
    // 之后我们同样尝试正序遍历 intervals
    for(const auto& interval : intervals)
    {
        // 1. interval[0] < interval[1] < a <= b 
        // 此时 a 和 b 都不能作用于 interval
        // 我们只能更新 a 和 b 为新的 interval[0] 和 interval[0]+1
        if(interval[1] < a)
        {
            a = interval[0];
            b = interval[0]+1;
            ret += 2;
        }
        // 2. interval[0] <= a <= interval[1] < b
        else if(interval[1] < b)
        {
            // 此时只有 a 是能用于 interval 的，我们只需要再添一个 interval[0] 这个值即可
            b = a;
            a = interval[0];
            ++ret;
        }
        // 3. interval[0] <= a <= b <= interval[1]
        // else
        // {
        //     // 此时二者都能应用于 interval
        //     // 我们什么也不用做
        // }
        // 注意到（这次是正确的注意到了（））
        // a 和 b 都不可能小于当前这个新 interval 的左边界
        // 这是基于我们的排序规则决定的
    }
    return ret;
}