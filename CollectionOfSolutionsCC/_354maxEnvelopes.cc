#include "Solution.h"

int Leetcode301_400::Solution::maxEnvelopes(vector<vector<int>>& envelopes)
{
    // 本题是300题：最长递增子序列的二维拓展
    // 我们先分析问题本身
    // 题目问的是，最多可以有多少个信封组成一组 "俄罗斯套娃" 信封
    // 其实意思就是让我们找一个最大的信封，这个信封内部保存了一组尺寸递增的信封
    // 这不就是二维的 "最长递增子序列" 问题吗
    // 所以，我们的问题切入角度就不难了
    // 考虑如何找出一个最长的 "尺寸" 单调递增的元组序列就是我们的解题关键
    // 不过动态两个维度值进行判断不是很容易
    // 我们可以考虑先固定一个维度
    // 因为题目要求的是 "序列"
    // 所以我们可以对原数组进行重排序
    // 如何进行重排序？
    // 一个比较明显的隐含信息是：最后找到的最长序列两个维度上都一定是非递减的
    // 所以我们可以按照任意一个维度先进行非递减排序
    // 比如我们按宽度先排序
    sort(envelopes.begin(), envelopes.end(), [&](const vector<int>& a, const vector<int>& b) {
        if(a[0] == b[0])
        {
            return a[1] > b[1];
        }
        return a[0] < b[0];
    }); 
    // 之后要进行的就是和一维的最长递增子序列问题了
    // 不过还有一个问题：如果有两个信封的宽度相同，那么我们很明显只能选一个添加到最终的结果序列中
    // 不过如果二者随机排序
    // 因为我们后面的判断逻辑是基于最长递增子序列的，那么很有可能就会导致本来两个不可以套到一起的信封，因为另一个维度的有序性而被我们套到一起了
    // 所以对于这样的信封，我们需要人为地把它们逆序，从而防止被选择到最终答案中
    // 这可以通过反序排列来实现
    // 即当两个信封宽度相同时，按照高度逆序对它们进行排序
    // 剩下的部分和300题就完全一样了
    // 回顾：dp 数组的定义是：
    // dp[i] 代表长度为 i+1 的所有序列中，结尾值最小的那一个的序列结尾值
    vector<int> dp;
    for(const auto& envelope : envelopes)
    {
        // 先二分出 dp 数组中第一个不小于 envelop[1] 的那个值的下标
        // 默认值为结尾下标
        int ret = dp.size();
        int left = 0, right = dp.size()-1;
        while(left <= right)
        {
            // 二分查找
            int mid = ((right-left)>>1)+left;
            if(dp[mid] >= envelope[1])
            {
                ret = mid;
                right = mid-1;
            }
            else
            {
                left = mid+1;
            }
        }
        // 根据 ret 的值进行 envelop[1] 的修改
        if(ret == dp.size())
        {
            dp.push_back(envelope[1]);
        }
        else
        {
            dp[ret] = envelope[1];
        }
    }    
    // 清算完成，dp 的总长度就是我们要找的答案
    return dp.size();
}