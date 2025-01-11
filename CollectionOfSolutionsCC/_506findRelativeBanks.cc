#include "Solution.h"

vector<string> Leetcode501_600::Soltuion::findRelativeBanks(vector<int>& score)
{
    // 简单题简单做，本题没法用线性的原地哈希算法，因为数据本身的范围并不是 [1, n] 类型的
    // 所以我们最多只能使用 O(nlogn) 的排序算法来实现
    // 对 score 数组进行降序排序
    // 用一个哈希表记录排序后 score 中每个唯一元素到原来位置的映射关系
    unordered_map<int, int> mapping;
    int n = score.size();
    for(int i = 0; i < n; ++i)
    {
        mapping[score[i]] = i;
    }
    sort(score.begin(), score.end(), greater<int>());
    vector<string> res(n);
    for(int i = 0; i < n; ++i)
    {
        switch(i)
        {
            case 0:
                res[mapping[score[i]]] = "Gold Medal";
                break;
            case 1:
                res[mapping[score[i]]] = "Silver Medal";
                break;
            case 2:
                res[mapping[score[i]]] = "Bronze Medal";
                break;
            default:
                res[mapping[score[i]]] = to_string(i+1);
        }
    }
    // 返回结果
    return res;
}