#include "Solution.h"

// 思考了两分钟，感觉这题很适配并查集，于是开始尝试
Leetcode301_400::Solution::SummaryRanges::SummaryRanges()
{
    // 为了加速检查某个新值 value 左右两侧的元素，以及它本身是否属于某个其它集合，我们在这个类中存储一个较大的数组来实现并查集的功能
    this->parents.resize(10001, -1);
}

// 为了实现并查集，我们需要实现一个合并函数和一个寻找所在集合代表的函数
// 寻找所在集合代表的函数
int findParent(vector<int>& parents, int val)
{
    if(parents[val] == val)
    {
        return val;
    }
    return findParent(parents, parents[val]);
}

// 合并函数
void combine(vector<int>& parents, int val1, int val2)
{
    // 注意，有任何一个元素没有被添加过，我们都不用进行合并
    if(val1 < 0 || val2 > 10000 || parents[val1] == -1 || parents[val2] == -1)
    {
        return;
    }
    // 首先判断两个数据是否属于同一个集合
    int parent1 = findParent(parents, val1);
    int parent2 = findParent(parents, val2);
    // 注意，有任何一个元素没有被添加过，我们都不用进行合并
    if(parent1 != parent2)
    {
        // 如果两个元素不属于同一个集合，那么我们把两个集合代表结点做一个指向关系即可
        parents[parent1] = parent2;
    }
    // 到这一步，已经可以确保两个元素在同一个集合中了
    // 或者二者中有任何一个元素还没添加到这个集合中来，因而没办法进行合并操作
}

void Leetcode301_400::Solution::SummaryRanges::addNum(int value)
{   
    // 对于一个新添加进来的元素，我们需要检查三件事
    // 1. 它本身是不是已经在一个集合中了
    // 2. 它右侧相邻位置的元素和它是否在同一个集合中
    // 3. 它左侧相邻位置的元素和它是否在同一个集合中
    // 1. 
    // 如果 parents[value] 为 -1，就说明这个元素我们是第一次添加
    if(this->parents[value] == -1)
    {
        // 注意我们的合并顺序，这和我们后面 getIntervals 中确认区间右端点的操作是一致的
        this->parents[value] = value;
        // 2.
        combine(this->parents, value, value+1);
        // 3. 
        combine(this->parents, value-1, value);
    }
    // 注意：如果这个元素已经添加过，那么我们肯定在前面第一次添加的时候就已经检查过它的左右邻居了，这里就不用检查了
}

vector<vector<int>> Leetcode301_400::Solution::SummaryRanges::getIntervals() 
{
    // 在输出归纳结果时，我们可能需要进行一些范围性的搜索
    // 规定标识当前在检查的区间的左边界和右边界的指针
    vector<vector<int>> res;
    int i = 0;
    while(i <= 10000)
    {
        if(this->parents[i] != -1)
        {
            // 重新划定一个新的区间的左边界
            int left = i;
            // 找到右边界
            int right = findParent(this->parents, left);
            res.push_back({left, right});
            i = right+1;
        }
        else
        {
            ++i;
        }
    }
    return res;
}

// 进一步优化：左边界的获取我们在第一版中使用的是暴力枚举，这并不是必要的，我们完全可以使用一个有序集合保存好所有的左边界，在输出的时候只遍历这些已知的左边界即可