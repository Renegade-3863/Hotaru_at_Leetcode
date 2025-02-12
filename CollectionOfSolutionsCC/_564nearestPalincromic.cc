#include "Solution.h"

string Leetcode501_600::Soltuion::nearestPalindromic(string n)
{
    // 没什么营养的分类讨论题
    // 这里参考了官解的分类方法
    // 首先，对于 "构造最近的回文数" 这件事，最简单的想法就是把原数较高的那一半值翻转到低位上去
    // 不过这样做并不总是最优的
    // 比如 99321
    // 我们把高位的两个 9 翻转过来，就变成了 99399，但实际上，99299 比 99399 更接近 99321
    // 同理：
    // 比如 11699
    // 比起 11611，11711 更接近 11699
    // 最后，我们考虑对中间值减少 1 可能导致的数位减少情况
    // 例如：10000 -> 翻转后 -> 10001，但是 9999 也是回文数，距离 10000 和 10001 相等，但更小
    // 所以我们还要考虑对于原数，数位少 1 的全 9 数值，以及对于原数，数位多 1 的 10xx1 形式数值
    // 最后，考虑那些本身就是回文数的值
    // 对于这些值，我们只要丢弃完全由翻转构造的那一个值，从其它四个结果中选择最近的那一个作为结果即可
    // 剩下的，我们只需要分别计算上面的五种候选值即可
    // 用 long 类型存储 n 的实际值
    long num = stol(n), ans = -1;
    // 返回一组 "候选人" 数组，存储了上面提到的所有有可能成为最终结果的值 (long 类型)
    function<vector<long>()> findCandidates = [&]() -> vector<long>
    {
        // 1. 前半翻转尾接
        int len = n.size();
        vector<long> candidates;
        candidates.push_back((long)pow(10, len-1)-1);
        candidates.push_back((long)pow(10, len)+1);
        long rev = stol(n.substr(0, (len+1)>>1));
        for(int i : {rev-1, rev, rev+1})
        {
            string revNum = to_string(i);
            string candidate = revNum + string(revNum.rbegin()+(len&1), revNum.rend());
            candidates.push_back(stol(candidate));
        }
        return candidates;
    };
    vector<long> candidates = findCandidates();
    for(const auto& candidate : candidates)
    {
        if(candidate != num)
        {
            if(ans == -1 || abs(candidate-num) < abs(ans-num) || abs(candidate-num) == abs(ans-num) && candidate < ans)
            {
                ans = candidate;
            }
        }
    }
    return to_string(ans);
}