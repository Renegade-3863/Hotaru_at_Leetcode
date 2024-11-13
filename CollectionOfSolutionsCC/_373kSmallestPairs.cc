#include "Solution.h"

vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k)
{
    // 比较经典的 K 路归并算法题
    // 我们考虑对所有可能的数对进行分组
    // nums1[num11, num12, num13, ...]
    // nums2[num21, num22, num23, ...]
    // 那么我们不难确认下面这样的几组数据流
    // [num11+num21, num11+num22, num11+num23, ...]
    // [num12+num21, num12+num22, num12+num23, ...]
    // ...
    // 上面的每一列数，我们都能明确地知道它们内部的元素一定是递增的
    // 所以，每一次选择，我们都只需要选择对应剩余数据列头部的元素进行比较
    // 选出最小的那一个添加到结果数组中，并移动对应的数据列头指针
    // 直到我们找到 k 对数对为止
    // 具体到实现流程，我们实际上只需要动态维护这 nums1.size() 条数据流的头部元素的两个下标即可
    struct myPair 
    {
    public:
        myPair(int _idx1, int _idx2, int _value) : idx1(_idx1), idx2(_idx2), value(_value) {}
        // idx1, idx2 分别计算这个数对对应到两个数组中的下标
        int idx1;
        int idx2;
        // value 记录这两个值的和
        int value;
    };
    struct cmp 
    {
        // 我们要的是最小的 K 对数字，所以这里要用的是小优先队列
        bool operator() (const myPair& a, const myPair& b)
        {
            return a.value > b.value;
        }
    };
    priority_queue<myPair, vector<myPair>, cmp> pq;
    // 先添加最开始的 nums.size() 对数对
    for(int i = 0; i < nums1.size(); ++i)
    {
        pq.emplace(i, 0, nums1[i]+nums2[0]);
    }
    // 往结果数组中填入 k 个结果即可
    vector<vector<int>> res(k, vector<int>(2, 0));
    for(int i = 0; i < k; ++i)
    {
        int ptr1 = pq.top().idx1, ptr2 = pq.top().idx2;
        // 把堆顶的数对加入答案
        res[i][0] = nums1[ptr1];
        res[i][1] = nums2[ptr2];
        // 先弹出最小的数对
        pq.pop();
        // 后移堆顶标识的数对的下标
        // 注意需要检查 idx2 后面还有没有元素，没有了就不加了
        if(ptr2+1 < nums2.size())
        {
            pq.emplace(ptr1, ptr2+1, nums1[ptr1]+nums2[ptr2+1]);
        }
    }
    return res;
}