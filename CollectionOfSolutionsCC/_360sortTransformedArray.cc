#include "Solution.h"

vector<int> Leetcode301_400::Solution::sortTransformedArray(vector<int>& nums, int a, int b, int c)
{
    // 学过一元二次方程组的同学应该都知道二次函数的图像是有对称轴的
    // 这个对称轴是 x = (-b/(2a))
    // 如果 a 是 0，那么本身就是一个一次函数，我们需要另开一个运算逻辑
    if(a == 0)
    {
        if(b == 0)
        {
            vector<int> ans(nums.size(), c);
            return ans;
        }
        vector<int> ret;
        for(int i = 0; i < nums.size(); ++i)
        {
            ret.push_back(b*nums[i]+c);
        }
        if(b < 0)
        {
            reverse(ret.begin(), ret.end());
        }
        return ret;
    }
    // 所以我们要把计算结果按序输出，可以根据这些 x 值距离对称轴的距离简单地判断出它们的大小顺序
    // 先计算出这个对称轴 
    double mirX = (double)(~b+1)/(2*a);
    // 之后先通过二分查找定位到 nums 数组中距离这个对称轴最近的那个值的下标
    int left = 0, right = nums.size()-1;
    int start = 0;
    while(left <= right)
    {
        int mid = ((right-left)>>1)+left;
        // 特殊情况，我们找到了恰好等于对称轴值的元素，那么直接把 start 放到这个 mid 处，结束循环即可
        if((double)(nums[mid]) == mirX)
        {
            start = mid;
            break;
        }
        // 比较中点处的值和 start 下标处的值距离 mirX 的距离
        double dist1 = abs(nums[start]-mirX), dist2 = abs(nums[mid]-mirX);
        // 如果 mid 处值的距离更近，那么我们更新 start 为 mid
        if(dist1 > dist2)
        {
            start = mid;
        }
        // 否则，不用进行更新
        // 根据 mid 下标处元素和 mirX 的大小关系，决定下一步检查哪一侧
        if(nums[mid] < mirX)
        {
            // nums[mid] 元素小于对称轴，那么我们下一步就是向右找
            left = mid+1;
        }
        else
        {
            // nums[mid] 元素大于对称轴，那么我们下一步就是向左找
            right = mid-1;
        }
    }
    // 循环结束后，我们就拿到了距离 mirX 最近的数组元素的下标
    // 之后使用双指针从这个位置开始向两侧扩散即可
    left = start, right = start+1;
    vector<int> res;
    while(left >= 0 || right < nums.size())
    {
        double dist1 = left >= 0 ? abs(nums[left]-mirX) : DBL_MAX;
        double dist2 = right < nums.size() ? abs(nums[right]-mirX) : DBL_MAX;
        // 判断两个指针上的元素哪一个距离对称轴的距离更近
        // 我们填充距离更近的那个指针指向的元素的运算结果，并移动对应的指针
        if(dist1 <= dist2)
        {
            // 相等的情况下移动左指针
            // 计算左指针处的运算结果，放到数组中
            res.push_back(a*nums[left]*nums[left]+b*nums[left]+c);
            --left;
        }
        else
        {
            // 否则移动右指针
            res.push_back(a*nums[right]*nums[right]+b*nums[right]+c);
            ++right;
        }
    }
    // 如果 a 是负数，我们需要对结果进行一下反序
    if(a < 0)
    {
        reverse(res.begin(), res.end());
    }
    // 处理完成，返回结果即可
    return res;
}