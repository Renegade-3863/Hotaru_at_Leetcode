#include "Solution.h"

int Leetcode301_400::Solution::kthSmallest(vector<vector<int>>& matrix, int k)
{
    // 又是一道很明显的 K 路归并类题目
    // 注意到下面的事实：我们可以把这矩阵中每一行的元素都看作是一个归并串
    // 这个归并串的内部元素是有序的
    // 所以每个时刻，如果我们想找出整个矩阵中最小的那个元素，都应该从这些归并串的头部元素中选择最小的那一个
    // 我们只需要维护一个长度最大为 n 的小顶堆即可完成题目的要求
    struct cmp
    {
        bool operator() (const pair<int, int>& a, const pair<int, int>& b)
        {
            return a.second > b.second;
        }
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;
    // 第一步：向这个优先队列中添加 n 行数据流的头部元素
    int n = matrix.size();
    // 用一个数组记录每一行当前的下标位置
    vector<int> indices(n, 0);
    for(int i = 0; i < n; ++i)
    {
        pq.emplace(i, matrix[i][0]);
    }
    // 弹出最多 k 次即可
    vector<int> res(k, 0);
    int i = 0;
    while(i < k)
    {
        auto tmp = pq.top();
        res[i++] = tmp.second;
        pq.pop();
        // 检查对应的行是否还有下一个元素，如果有，压入，否则不管了
        if(++indices[tmp.first] < n)
        {
            pq.emplace(tmp.first, matrix[tmp.first][indices[tmp.first]]);
        }
    }
    return res.back();  
}