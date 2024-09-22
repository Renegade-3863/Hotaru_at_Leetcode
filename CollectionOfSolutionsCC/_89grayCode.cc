#include "Solution.h"

vector<int> Leetcode1_100::Solution::grayCode(int n)
{
    // 简单扫一眼题干：像回溯
    // 遇到回溯不会写，画递归树！
    // 画了一段时间，发现了一个很巧妙的规律
    // 利用完全二叉树的性质，这里可以利用每一层内结点下标的奇偶性来决定如何向下延伸结果
    // BFS 结束条件：已经检查到了第 n 位
    // idx 记录的是当前检查的层序号
    // 用一个队列存储完全二叉树的每一行
    queue<int> levels;
    vector<int> res;
    function<void(vector<int>&)> backtrack = [&](vector<int>& res)
    {
        int idx = 1;
        while(idx < n)
        {
            int len = levels.size();
            for(int i = 0; i < len; ++i)
            {
                // 层内序号为偶数的结点，它的左孩子要填一个0，右孩子要填一个1
                // 层内序号为奇数的结点，它的左孩子要填一个1，右孩子要填一个0
                int first = i % 2 ? 1 : 0, second = i % 2 ? 0 : 1;
                // 每次取出队头的一个元素，按照其下标进行子代生成
                int val = levels.front();
                // 弹出这个队头元素
                levels.pop();
                // 根据回溯树上的规律
                levels.push((val<<1) | first);
                if(idx == n-1)
                {
                    res.push_back((val<<1) | first);
                }
                levels.push((val<<1) | second);
                if(idx == n-1)
                {
                    res.push_back((val<<1) | second);
                }
            }
            ++idx;
        }
    };
    if(n == 0)
    {
        return res;
    }
    if(n == 1)
    {
        return {0, 1};
    }
    levels.push(0); levels.push(1);
    backtrack(res);
    return res;
}