#include "Solution.h"

// 很不错的一道二分扩展题目，值得多做几次细细品味
vector<int> findPeakGrid(vector<vector<int>>& mat)
{
    // 本题与一维的寻找峰值问题类似，也可以采用二分的方案
    // 不过如果我们在两个维度上同时进行二分，显然不是很容易确定二分策略
    // 同时也容易丢失可能的解
    // 同时题目也仅要求我们实现 O(mlogn)/O(nlogm) 的策略
    // 所以考虑遍历形式的二分
    // 这里尝试实现按列遍历的列二分
    int m = mat.size(), n = mat[0].size();
    // 规定可能存在合法结果的列
    int left = 0, right = n-1;
    // 合法的初始范围规定为每一列的上下边界
    int up = 0, down = m-1;
    // found 代表是否已经找到了答案，用做循环的退出条件之一
    bool found = false;
    vector<int> res(2, -1);
    // 退出条件为：已经遍历完了所有可能有结果的列，或者已经找到了一个合法的结果
    while(left <= right && !found)
    {
        // 对中点处的列进行遍历
        int mid = ((right-left)>>1)+left;
        // 在每一列的内部，我们使用 O(m) 的循环遍历
        int maximum = 0;
        for(int i = 1; i < m; ++i)
        {
            // 注意我们需要明确找出当前列中所有的峰值进行后续判断
            // 思考：我们是否需要考虑所有的峰值？
            // 如果要考虑的话，可能会出现无法对列区间进行二分的情况
            // 比如同一列中，有两个峰值，一个是大于左侧值，小于右侧值的
            //                      另一个是大于右侧值，小于左侧值的
            // 那么此时我们无法明确知道那一侧是有峰值的
            // 怎么办？
            // 那么我们显然可以进一步比较这两个同列中的峰值
            // 判断哪一个更大，更大的那一个显然更有希望在对应的另一侧的列中找到峰值
            // 证明方案：
            // 考虑这样的情况：
            // 两个峰值分别为：max1, max2
            // 它们有：
            // max1 < rightMax1 (第一个峰值小于它右侧的值，而大于左侧的值)
            // max2 < leftMax2 (第二个峰值小于它左侧的值，而大于右侧的值)
            // 此时，如果有 max1 > max2 (即第一个峰值大于第二个峰值)
            // 那么显然我们可以知道 rightMax1 是同时大于 max1 和 max2 的
            // 此时我们会发现另一个事实
            // 如果 max1 同时也是整个列中最大的那个元素，那么更进一步，我们可以确认 rightMax1 是大于 max1 所在列中的所有元素的
            // 此时我们就会明白：如果我们只根据每一列中的最大值进行列区间的更新，我们总能找到一个一定存在本地极大值的列
            // 因为我们更新的时候，丢掉的总是一个其中所有值都小于另一侧的列，这样的二分方案，我们总能最后定位到唯一的一个列
            // 这个列中的最大值是大于左侧列中所有元素，同时大于右侧列中所有元素的
            // 这样我们就找到了一个本地的峰值
            // 尝试更新最大值横坐标
            maximum = mat[i][mid] > mat[maximum][mid] ? i : maximum; 
        }
        // 循环了一列，找到了本列中最大的那个元素
        // 判断其左右元素，方法和162题是一样的
        // 找到了本地的峰值，直接记录结果即可
        if((mid == 0 || mat[maximum][mid] > mat[maximum][mid-1]) && (mid == n-1 || mat[maximum][mid] > mat[maximum][mid+1]))
        {
            res[0] = maximum; res[1] = mid;
            found = true;
        }
        // 需要查找右侧的列
        else if((mid == 0 || mat[maximum][mid] > mat[maximum][mid-1]) && (mid < n-1 && mat[maximum][mid] < mat[maximum][mid+1]))
        {
            res[0] = maximum; res[1] = mid+1;
            // 注意这里不能更新 found 值，因为记录的点只是一个临时可能的结果
            left = mid+1;
        }
        else if((mid > 0 && mat[maximum][mid] < mat[maximum][mid-1]) && (mid == n-1 || mat[maximum][mid] > mat[maximum][mid+1]))
        {
            res[0] = maximum; res[1] = mid-1;
            right = mid-1;
        }
        // 随便找一侧继续检查，这里我们选左侧
        else 
        {
            res[0] = maximum; res[1] = mid+1;
            left = mid+1;
        }
    }
    // 循环结束，返回结果即可
    return res;
}