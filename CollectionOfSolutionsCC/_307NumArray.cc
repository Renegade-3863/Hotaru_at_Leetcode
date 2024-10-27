#include "Solution.h"

// 单纯利用数组不可变的那种前缀和算法显然是可以的，不过我们应该注意到每次对数组单个元素的修改都会导致一串前缀和数据需要被修改
// 因而我们考虑换用更高级的线段树结构进行操作
Leetcode301_400::Solution::NumArray2::NumArray2(vector<int>& nums)
{
    // 这里我们使用之前写的线段树结构来解决本题
    // 初始化根结点
    int n = nums.size();
    this->root = new SegNode(0, n-1);
    // 之后对每个元素进行更新
    for(int i = 0; i < n; ++i)
    {
        this->root->update(i, i, nums[i]);
    }
}

void Leetcode301_400::Solution::NumArray2::update(int index, int val)
{
    // 根据 index 对线段树结点进行更新
    this->root->update(index, index, val);
}

int Leetcode301_400::Solution::NumArray2::sumRange(int left, int right)
{
    // 调用线段树的查询函数即可
    return this->root->query(left, right);
}